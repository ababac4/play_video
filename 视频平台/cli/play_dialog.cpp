#include "play_dialog.h"
#include "ui_play_dialog.h"
#include<QFileDialog>
#define PATH "E:/vedio-test/1.mp4"
#define TEST_PATH "rtmp://192.168.183.130:1935/vod//1.mp4"
#define ZHI_PATH "rtmp://192.168.183.130/videotest/user=100"
#include<QInputDialog>
#include"uploadplike.h"
#include"ckenel.h"
void Play_Dialog::setCoin(int coinid)
{
    QString path=QString(":/face/btn_avatar_a%1.png").arg(coinid);
    qDebug()<<path;
    ui->pb_icon->setIcon(QIcon(path));
}

Play_Dialog::Play_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Play_Dialog)
{

   isPlay=true;

   history_dio=new history_dialog;
   qRegisterMetaType<Hobby>("Hobby");
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
  recor_dia=new Recorder_Dialog;
    ui->time_slider->installEventFilter(this);//安装事件过滤器 让该对象称为被观察对象
    m_up_dia=new upload_file;
    com_dio=new comment;
    connect(m_up_dia,SIGNAL(sig_Uploadfile(QString,Hobby)),this,SIGNAL(sig_Uploadfile2(QString,Hobby)));

    connect(this,SIGNAL( sig_upload_process(qint64,qint64)),m_up_dia,SLOT(slot_upload_process(qint64,qint64)));
    connect(this,SIGNAL(sig_up_success()),m_up_dia,SLOT(slot_up_success()));
    connect(history_dio,SIGNAL(sig_play_Name(QString)),this,SIGNAL(sig_play_media_Name(QString)));
    connect(history_dio,SIGNAL(sig_play_Name(QString)),this,SLOT(slot_history()));

    connect(com_dio,SIGNAL(sig_comment_content(QString,int)),this,SIGNAL(sig_comment_media_content(QString,int)));
    connect(this,SIGNAL(sig_comment_media_sucess()),com_dio,SLOT(slot_comment_sucess()));
    flagPlay=false;
}

Play_Dialog::~Play_Dialog()
{
    delete play_ptr;
    delete ui;
}

void Play_Dialog::slot_set_Plike()
{

}

//void Play_Dialog::play_auto()
//{
//   srand(static_cast<unsigned int>(time(0)));


//while(1){
//   int play_id=m_min_fileId + rand() % (m_max_fileId - m_min_fileId + 1);
//   cout<<play_id<<endl;
//   QString m_path=QString("rtmp://192.168.183.130:1935/vod%1").arg(m_playmap[play_id]->filepath);
//   qDebug()<<m_playmap[play_id]->filepath;
//   _sleep(1000);
//}
//   play_ptr->setFileName(m_path);//播放函数在设置文件内容里面
//   slot_PlayerStateChanged(PlayerState::Playing);

//}
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

        if(Sec>play_time/2&&flagPlay==false){//读到一半算一次播放量

                flagPlay=true;
                m_user_Plike[m_FileId]->play+=1;
                m_File_Plike[m_FileId]->play+=1;

        }

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

void Play_Dialog::slot_set_comment(QString name, QString time, QString comment)
{
    comment_user* item=new comment_user;
    item->setVal(name,time,comment);
    Comment_Dialog* temp=m_Map_comment[m_FileId];

    temp->addComment(item);

}


#include<QMouseEvent>
#include<QStyle>
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

    QString string = QInputDialog::getText(this,"QInputdialog_Name", "url:",QLineEdit::Normal);
    qDebug()<<string;
    if(play_ptr->playerState()!=PlayerState::Stop){
        play_ptr->stop(true);//调用暂停停止方法
    }
    isPlay=false;
    play_ptr->setFileName(string);
    slot_PlayerStateChanged(PlayerState::Playing);
    //    play_ptr->start();
   // qDebug()<<__func__<<'\n';
    //首先要先关闭，并且要判断状态
//    if(play_ptr->playerState()!=PlayerState::Stop){
//        play_ptr->stop(true);//调用暂停停止方法
//    }
    //打开浏览 选择文件
//    QString path=QFileDialog::getOpenFileName(this,"请选择文件","./");


//    //判断
//    if(path.isEmpty()) return;
//    //设置m_play fileName
//    play_ptr->setFileName(path);//播放函数在设置文件内容里面
//  play_ptr->setFileName(TEST_PATH);
//    //play_ptr->setFileName(ZHI_PATH);
//    //play
//    slot_PlayerStateChanged(PlayerState::Playing);
}

