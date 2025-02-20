#ifndef PLAY_DIALOG_H
#define PLAY_DIALOG_H

#include <QDialog>
#include "vedio_play.h"
#include<QPixmap>
#include<QImage>
QT_BEGIN_NAMESPACE
#include<QTimer>

namespace Ui { class Play_Dialog; }
QT_END_NAMESPACE

class Play_Dialog : public QDialog
{
    Q_OBJECT

public:
    Play_Dialog(QWidget *parent = nullptr);
    ~Play_Dialog();
    void play_my_video(QString rtmp);
private slots:
    void on_pl_button_clicked();
    void sig_sendimg(QImage img);
    void on_pb_resume_clicked();

    void on_pb_pause_clicked();

    void on_pb_stop_clicked();

    void slot_PlayerStateChanged(int state);
    void slot_getTotalTime(qint64 uSec);
    void slot_TimerTimeOut();
    //事件过滤器
    bool eventFilter(QObject *obj, QEvent *eve);
    void on_pb_url_clicked();
    void closeEvent(QCloseEvent* event);
private:
    Ui::Play_Dialog *ui;
    Vedio_play* play_ptr;
    QTimer m_Timer;
    bool isStop;
};
#endif // PLAY_DIALOG_H
