#include "play_dialog.h"
#include "ui_play_dialog.h"
#include<QFileDialog>
#define PATH "E:/vedio-test/1.mp4"
#define TEST_PATH "rtmp://192.168.183.130:1935/vod//2.mp4"
#define ZHI_PATH "rtmp://192.168.183.130/videotest/user=100"
Play_Dialog::Play_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Play_Dialog)
{

    ui->setupUi(this);
    play_ptr=new Vedio_play;
    // play_ptr->setFileName(PATH);
    connect(play_ptr,SIGNAL(sig_sendimg(QImage)),this,SLOT(sig_sendimg(QImage)));
    slot_PlayerStateChanged(PlayerState::Stop);
    connect(play_ptr,SIGNAL(SIG_PlayerStateChanged(int)),this,SLOT(slot_PlayerStateChanged(int)));
    connect( play_ptr, SIGNAL( SIG_TotalTime(qint64))  ,
             this ,SLOT( slot_getTotalTime(qint64)) );

    connect(&m_Timer,SIGNAL(timeout()),this,SLOT(slot_TimerTimeOut()));
    m_Timer.setInterval(500);//超时500ms

    ui->time_slider->installEventFilter(this);//安装事件过滤器 让该对象称为被观察对象
}

Play_Dialog::~Play_Dialog()
{
    delete play_ptr;
    delete ui;
}

void Play_Dialog::play_my_video(QString rtmp)
{
    //    play_ptr->start();

    //首先要先关闭，并且要判断状态
    if(play_ptr->playerState()!=PlayerState::Stop){
        play_ptr->stop(true);//调用暂停停止方法
    }
    //打开浏览 选择文件
//    QString path=QFileDialog::getOpenFileName(this,"请选择文件","./");


//    //判断
//    if(path.isEmpty()) return;
//    //设置m_play fileName
//    play_ptr->setFileName(path);//播放函数在设置文件内容里面
     play_ptr->setFileName(rtmp);
    //play_ptr->setFileName(ZHI_PATH);
    //play
    slot_PlayerStateChanged(PlayerState::Playing);
}
void Play_Dialog::slot_TimerTimeOut()
{
    if (QObject::sender() == &m_Timer)
    {
        qint64 Sec =play_ptr->getCurrentTime()/1000000;//变成秒
        ui->time_slider->setValue(Sec);
        QString hStr = QString("00%1").arg(Sec/3600);
        QString mStr = QString("00%1").arg(Sec/60%60);
        QString sStr = QString("00%1").arg(Sec%60);
        QString str =
                QString("%1:%2:%3").arg(hStr.right(2)).arg(mStr.right(2)).arg(sStr.right(2));
        ui->cur_time->setText(str);
        if(ui->time_slider->value() == ui->time_slider->maximum()
                && play_ptr->playerState() == PlayerState::Stop)
        {
            slot_PlayerStateChanged( PlayerState::Stop );
        }else if(ui->time_slider->value() + 1  ==
                 ui->time_slider->maximum()
                 && play_ptr->playerState() == PlayerState::Stop)
        {
            slot_PlayerStateChanged( PlayerState::Stop );
        }
    }
}
#include<QMouseEvent>
#include<QStyle>
#include <qmessagebox.h>
bool Play_Dialog::eventFilter(QObject *obj, QEvent *eve)
{
    if(obj==ui->time_slider)
    {
     if(eve->type()==QEvent::MouseButtonPress)
     {
            QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(eve);
            int value = QStyle::sliderValueFromPosition(
            ui->time_slider->minimum(), ui->time_slider->maximum(), mouseEvent->pos().x(), ui->time_slider->width());
            m_Timer.stop();//如果不停止定时器，在下面赋值时 还会回跳一下再过去，因为之前位置的定时器还会走
            ui->time_slider->setValue(value);
            play_ptr->seek((qint64)value*1000000);  //value 秒 跳转
            m_Timer.start();
            return true;
     }else{
         return false;
     }
    }
    return QDialog::eventFilter(obj,eve);
}

