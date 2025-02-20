#ifndef RECORDER_DIALOG_H
#define RECORDER_DIALOG_H

#include <QDialog>
//主线程控件管理
#include"picture_widget.h"
#include"savevideothread.h"
#include<QApplication>

#include<QScreen>
QT_BEGIN_NAMESPACE
namespace Ui { class Recorder_Dialog; }
QT_END_NAMESPACE

class Recorder_Dialog : public QDialog
{
    Q_OBJECT

public:
    Recorder_Dialog(QWidget *parent = nullptr);
    ~Recorder_Dialog();

private slots:
    void on_pb_start_clicked();

    void on_pb_end_clicked();

    void on_pb_set_clicked();


    void sl_sentimg(QImage img);
private:
    Ui::Recorder_Dialog *ui;
    picture_widget * pit_wid;
    savevideothread *save_thread;
    QString m_url;
};
#endif // RECORDER_DIALOG_H
