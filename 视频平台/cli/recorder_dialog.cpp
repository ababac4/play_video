#include "recorder_dialog.h"
#include "ui_recorder_dialog.h"

Recorder_Dialog::Recorder_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Recorder_Dialog)
{
    ui->setupUi(this);
    save_thread=new savevideothread;
    pit_wid=new  picture_widget;
    pit_wid->hide();
    pit_wid->move(0,0);
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint|
     Qt::WindowCloseButtonHint);
    connect(save_thread,SIGNAL(SIG_sendVideoFrame(QImage)),this,SLOT(sl_sentimg(QImage)));//转发给自己 桌面截图
   connect(save_thread,SIGNAL(SIG_sendPicInPic( QImage)),pit_wid,SLOT(sl_sentimg(QImage)));//转发给小窗口显示



}

Recorder_Dialog::~Recorder_Dialog()
{
    delete ui;
}


void Recorder_Dialog::on_pb_start_clicked()
{
    this->showMinimized();
    pit_wid->show();
    STRU_AV_FORMAT format;
    format.filename=m_url;
    format.frame_rate=FRAME_RATE;
    format.hasAudio=true;
    format.hasCamera=true;
    format.hasDesk=true;
QScreen *src = QApplication::primaryScreen();//主窗口
QRect rect=src->geometry();
    format.height=rect.height();
    format.width=rect.width();
    format.videoBitRate=400000;
    save_thread->setinfo(format);
    save_thread->slot_openvideo();//获取视频信息
}


void Recorder_Dialog::on_pb_end_clicked()
{
    pit_wid->hide();
    save_thread->slot_closevideo();

}


void Recorder_Dialog::on_pb_set_clicked()
{
    m_url=ui->le_url->text();
    m_url.replace("/","\\");
}

void Recorder_Dialog::sl_sentimg(QImage img)
{
    QPixmap map;
    if(!img.isNull()){
        map=QPixmap::fromImage(img.scaled(ui->lb_showimage->size(),Qt::KeepAspectRatio));
    }else{
        map=QPixmap::fromImage(img);
    }
    ui->lb_showimage->setPixmap(map);
}
