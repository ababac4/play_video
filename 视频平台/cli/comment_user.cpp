#include "comment_user.h"
#include "ui_comment_user.h"

comment_user::comment_user(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::comment_user)
{
    ui->setupUi(this);
}

comment_user::~comment_user()
{
    delete ui;
}

void comment_user::setVal(QString name, QString time, QString comment)
{
   ui->lb_time->setText(time);
   ui->lb_comment->setText(comment);
   ui->lb_Name->setText(name);
}
