#ifndef USERITEM_H
#define USERITEM_H

#include <QDialog>

namespace Ui {
class useritem;
}

class useritem : public QDialog
{
    Q_OBJECT
signals:
    void sig_sendid(int id);
public:
    explicit useritem(QWidget *parent = nullptr);
    ~useritem();
    void setFrientItem(int id,QString name,QString feeling,int coinId);
    const QString &name() const;

private slots:
    void on_pb_icon_clicked();

private:
    Ui::useritem *ui;
    int m_id;
    QString m_name;
    QString m_feeling;
    int m_coinId;

};

#endif // USERITEM_H
