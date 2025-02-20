#ifndef COMMENT_USER_H
#define COMMENT_USER_H

#include <QWidget>

namespace Ui {
class comment_user;
}

class comment_user : public QWidget
{
    Q_OBJECT

public:
    explicit comment_user(QWidget *parent = nullptr);
    ~comment_user();
    void setVal(QString name,QString time,QString comment);
private:
    Ui::comment_user *ui;
};

#endif // COMMENT_USER_H
