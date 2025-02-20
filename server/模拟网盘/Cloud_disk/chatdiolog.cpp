#include "chatdiolog.h"
#include "ui_chatdiolog.h"
#include"QTime"
#include<iostream>
#include<QDebug>
using namespace std;

chatdiolog::chatdiolog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatdiolog)
{
    ui->setupUi(this);
}

chatdiolog::~chatdiolog()
{
    delete ui;
}

void chatdiolog::setChatdio(QString name, int id)
{
    setWindowTitle(QString("聊天用户名:%1").arg(name));
    m_fid=id;
    m_name=name;
}

void chatdiolog::setContent(QString name, int id, QString time,QString content)
{


    ui->td_chat->append(QString("【%1】 %2").arg(name).arg(time));
    ui->td_chat->append(content);
}

void chatdiolog::setFrichat(QString content)
{
    ui->td_chat->append(QString("【%1】 %2").arg(m_name).arg(QTime::currentTime().toString("hh::mm::ss")));
    ui->td_chat->append(content);
}

void chatdiolog::cleartd()
{
    ui->td_chat->clear();
}

void chatdiolog::on_pb_send_clicked()
{
    //效验文本 不能为空 不能全为空格
    QString content=ui->te_chat->toPlainText();
    QString tmp=content;
    qDebug()<<tmp;
    if(content.isEmpty()||content.remove(" ").isEmpty()){
        ui->te_chat->setText("");
        return;
    }
    content=ui->te_chat->toHtml();
    //设置到聊天窗口上
    ui->te_chat->setText("");
    ui->td_chat->append(QString("【我】 %1").arg(QTime::currentTime().toString("hh::mm::ss")));
    ui->td_chat->append(content);
    Q_EMIT sig_sendChatinfo(tmp,m_fid);
}

const QString &chatdiolog::name() const
{
    return m_name;
}

