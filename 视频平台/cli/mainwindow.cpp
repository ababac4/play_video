#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //注册类

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"退出提示","是否退出")==QMessageBox::Yes){
       event->accept();
       Q_EMIT sig_close_win();
    }else{
        event->ignore();//忽略不然一直卡住
    }
}


void MainWindow::on_pb_login_clicked()
{
    QString phone=ui->le_login_phone->text();
    QString pass=ui->le_login_pass->text();
    qDebug()<<phone<<' '<<pass<<'\n';
    //验证
    QString pt=phone;
    QString passt=pass;
    if(phone.isEmpty()||pass.isEmpty()||pt.remove(' ').isEmpty()||passt.remove(' ').isEmpty()){
       QMessageBox::about(this,"提示","不能为空");
       return;
    }
    //发送
    Q_EMIT sig_login(phone,pass);
}


void MainWindow::on_pb_login_clear_clicked()
{
ui->le_login_pass->setText("");
ui->le_login_phone->setText("");
}


void MainWindow::on_pb_register_clicked()
{
    QString phone=ui->le_reg_phone->text();
    QString pass=ui->le_reg_pass->text();
     QString username=ui->le_reg_user->text();
     QString duan=ui->le_reg_duan->text();
     QString pt=phone;
     QString passt=pass;
     QString uset=username;
     qDebug()<<phone<<' '<<pass<<' '<<username<<'\n';
     //验证
     if(duan.isEmpty()||phone.isEmpty()||pass.isEmpty()||username.isEmpty()||pt.remove(' ').isEmpty()||passt.remove(' ').isEmpty()||uset.remove(' ').isEmpty()){
        QMessageBox::about(this,"提示","不能为空");
        return;
     }
     Hobby h;

     h.cartoon=ui->cb_cartoon->isChecked()?'1':'0';
     h.food=ui->cb_food->isChecked()?'1':'0';
     h.game=ui->cb_game->isChecked()?'1':'0';
     h.life=ui->cb_life->isChecked()?'1':'0';
     h.music=ui->cb_music->isChecked()?'1':'0';
     //发送
     Q_EMIT sig_register(phone,username,pass,h,duan);
}


void MainWindow::on_pb_clear_clicked()
{
ui->le_reg_pass->setText("");
ui->le_reg_phone->setText("");
ui->le_reg_user->setText("");

}


void MainWindow::on_pb_sendduan_clicked()
{
  QString phone=ui->le_reg_phone->text();
  if(phone.isEmpty()){
      QMessageBox::about(this,"提示","不能为空");
      return;
  }
  Q_EMIT sig_sendSms(phone);
}

