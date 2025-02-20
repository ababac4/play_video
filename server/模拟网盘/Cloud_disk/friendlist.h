#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QDialog>
#include<QVBoxLayout>

#include<QCloseEvent>
#include<QMenu>
#include"useritem.h"
#include"addfridio.h"
QT_BEGIN_NAMESPACE
namespace Ui { class friendlist; }
QT_END_NAMESPACE
class useritem;
class friendlist : public QDialog
{
    Q_OBJECT

public:
    friendlist(QWidget *parent = nullptr);
    ~friendlist();
void addfriend(useritem* user);
void addfriendrq(addfridio *add_rq);
void setUserinfo(QString name, QString feeling,int coinId);
void closeEvent(QCloseEvent *event);
public slots:
void slot_triggered(QAction *action);
signals:
void sig_ExitProcess();
void sig_addFriend();
private slots:
void on_pb_tool1_clicked();


private:
    Ui::friendlist *ui;
    QVBoxLayout*m_layout;
    QVBoxLayout*m_layout2;
    QMenu * m_Menu;
    useritem *item;
    addfridio *add_rq;
};
#endif // FRIENDLIST_H
