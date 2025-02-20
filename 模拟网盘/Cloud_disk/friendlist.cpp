#include "friendlist.h"
#include "ui_friendlist.h"
#include<QMessageBox>
#include<QDebug>
friendlist::friendlist(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::friendlist)
{
    //new 一个全局布局的变量
    ui->setupUi(this);
    m_layout=new QVBoxLayout;
    m_layout2=new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout2->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(3);
    m_layout2->setSpacing(3);
//将层设置到大控件上 设置图层
ui->wid_list->setLayout(m_layout);
ui->wid_list_2->setLayout(m_layout2);

m_Menu=new QMenu;
m_Menu->addAction("添加好友");
m_Menu->addAction("不添加好友");
connect(m_Menu,SIGNAL(triggered(QAction*)),this,SLOT(slot_triggered(QAction*)));
}
friendlist::~friendlist()
{
    delete ui;
}

void friendlist::addfriend(useritem *user)
{
    //把好友添加到列表上
    m_layout->addWidget(user);
}

void friendlist::addfriendrq(addfridio *add_rq)
{
    m_layout2->addWidget(add_rq);
}

void friendlist::setUserinfo(QString name, QString feeling, int coinId)
{
    ui->le_feeling->setText(feeling);
    ui->lb_icon->setText(name);
    QString path=QString(":/face/btn_avatar_a%1.png").arg(coinId);
    qDebug()<<path;
    ui->pb_icon->setIcon(QIcon(path));

}

void friendlist::closeEvent(QCloseEvent* event)
{
   event->ignore();
   if(QMessageBox::Yes==QMessageBox::question(this,"提示","是否关闭窗口"))
   {
       this->hide();
       Q_EMIT sig_ExitProcess();
   }
}

void friendlist::slot_triggered(QAction *action)
{
qDebug()<<__func__;
    QString act=action->text();
    if(act=="添加好友")
      {
        Q_EMIT sig_addFriend();
    }else{
        return;
    }
}


void friendlist::on_pb_tool1_clicked()
{
    QPoint point=QCursor::pos();
    QSize size=m_Menu->sizeHint();
    m_Menu->exec(QPoint(point.x(),point.y()-size.height()));
}

