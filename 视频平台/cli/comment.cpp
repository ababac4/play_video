#include "comment.h"
#include "ui_comment.h"
#include<QMessageBox>
comment::comment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::comment)
{
    ui->setupUi(this);
}

comment::~comment()
{
    delete ui;
}

void comment::on_pb_publish_clicked()
{
    QString content=ui->le_comment->text();
    Q_EMIT sig_comment_content(content,m_file_id);
}


void comment::on_pb_clear_clicked()
{
    ui->le_comment->setText("");
}


void comment::slot_comment_sucess()
{
QMessageBox::about(this,"提示","评论发布成功");
}

void comment::setFile_id(int newFile_id)
{
    m_file_id = newFile_id;
}
