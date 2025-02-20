#ifndef HISTORY_DIALOG_H
#define HISTORY_DIALOG_H

#include <QDialog>

#include<iostream>
#include"packdef.h"
using namespace std;
#include<queue>
namespace Ui {
class history_dialog;
}

class history_dialog : public QDialog
{
    Q_OBJECT
signals:
void sig_play_Name(QString name);
public:
    explicit history_dialog(QWidget *parent = nullptr);
    ~history_dialog();
    void initqueue();
private slots:
    void on_pb_history1_clicked();

    void on_pb_history1_2_clicked();

    void on_pb_history1_3_clicked();

    void on_pb_history1_4_clicked();

    void on_pb_history1_5_clicked();

    void on_pb_history1_6_clicked();
    void slot_history(QString Name,int id);


    void on_pb_upgrad_clicked();

private:
    Ui::history_dialog *ui;



};

#endif // HISTORY_DIALOG_H
