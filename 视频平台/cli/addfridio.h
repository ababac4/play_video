#ifndef ADDFRIDIO_H
#define ADDFRIDIO_H

#include <QDialog>

namespace Ui {
class addfridio;
}

class addfridio : public QDialog
{
    Q_OBJECT
signals:
    void sig_addrs(int rq,int id);
public:
    explicit addfridio(QWidget *parent = nullptr);
    void setInfo(int m_id,QString name);
    ~addfridio();

private slots:
    void on_pb_yes_clicked();

    void on_pb_no_clicked();

private:
    Ui::addfridio *ui;
    int m_userid;
};

#endif // ADDFRIDIO_H
