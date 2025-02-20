#ifndef CKENEL_H
#define CKENEL_H

#include <QObject>
#include "mainwindow.h"
#include"packdef.h"
#include<unordered_set>
#include"play_dialog.h"
#include"uploadplike.h"
//#define USE_SERVER 1
#include<vector>
#include<iostream>
#include"md5.h"
#include"chatdiolog.h"
#include"friendlist.h"
using namespace std;
class Ckenel;
typedef void (Ckenel::*PFUN)(unsigned int, char*, int);
class INetMediator;
#include "useritem.h"
//单例模式，核心处理类

class Ckenel : public QObject
{
    Q_OBJECT
public:

signals:
void sig_upload_messbox();
void sig_setprocess(qint64 cur,qint64 max);
void sig_play_auto(QString path,int FileId);
void sig_Download_success();
void sig_comment_sucess();
void sig_set_comment(QString name,QString time,QString comment);
void sig_set_Plike();
private slots:
   void slot_close_wind();
   void slot_client_data( unsigned int lSendIP , char* buf , int nlen );
   void slot_register(QString phone,QString name,QString password,Hobby h,QString duan);
   void slot_login(QString phone,QString password);
   void slot_updload(QString filename,Hobby h);
   void slot_play_end();
   void slot_Download(int m_FileId);
    void slot_play_history(int FileId);
    void slot_play_Name(QString fileName);
    void slot_comment_content(QString content,int fileid);
    void slot_get_comment(int m_FileId);
    void slot_sendSms(QString phone);
    void slot_get_recomm();
    void slot_sendid(int);
    void slot_sendChatinfo(QString content,int id);
    void slot_addfriend();
    void slot_addrs(int rq,int m_userid);
#ifdef USE_SERVER
    void slot_server_data( unsigned int lSendIP , char* buf , int nlen );
#endif

private:
    explicit Ckenel(QObject *parent = nullptr);
    explicit Ckenel(const Ckenel&temp);
    ~Ckenel();

   void loadinfo();
    void uploadfile(QString filename,Hobby h);
   void initpFUN();
    void play_auto();
    void sendPlike();
   void dealRegisterRS( unsigned int lSendIP , char* buf , int nlen);
   void dealLoginRS( unsigned int lSendIP , char* buf , int nlen );
   void dealUploadRS( unsigned int lSendIP , char* buf , int nlen );
   void dealInit( unsigned int lSendIP , char* buf , int nlen );
   void download_rs(unsigned int lSendIP , char* buf , int nlen );
   void block_Download(unsigned int lSendIP , char* buf , int nlen );
   void deal_comment_push(unsigned int lSendIP , char* buf , int nlen );
   void deal_get_comment(unsigned int lSendIP , char* buf , int nlen );
   void recv_Plike(unsigned int lSendIP , char* buf , int nlen );
   void dealfriend_Info(unsigned int lSendIP , char* buf , int nlen );
   void dealaddfriend(unsigned int lSendIP , char* buf , int nlen );
   void recv_friendRQ(unsigned int lSendIP , char* buf , int nlen );
public:
    vector<int>find_history;
    map<int,FileInfo*>m_FIleDownload_map;
    map<int,QString>m_playmap;
    map<int,FilePlay*>m_play_audio;
    map<int,QString>m_playName;
    vector<int>find_my_history;
      friendlist* friend_list;
    //vector<FilePlay*>vec_play_audio;
    static Ckenel* create(){
       static Ckenel op;
        return &op;
    }
    friend class UploadPlike;

private:

  MainWindow *m_wind;//管理线程来处理

   QString m_ip;
   QString m_port;

   INetMediator* Tcpclient;
   Play_Dialog *dio;
   PFUN funarr[_DEF_FUN_MAX];

   unordered_set<int>m_histoty;
   map<int,useritem*>m_useritem;
   map<int,chatdiolog*>m_chatdio;
   map<int,addfridio*>m_friendRQ;
   map<int,int>m_map;

   int m_max_fileId;
   int m_min_fileId;
   int m_userid;
   QString m_username;

#ifdef USE_SERVER
   INetMediator*Tcpserver;
#endif
};

#endif // CKENEL_H
