#ifndef CKENEL_H
#define CKENEL_H

#include <QObject>
#include "mainwindow.h"
#include"packdef.h"
#include<unordered_set>
//#define USE_SERVER 1
#include<vector>
#include<iostream>
#include"md5.h"
#include"logindialog.h"
#include"csqlite.h"
#include"writelog.h"
#include"cmyaes.h"
#include"cmyrsa.h"
#include"chatdiolog.h"
#include"friendlist.h"

using namespace std;

class INetMediator;
class Ckenel;
typedef void (Ckenel::*PFUN)(unsigned int, char*, int);
class Ckenel : public QObject
{
    Q_OBJECT
signals:
void sig_uploadProgess(int timestamp,int pos);
void sig_DownloadProgess(int timestamp,int pos);
public:

    static Ckenel* create(){
       static Ckenel op;
        return &op;
    }
    void initpFUN();
    void loadinfo();
    void default_Path();
    void dealRegisterRS(unsigned int lSendIP, char *buf, int nlen);
    void dealLoginRS(unsigned int lSendIP, char *buf, int nlen);
    void dealUploadRs(unsigned int lSendIP, char *buf, int nlen);
    void dealContentRs(unsigned int lSendIP, char *buf, int nlen);
    void deal_GetInfo(unsigned int lSendIP, char *buf, int nlen);
    void deal_Download_FileHeadRq(unsigned int lSendIP, char *buf, int nlen);
    void deal_download_ContentRq(unsigned int lSendIP, char *buf, int nlen);
    void deal_mkdirRS(unsigned int lSendIP, char *buf, int nlen);
    void deal_Quick_Rs(unsigned int lSendIP, char *buf, int nlen);
    void deal_share_Rs(unsigned int lSendIP, char *buf, int nlen);
    void deal_GetShareRS(unsigned int lSendIP, char *buf, int nlen);
    void deal_Link_Rs(unsigned int lSendIP, char *buf, int nlen);
    void deal_addfolder(unsigned int lSendIP, char *buf, int nlen);
    void deal_deleteFileRs(unsigned int lSendIP, char *buf, int nlen);
    void deal_Upload_Conrq(unsigned int lSendIP, char *buf, int nlen);
    void slot_Readcontent(QList<local_content*>&chat_con);

    QString gbtoutf(char *str);
    void utftogb(QString csv, char *dst, int len);
    void dealfriend_Info(unsigned int lSendIP, char *buf, int nlen);
    void recv_friendRQ(unsigned int lSendIP, char *buf, int nlen);
    void deal_chatRq(unsigned int lSendIP, char *buf, int nlen);
private:
    void Initsql(int id);
    explicit Ckenel(QObject *parent = nullptr);
    explicit Ckenel(const Ckenel&temp);

    ~Ckenel();

    MainWindow *m_wind;//管理线程来处理
    QString m_ip;
    QString m_port;
    INetMediator* Tcpclient;
    PFUN funarr[_DEF_FUN_MAX];
    int m_userid;
    QString m_cur_dir;
    MD5 *md5;
    LoginDialog* dio;

    map<int,FileInfo*>m_mapTimeStampinfo;
    map<int,useritem*>m_useritem;
    map<int,chatdiolog*>m_chatdio;
    map<int,addfridio*>m_friendRQ;



    QString m_path;//根目录
    int isEnd;
    CSqlite *m_sql;
    Rsa_PublicKey m_publickey;
    friendlist *friend_list;
    QString m_username;
    QList<local_content*>chat_con;

    void dealRS(unsigned int lSendIP, char *buf, int nlen);
private slots:
    void slot_addrs(int result,int friendid);
    void slot_close_dio();
    void slot_client_data( unsigned int lSendIP , char* buf , int nlen );
    void slot_register(QString phone,QString name,QString password,QString duan);
    void slot_login(QString phone,QString password);
    void slot_send_upInfo(QString name,QString dir);
    void slot_Get_File_Info();
    void slot_download_file(int file_id,QString dir);
    void slot_download_folder(int file_id,QString dir);
    void slot_add_Folder(QString path,QString dir);
    void slot_changDir(QString dir);
    void slot_upload_folder(QString path,QString dir);
    void slot_share_info(QVector<int> res,QString dir);
    void slot_Get_sharelist();
    void slot_Send_Link(QString dir,int code);
    void slot_delete_file(QVector<int> res,QString dir);
    void slot_down_attr(int timestamp,int result);
    void slot_up_attr(int timestamp,int result);
    void slot_ReadUpload(QList<FileInfo*>&info);
    void slot_ReadDown(QList<FileInfo*>&info);
    void slot_deleteUpload(FileInfo *info);
    void slot_deleteDown(FileInfo *info);
    void slot_writeDown(FileInfo *info);
    void slot_writeUpload(FileInfo *info);
    void slot_writeContent(local_content*info);
    void slot_sendSms(QString phone);
    friend LoginDialog;
    void slot_sendChatinfo(QString content, int id);
    void slot_sendid(int id);
    void slot_addfriend();
    void dealaddfriend(unsigned int lSendIP, char *buf, int nlen);
};

#endif // CKENEL_H
