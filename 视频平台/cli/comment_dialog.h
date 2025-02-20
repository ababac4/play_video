#ifndef COMMENT_DIALOG_H
#define COMMENT_DIALOG_H

#include <QDialog>
#include<QVBoxLayout>
#include"comment_user.h"
namespace Ui {
class Comment_Dialog;
}

class Comment_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Comment_Dialog(QWidget *parent = nullptr);
    ~Comment_Dialog();
  void addComment(comment_user*item);
  void clearlay();

private:
    Ui::Comment_Dialog *ui;
    QVBoxLayout* m_layout;


};

#endif // COMMENT_DIALOG_H
