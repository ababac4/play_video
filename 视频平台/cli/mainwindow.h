#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QCloseEvent>
#include"packdef.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void sig_close_win();
    void sig_register(QString phone,QString name,QString password,Hobby h,QString duan);
    void sig_login(QString phone,QString password);
    void sig_sendSms(QString phone);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void closeEvent(QCloseEvent* event);
private slots:
   void on_pb_login_clicked();

   void on_pb_login_clear_clicked();

   void on_pb_register_clicked();

   void on_pb_clear_clicked();

   void on_pb_sendduan_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
