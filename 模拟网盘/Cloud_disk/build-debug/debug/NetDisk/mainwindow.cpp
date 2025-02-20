#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("搜索");
    this->setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinMaxButtonsHint);
    NetReuqest1=new netRequest;
    NetReuqest2=new netRequest;
    connect(NetReuqest1,SIGNAL(SIG_getResult(int,QByteArray)),this,SLOT(slot_deal_request(int, QByteArray)));
    connect(NetReuqest2,SIGNAL(SIG_getResult(int,QByteArray)),this,SLOT(slot_deal_recv(int, QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_deal_request(int code, QByteArray bt)
{
    if(code<0){
        qDebug()<<"request fail";
        return ;
    }
    //    QFile file("./text.html");
    //    qDebug()<<"请求成功";
    //    if(file.open(QIODevice::WriteOnly)){
    //        file.write(bt);
    //        file.close();
    //    }
    QString result(bt); //转化为字符串
    //提取
    int idx = result.indexOf( QRegExp("data-url=\"https*://baike.sogou.com") );
    QString str = result.mid( idx );
    int beginIdx = str.indexOf(QRegExp("https*://") );
    int endIdx = str.indexOf("\">");
    str = str.mid( beginIdx , endIdx- beginIdx );
    qDebug() << str;
    //发送第二个链接请求
    NetReuqest2->slot_sendUrlRequest( str );
}


void MainWindow::on_pb_send_clicked()
{
    QString str=ui->le_find->text();
    QString con=QString("https://www.sogou.com/sie?ie=utf8&query=%1&pid=AWNb5-7772").arg(str);

    qDebug()<<con;
    NetReuqest1->slot_sendUrlRequest(con);
}

void MainWindow::slot_deal_recv(int code, QByteArray bt)
{
    if( code < 0 ){
        qDebug() << "request fail ";
        return;
    }
    QString result(bt); //转化为字符串
    //提取
    int idx = result.indexOf( QRegExp("<div id=\"j-shareAbstract\" style=\"display:none\">") );
    QString str = result.mid( idx );
    int beginIdx = QString("<div id=\"j-shareAbstract\" style=\"display:none\">").length();
    int endIdx = str.indexOf("</div>");
    str = str.mid( beginIdx , endIdx- beginIdx );
    qDebug() << str;

    ui->td_showcontent->setText(str);
}

