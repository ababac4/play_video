#ifndef UPLOAD_FILE_H
#define UPLOAD_FILE_H

#include <QDialog>

namespace Ui {
class upload_file;
}

#include"packdef.h"

class upload_file : public QDialog
{
    Q_OBJECT

signals:
    void sig_Uploadfile(QString filename,Hobby h);
public:
    explicit upload_file(QWidget *parent = nullptr);
    ~upload_file();

private slots:
    void on_pb_find_clicked();

    void on_pb_clear_clicked();
    void slot_upload_process(qint64 cur,qint64 max);
    void on_pb_upload_clicked();
    void slot_up_success();

private:
    Ui::upload_file *ui;
    QString m_filepath;
};

#endif // UPLOAD_FILE_H