void Play_Dialog::sig_sendimg(QImage img)
{
    //pixmap 高效显示图片
    //qDebug()<<__func__<<"  \n";
    QPixmap map=QPixmap::fromImage(img.scaled(ui->play_lable->size(),Qt::KeepAspectRatio));
    ui->play_lable->setPixmap(map);
    File_Plike*temp=m_File_Plike[m_FileId];
    ui->lb_like->setText(QString::number(temp->like));
    ui->lb_showplay->setText(QString::number(temp->play));
    if(map.isNull()&&isPlay==true&&isStop==false){

        Q_EMIT sig_play_end();
    }else if(map.isNull()&&isPlay==false){
        isPlay=true;
    }

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
        qDebug()<< "VideoPlayer::Playing";
        ui->pb_resume->hide();
        ui->pb_pause->show();

        if(m_FileId!=4){
            cout<<1<<endl;
        }
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
    play_time=Sec;
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

void Play_Dialog::slot_play_auto(QString path,int FileId)
{

    if(play_ptr->playerState()!=PlayerState::Stop){
        play_ptr->stop(true);//调用暂停停止方法
    }
    for(auto t:m_user_Plike){
        UploadPlike::creatUpload()->m_user_Plike[t.first]=t.second;
    }

    ui->pb_cllike->hide();
    ui->pb_like->show();
    flagPlay=false;//调用初次播放
    if(m_user_Plike.find(FileId)==m_user_Plike.end()){
    File_Plike* t=new File_Plike;
    t->like=0;
    t->play=0;
    m_user_Plike[FileId]=t;
    }
    m_FileId=FileId;

       play_ptr->setFileName(path);//播放函数在设置文件内容里面
       slot_PlayerStateChanged(PlayerState::Playing);

}

void Play_Dialog::slot_Download_success()
{
QMessageBox::about(this,"提示","下载成功");
}


void Play_Dialog::on_pb_pause_clicked()
{

    if(play_ptr->playerState()!=PlayerState::Playing) return;

    play_ptr->pause();
    ui->pb_resume->show();
    ui->pb_pause->hide();
}

void Play_Dialog::slot_history()
{

    isPlay=false;
}


void Play_Dialog::on_pb_stop_clicked()
{
    play_ptr->stop(true);
}

void Play_Dialog::slot_comment_media_sucess()
{

}


void Play_Dialog::on_pb_url_clicked()
{

        QString path=QFileDialog::getOpenFileName(this,"请选择文件","./");
        //判断
        if(path.isEmpty()) return;
        //设置m_play fileName
        if(play_ptr->playerState()!=PlayerState::Stop){
            play_ptr->stop(true);//调用暂停停止方法
        }
            isPlay=false;
        play_ptr->setFileName(path);//播放函数在设置文件内容里面
        slot_PlayerStateChanged(PlayerState::Playing);
}


void Play_Dialog::on_pb_recorder_clicked()
{
    recor_dia->show();
}


void Play_Dialog::on_pb_upload_clicked()
{
    m_up_dia->show();
}



void Play_Dialog::on_pb_pre_clicked()
{
    qDebug()<<__func__<<m_FileId;
    isPlay=false;
     Q_EMIT sig_play_history(m_FileId);
}


void Play_Dialog::on_pb_next_clicked()
{
   // play_ptr->stop(true);
     isPlay=false;
    Q_EMIT sig_play_end();
}




void Play_Dialog::on_pb_play_clicked()
{
    if(isStop==true){
        //isPlay=true;
        Q_EMIT sig_play_end();
    }
}


void Play_Dialog::on_pb_download_clicked()
{
qDebug()<<__func__<<endl;
on_pb_pause_clicked();
Q_EMIT sig_Download(m_FileId);
}


void Play_Dialog::on_pb_history_clicked()
{

history_dio->initqueue();
history_dio->show();

}


void Play_Dialog::on_pb_comment_clicked()
{

on_pb_pause_clicked();
Comment_Dialog *temp=new Comment_Dialog;

m_Map_comment[m_FileId]=temp;

com_dio->setFile_id(m_FileId);
Q_EMIT sig_get_comment(m_FileId);
temp->show();
com_dio->show();

}


void Play_Dialog::on_pb_recommend_clicked()
{
    Q_EMIT sig_get_recomm();
}


void Play_Dialog::on_pb_like_clicked()
{
    ui->pb_like->hide();
    ui->pb_cllike->show();
m_user_Plike[m_FileId]->like+=1;
m_File_Plike[m_FileId]->like+=1;
}

void Play_Dialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"退出提示","是否退出")==QMessageBox::Yes){
       event->accept();
       Q_EMIT sig_close_win();
    }else{
        event->ignore();//忽略不然一直卡住
    }
}


void Play_Dialog::on_pb_cllike_clicked()
{
    ui->pb_like->show();
    ui->pb_cllike->hide();
    m_user_Plike[m_FileId]->like-=1;
    m_File_Plike[m_FileId]->like-=1;
}


void Play_Dialog::on_pb_icon_clicked()
{
    Ckenel::create()->friend_list->show();
}

