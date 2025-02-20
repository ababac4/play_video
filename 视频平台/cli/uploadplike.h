#ifndef UPLOADPLIKE_H
#define UPLOADPLIKE_H
#include"packdef.h"
#include <QThread>
#include<map>
#include<iostream>
#include <QTimer>
#include <QDebug>
class INetMediator;
using namespace std;
class UploadPlike : public QThread
{
    Q_OBJECT
public:
int m_running;
    static UploadPlike* creatUpload(){
        static UploadPlike temp;
        return &temp;
    }
    void run();
    void upload();
    int user_id;
    map<int,File_Plike*>m_user_Plike;
    map<int,File_Plike*>m_pre_Plike;
private:
     explicit UploadPlike(QObject *parent = nullptr);
    INetMediator* Tcpupload;

};

#endif // UPLOADPLIKE_H