//qt 线程 子线程调用start()->run()执行run方法
void Play_Dialog::on_pl_button_clicked()
{
    //    play_ptr->start();
    qDebug()<<__func__<<'\n';
    //首先要先关闭，并且要判断状态
    if(play_ptr->playerState()!=PlayerState::Stop){
        play_ptr->stop(true);//调用暂停停止方法
    }
    //打开浏览 选择文件
//    QString path=QFileDialog::getOpenFileName(this,"请选择文件","./");


//    //判断
//    if(path.isEmpty()) return;
//    //设置m_play fileName
//    play_ptr->setFileName(path);//播放函数在设置文件内容里面
  play_ptr->setFileName(TEST_PATH);
    //play_ptr->setFileName(ZHI_PATH);
    //play
    slot_PlayerStateChanged(PlayerState::Playing);
}

void Play_Dialog::sig_sendimg(QImage img)
{
    //pixmap 高效显示图片
   // qDebug()<<__func__<<"  \n";
    QPixmap map=QPixmap::fromImage(img.scaled(ui->play_lable->size(),Qt::KeepAspectRatio));
    ui->play_lable->setPixmap(map);

}
void Play_Dialog::slot_PlayerStateChanged(int state)
{
    switch( state )
    {
    case PlayerState::Stop:
        qDebug()<< "VideoPlayer::Stop";
        m_Timer.stop();
        ui->time_slider->setValue(0);
        ui->end_time->setText("00:00:00");
        ui->cur_time->setText("00:00:00");

        ui->pb_pause->hide();
        ui->pb_resume->show();
        //    {
        //        QImage img;
        //        img.fill( Qt::black);
        //        sig_sendimg( img );
        //    }
        this->update();
        isStop = true;
        break;
    case PlayerState::Playing:
        //qDebug()<< "VideoPlayer::Playing";
        ui->pb_resume->hide();
        ui->pb_pause->show();
        m_Timer.start();
        this->update();
        isStop = false;
        break;
    }
}

void Play_Dialog::slot_getTotalTime(qint64 uSec)
{
    qint64 Sec = uSec/1000000;
    ui->time_slider->setRange(0,Sec);//精确到秒
    QString hStr = QString("00%1").arg(Sec/3600);
    QString mStr = QString("00%1").arg(Sec/60);
    QString sStr = QString("00%1").arg(Sec%60);
    QString str =
            QString("%1:%2:%3").arg(hStr.right(2)).arg(mStr.right(2)).arg(sStr.right(2));
    ui->end_time->setText(str);
}

void Play_Dialog::on_pb_resume_clicked()
{
    if(play_ptr->playerState()!=PlayerState::Pause) return;
    play_ptr->play();
    ui->pb_resume->hide();
    ui->pb_pause->show();

}


void Play_Dialog::on_pb_pause_clicked()
{
    if(play_ptr->playerState()!=PlayerState::Playing) return;

    play_ptr->pause();
    ui->pb_resume->show();
    ui->pb_pause->hide();
}


void Play_Dialog::on_pb_stop_clicked()
{
    play_ptr->stop(true);
}

#include<QInputDialog>
void Play_Dialog::on_pb_url_clicked()
{
    QString string = QInputDialog::getText(this,"QInputdialog_Name", "url:",QLineEdit::Normal);
    qDebug()<<string;
    if(play_ptr->playerState()!=PlayerState::Stop){
        play_ptr->stop(true);//调用暂停停止方法
    }
    play_ptr->setFileName(string);
    slot_PlayerStateChanged(PlayerState::Playing);
}

void Play_Dialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"退出提示","是否退出")==QMessageBox::Yes){
       event->accept();
       play_ptr->stop(true);
    }else{
        event->ignore();//忽略不然一直卡住
    }
}

