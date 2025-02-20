#include "history_dialog.h"
#include "ui_history_dialog.h"
#include<QDebug>
#include<ckenel.h>

history_dialog::history_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::history_dialog)
{
    ui->setupUi(this);

}

history_dialog::~history_dialog()
{
    delete ui;
}

void history_dialog::on_pb_history1_clicked()
{
    QString name=ui->pb_history1->text();
    if(!name.isEmpty()){
        Q_EMIT sig_play_Name(name);
    }

}


void history_dialog::on_pb_history1_2_clicked()
{
    QString name=ui->pb_history1_2->text();
    if(!name.isEmpty()){
        Q_EMIT sig_play_Name(name);
    }
}


void history_dialog::on_pb_history1_3_clicked()
{
    QString name=ui->pb_history1_3->text();
    if(!name.isEmpty()){
        Q_EMIT sig_play_Name(name);
    }
}


void history_dialog::on_pb_history1_4_clicked()
{
    QString name=ui->pb_history1_4->text();
    if(!name.isEmpty()){
        Q_EMIT sig_play_Name(name);
    }
}


void history_dialog::on_pb_history1_5_clicked()
{
    QString name=ui->pb_history1_5->text();
    if(!name.isEmpty()){
        Q_EMIT sig_play_Name(name);
    }
}


void history_dialog::on_pb_history1_6_clicked()
{
    QString name=ui->pb_history1_6->text();
    if(!name.isEmpty()){
        Q_EMIT sig_play_Name(name);
    }

}

void history_dialog::slot_history(QString Name, int id)
{
    qDebug()<<__func__;
}

void history_dialog::initqueue()
{
    for(int i=0;i<Ckenel::create()->find_my_history.size();i++){
       int len=i%6;
        QString name=Ckenel::create()->m_playName[Ckenel::create()->m_play_audio[Ckenel::create()->find_my_history[i]]->fileId];

       switch (len) {
       case 0:
           ui->pb_history1->setText(name);
           break;
       case 1:
           ui->pb_history1_2->setText(name);
           break;
       case 2:
           ui->pb_history1_3->setText(name);
           break;
       case 3:
           ui->pb_history1_4->setText(name);
           break;
       case 4:
           ui->pb_history1_5->setText(name);
           break;
       case 5:
           ui->pb_history1_6->setText(name);
           break;

       }
    }
}


void history_dialog::on_pb_upgrad_clicked()
{
    initqueue();
}

