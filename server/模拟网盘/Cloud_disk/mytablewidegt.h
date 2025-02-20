#ifndef MYTABLEWIDEGT_H
#define MYTABLEWIDEGT_H

#include <QTableWidgetItem>
#include"packdef.h"
class LoginDialog;
class MyTableWidegt : public QTableWidgetItem//继承QTableWidgetItem用于插入表格
{
public:
    MyTableWidegt();

public slots:
    void slot_setInfo(FileInfo* item);

private:
FileInfo*info;
friend class LoginDialog;
};

#endif // MYTABLEWIDEGT_H
