#include "dialog.h"

#include <QApplication>
#include<writelog.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();

    for(int i=0;i<30;i++){
        char buf[1024]="";
        sprintf(buf,"info,test,text:%d",i);
        WriteLog::GetInstance()->Write_log(1,"this is a log");
    }
    return a.exec();
}
