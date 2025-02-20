#include "addfridio.h"
#include "ui_addfridio.h"
#include"packdef.h"
addfridio::addfridio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addfridio)
{
    ui->setupUi(this);
}

void addfridio::setInfo(int m_id, QString name)
{
ui->lb_name->setText(name);
m_userid=m_id;

}

addfridio::~addfridio()
{
    delete ui;
}

void addfridio::on_pb_yes_clicked()
{
  Q_EMIT sig_addrs(_add_friend_success,m_userid);
}


void addfridio::on_pb_no_clicked()
{
Q_EMIT sig_addrs(_add_friend_refuse,m_userid);
}

