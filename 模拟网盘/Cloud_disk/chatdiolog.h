#ifndef CHATDIOLOG_H
#define CHATDIOLOG_H

#include <QDialog>

namespace Ui {
class chatdiolog;
}

class chatdiolog : public QDialog
{
    Q_OBJECT
signals:
    void sig_sendChatinfo(QString content,int id);
public:
    explicit chatdiolog(QWidget *parent = nullptr);
    ~chatdiolog();
    void setChatdio(QString name,int id);
    void setContent(QString name,int id,QString time,QString content);
    void setFrichat(QString content);
    void cleartd();
    const QString &name() const;

private slots:
    void on_pb_send_clicked();

private:
    Ui::chatdiolog *ui;
    int m_fid;
    QString m_name;
};

#endif // CHATDIOLOG_H
