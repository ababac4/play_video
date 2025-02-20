

#include "comment_dialog.h"
#include "ui_comment_dialog.h"
#include<QDebug>

Comment_Dialog::Comment_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Comment_Dialog)
{
    ui->setupUi(this);
    m_layout=new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(3);
    ui->qwg_comment->setLayout(m_layout);
}

Comment_Dialog::~Comment_Dialog()
{
    delete ui;
}

void Comment_Dialog::addComment(comment_user *item)
{
    m_layout->addWidget(item);
}

void Comment_Dialog::clearlay()
{
    while (QLayoutItem* item = m_layout->takeAt(0)) {
        delete item->widget(); // 删除小部件
        delete item; // 删除布局项
    }

}







