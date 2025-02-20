#ifndef COMMENT_H
#define COMMENT_H

#include <QDialog>

namespace Ui {
class comment;
}

class comment : public QDialog
{
    Q_OBJECT
signals:
  void sig_comment_content(QString content,int fileid);
public:
    explicit comment(QWidget *parent = nullptr);
    ~comment();
  void setFile_id(int newFile_id);
private slots:
    void on_pb_publish_clicked();

    void on_pb_clear_clicked();

    void slot_comment_sucess();

private:
    Ui::comment *ui;
    int m_file_id;
};

#endif // COMMENT_H
