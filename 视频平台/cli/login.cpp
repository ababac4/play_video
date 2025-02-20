#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
     diolog=new Play_Dialog;
     m_recor=new Recorder_Dialog;
}

login::~login()
{
    delete ui;
}

void login::on_pb_local_play_clicked()
{
    diolog->show();
}


void login::on_pb_recorder_clicked()
{
    m_recor->show();
}

