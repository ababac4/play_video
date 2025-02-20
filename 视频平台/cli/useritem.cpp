#include "useritem.h"
#include "ui_useritem.h"

useritem::useritem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::useritem)
{
    ui->setupUi(this);
}

useritem::~useritem()
{
    delete ui;
}

void useritem::setFrientItem(int id, QString name, QString feeling, int coinId)
{
    m_id=id;//好友信息
    m_name=name;
    m_feeling=feeling;

    m_coinId=coinId;
    ui->lb_feeling->setText(feeling);
    ui->lb_name->setText(name);
QString path = QString(":/face/btn_avatar_a%1.png").arg(m_coinId);
ui->pb_icon->setIcon(QIcon(path));
}

void useritem::on_pb_icon_clicked()
{
    Q_EMIT sig_sendid(m_id);
}

const QString &useritem::name() const
{
    return m_name;
}

