#ifndef PLAY_DIALOG_H
#define PLAY_DIALOG_H

#include <QDialog>
#include "vedio_play.h"
#include<QPixmap>
#include<QImage>
QT_BEGIN_NAMESPACE
#include<QTimer>
#include"recorder_dialog.h"
namespace Ui { class Play_Dialog; }
QT_END_NAMESPACE
#include"upload_file.h"
#include<map>
#include<iostream>
using namespace std;
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()
#include <QDebug>
#include<set>
#include"history_dialog.h"
#include"comment_user.h"
#include"comment_dialog.h"
#include"comment.h"

class Play_Dialog : public QDialog
{
    Q_OBJECT
signals:
void sig_Uploadfile2(QString,Hobby);
void sig_upload_process(qint64,qint64);
void sig_up_success();
void sig_play_end();
void sig_Download(int FileId);
void sig_play_media_Name(QString);
void sig_play_history(int);
void sig_comment_media_content(QString content,int file_id);
void sig_comment_media_sucess();
void sig_get_comment(int m_FileId);
void sig_close_win();
void sig_get_recomm();
public:
    void setCoin(int coinid);
    Play_Dialog(QWidget *parent = nullptr);
    ~Play_Dialog();

map<int,Comment_Dialog*>m_Map_comment;
private slots:
    void slot_set_Plike();
    void on_pl_button_clicked();
    void sig_sendimg(QImage img);
    void on_pb_resume_clicked();
    void slot_play_auto(QString path,int FileId);
    void slot_Download_success();
    void on_pb_pause_clicked();
    void slot_history();
    void on_pb_stop_clicked();
   void slot_comment_media_sucess();
    void slot_PlayerStateChanged(int state);
    void slot_getTotalTime(qint64 uSec);
    void slot_TimerTimeOut();
    void slot_set_comment(QString name,QString time,QString comment);
    //事件过滤器
    bool eventFilter(QObject *obj, QEvent *eve);
    void on_pb_url_clicked();

    void on_pb_recorder_clicked();

    void on_pb_upload_clicked();

    void on_pb_pre_clicked();

    void on_pb_next_clicked();


    void on_pb_play_clicked();

    void on_pb_download_clicked();

    void on_pb_history_clicked();

    void on_pb_comment_clicked();

    void on_pb_recommend_clicked();

    void on_pb_like_clicked();

    void closeEvent(QCloseEvent* event);

    void on_pb_cllike_clicked();

    void on_pb_icon_clicked();

private:
    Ui::Play_Dialog *ui;
    Vedio_play* play_ptr;
    QTimer m_Timer;
    bool isStop;
    Recorder_Dialog*recor_dia;
    bool isPlay;
    upload_file*m_up_dia;
    int m_FileId;
    history_dialog *history_dio;
    comment*com_dio;


    bool flagPlay;
    qint64 play_time;
    //void add_Comment();
    void send_comment(QString content,int file_id);
public:
     map<int,File_Plike*>m_File_Plike;
     map<int,File_Plike*>m_user_Plike;
};
#endif // PLAY_DIALOG_H
