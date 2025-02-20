#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
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



void MainWindow::on_pb_clear_clicked()
{

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
         if(phone.isEmpty()||pass.isEmpty()||username.isEmpty()||pt.remove(' ').isEmpty()||passt.remove(' ').isEmpty()||uset.remove(' ').isEmpty()){
            QMessageBox::about(this,"提示","不能为空");
            return;
         }
         //发送
         Q_EMIT sig_register(phone,username,pass,duan);
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

