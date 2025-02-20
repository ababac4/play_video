#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<play_dialog.h>
#include "recorder_dialog.h"
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pb_local_play_clicked();

    void on_pb_recorder_clicked();

private:
    Ui::login *ui;
    Play_Dialog *diolog;
    Recorder_Dialog* m_recor;
};

#endif // LOGIN_H
