#pragma once

#include<memory.h>
#include<QString>
#include<QFile>
#define _DEF_BUFFER         (4096)
#define _DEF_CONTENT_SIZE	(1024)
#define _MAX_SIZE           (100)
#define _MAX_PATH           (260)
#define _MAX_PATH_SIZE      (260)
#define _HOBBY_SIZE         (5)
#define _SMS_SIZE           (4)

//自定义协议   先写协议头 再写协议结构
//登录 注册 获取好友信息 添加好友 聊天 发文件 下线请求
#define  _PRIVATE_MYKEY  (100)
#define _DEF_PACK_BASE	(10000)
#define _DEF_PACK_COUNT (100)


#define _DEF_FUN_MAX (_DEF_PACK_BASE+_DEF_PACK_COUNT)
//注册
#define _DEF_PACK_REGISTER_RQ	(_DEF_PACK_BASE + 0 )
#define _DEF_PACK_REGISTER_RS	(_DEF_PACK_BASE + 1 )
//登录
#define _DEF_PACK_LOGIN_RQ	(_DEF_PACK_BASE + 2 )
#define _DEF_PACK_LOGIN_RS	(_DEF_PACK_BASE + 3 )

//上传文件请求
#define _DEF_PACK_UPLOAD_FILE_RQ       (_DEF_PACK_BASE + 4 )
//上传文件回复
#define _DEF_PACK_UPLOAD_FILE_RS       (_DEF_PACK_BASE + 5 )

//文件内容请求
#define _DEF_PACK_FILE_CONTENT_RQ       (_DEF_PACK_BASE + 6 )
//文件内容回复
#define _DEF_PACK_FILE_CONTENT_RS       (_DEF_PACK_BASE + 7 )
//文件信息获取
#define _DEF_PACK_GETINFO_RQ (_DEF_PACK_BASE + 8)
#define _DEF_PACK_GETINFO_RS (_DEF_PACK_BASE + 9)
//下载文件请求
#define _DEF_PACK_DOWNLOAD_FILE_RQ			(_DEF_PACK_BASE + 10 )

//下载文件夹(文件请求)
#define _DEF_PACK_DOWNLOAD_FOLDER_RQ		(_DEF_PACK_BASE + 11 )
#define _DEF_PACK_DOWNLOAD_FILE_RS			(_DEF_PACK_BASE + 12 )
//下载文件头
#define _DEF_PACK_FILE_HEADER_RQ			(_DEF_PACK_BASE + 13 )
#define _DEF_PACK_FILE_HEADER_RS			(_DEF_PACK_BASE + 14 )
//新建文件夹请求
#define _DEF_PACK_ADD_FOLDER_RQ             (_DEF_PACK_BASE + 15 )
//新建文件夹回复
#define _DEF_PACK_ADD_FOLDER_RS             (_DEF_PACK_BASE + 16 )
//秒传
#define _DEF_PACK_QUICK_UPLOAD_RS          (_DEF_PACK_BASE + 17 )
///分享文件请求
#define _DEF_PACK_SHARE_FILE_RQ       (_DEF_PACK_BASE + 18 )
/// 分享文件回复
#define _DEF_PACK_SHARE_FILE_RS       (_DEF_PACK_BASE + 19 )
//获取自己的分享请求
#define _DEF_PACK_MY_SHARE_RQ   (_DEF_PACK_BASE + 20 )
//获取自己的分享回复
#define _DEF_PACK_MY_SHARE_RS   (_DEF_PACK_BASE + 21 )
//获取分享请求
#define _DEF_PACK_GET_SHARE_RQ       (_DEF_PACK_BASE + 22 )
//获取分享回复
#define _DEF_PACK_GET_SHARE_RS       (_DEF_PACK_BASE + 23 )
//下载文件夹
#define _DEF_PACK_FOLDER_HEADER_RQ   (_DEF_PACK_BASE + 24 )
//删除文件请求
#define _DEF_PACK_DELETE_FILE_RQ       (_DEF_PACK_BASE + 25 )
//删除文件回复
#define _DEF_PACK_DELETE_FILE_RS       (_DEF_PACK_BASE + 26 )
//请求
#define _DEF_PACK_CONTINUE_DOWNLOAD_RQ     (_DEF_PACK_BASE + 27)
//请求
#define _DEF_PACK_CONTINUE_UPLOAD_RQ     (_DEF_PACK_BASE + 28)
//回复  客户端在回复处理时 , 发文件块
#define _DEF_PACK_CONTINUE_UPLOAD_RS     (_DEF_PACK_BASE + 29)

//发送信息
#define _DEF_FRIEND_INFO   (_DEF_PACK_BASE+30)

//添加好友
#define _DEF_ADD_FRIEND_RQ  (_DEF_PACK_BASE+31)
#define _DEF_ADD_FRIEND_RS  (_DEF_PACK_BASE+32)
//短信验证
#define _DEF_PACK_SMS_RQ (_DEF_PACK_BASE+33)
#define _DEF_PACK_SMS_RS (_DEF_PACK_BASE+34)
//聊天请求
#define  _DEF_PACK_CHAT_RQ (_DEF_PACK_BASE+35)
//聊天回复
#define _DEF_PACK_CHAT_RS (_DEF_PACK_BASE+36)
//聊天返回
#define _chat_success (0)
#define _chat_error (1)
//添加好友返回
#define _add_friend_success (0)
#define _add_friend_phone_not (1)
#define _add_friend_refuse (2)
#define _add_friend_offline (3)
//在线情况
#define _offline (1)
#define _online (0)

//返回的结果
//注册请求的结果
#define user_is_exist		(0)
#define register_success	(1)
#define tel_is_exist		(2)
#define sms_empire          (3)
#define sms_wrong           (4)
//登录请求的结果
#define user_not_exist		(0)
#define password_error		(1)
#define login_success		(2)
//上传文件结果
#define upload_success      (0)
//发布评论结果
#define comment_sucesss (0)
// 添加好友结果
#define _add_friend_success (0)
#define _add_friend_phone_not (1)
#define _add_friend_refuse (2)
#define _add_friend_offline (3)

typedef int PackType;

struct Hobby{
    char food;
    char life;
    char cartoon;
    char game;
    char music;
};
//协议结构

typedef struct MY_KEY
{
    MY_KEY():type(_PRIVATE_MYKEY)
    {
        memset( KEY , 0, sizeof(KEY) );
    }
    //需要手机号码 , 密码, 昵称
    PackType type;

    char KEY[_MAX_SIZE];

}MY_KEY;
//注册

typedef struct STRU_REGISTER_RQ
{
    STRU_REGISTER_RQ():type(_DEF_PACK_REGISTER_RQ)
    {
        memset( tel  , 0, sizeof(tel));
        memset( name  , 0, sizeof(name));
        memset( password , 0, sizeof(password) );
        memset( sms, 0, sizeof(sms) );
    }
    //需要手机号码 , 密码, 昵称
    PackType type;
    char tel[_MAX_SIZE];
    char name[_MAX_SIZE];
    char password[_MAX_SIZE];
    char sms[_MAX_SIZE];

}STRU_REGISTER_RQ;

typedef struct STRU_REGISTER_RS
{
    //回复结果
    STRU_REGISTER_RS(): type(_DEF_PACK_REGISTER_RS) , result(register_success)
    {
    }
    PackType type;
    int result;

}STRU_REGISTER_RS;

//登录
typedef struct STRU_LOGIN_RQ
{
    //登录需要: 手机号 密码
    STRU_LOGIN_RQ():type(_DEF_PACK_LOGIN_RQ)
    {
        memset( tel , 0, sizeof(tel) );
        memset( password , 0, sizeof(password) );
    }
    PackType type;
    char tel[_MAX_SIZE];
    char password[_MAX_SIZE];

}STRU_LOGIN_RQ;

typedef struct STRU_LOGIN_RS
{
    // 需要 结果 , 用户的id
    STRU_LOGIN_RS(): type(_DEF_PACK_LOGIN_RS) , result(login_success),userid(0)
    {
    }
    PackType type;
    int result;
    int userid;

}STRU_LOGIN_RS;


////////////////////文件信息/////////////////
struct FileInfo
{

    FileInfo():fileid(0) , size(0),pFile( nullptr )
      , pos(0) , isPause(0),timestamp(0){

    }

    int fileid;
    QString name;
    QString dir;
    QString time;
    int size;
    QString md5;
    QString type;
    QString absolutePath;
    QString rtmp;
    int timestamp; //文件身份
    int pos; //上传或下载到什么位置

    int isPause; //暂停  0 1

    //文件指针
    FILE* pFile;
    //字节换算
    static QString getsize(int size){
        int count=0;
        int temp=size;

        while(temp){
            temp/=1024;
            if(temp)count++;
        }
        QString res;
        switch (count) {
        case 0://KB
            res=QString("0.%1KB").arg((int)(size%1024/1024.0*100),2,10,QChar('0'));
            break;
        case 1:
            res=QString("%1.%2KB").arg(size/1024).arg((int)(size%1024/1024.0*100),2,10,QChar('0'));
            break;
        case 2:
        case 3:
            res=QString("%1.%2MB").arg(size/1024/1024).arg((int)(size/1024%1024/1024.0*100),2,10,QChar('0'));
            break;
        default:
            break;
        }
        return res;
    }
};




//上传文件请求
struct STRU_UPLOAD_FILE_RQ
{
    STRU_UPLOAD_FILE_RQ():type(_DEF_PACK_UPLOAD_FILE_RQ)
      ,userid(0),size(0),timestamp(0){

        memset( fileName , 0, sizeof(fileName) );
        memset( dir , 0, sizeof(dir) );
        memset( md5 , 0, sizeof(md5) );
        memset( fileType , 0, sizeof(fileType) );
        memset( time , 0, sizeof(time) );
    }

    PackType type;
    int timestamp;//时间戳用于区分不同任务
    int userid; //服务器与时间戳配合,区分不同任务
    char fileName[_MAX_PATH_SIZE]; //上传文件名字
    int size;//大小
    char dir[_MAX_PATH_SIZE];//上传到什么目录
    char md5[_MAX_SIZE]; //上传文件的md5, 用于验证文件是否完整无误
    char fileType[_MAX_SIZE];//文件类型
    char time[_MAX_SIZE]; //上传时间
};

//上传文件回复
struct STRU_UPLOAD_FILE_RS
{
    STRU_UPLOAD_FILE_RS(): type(_DEF_PACK_UPLOAD_FILE_RS)
      , userid(0), fileid(0),result(1),timestamp(0){

    }

    PackType type;
    int timestamp;//时间戳用于区分不同任务
    int userid;//用户id
    int fileid; //文件id
    int result; //结果
};


//文件内容请求
struct STRU_FILE_CONTENT_RQ
{
    STRU_FILE_CONTENT_RQ():type(_DEF_PACK_FILE_CONTENT_RQ),
        userid(0),fileid(0),len(0),timestamp(0){
        memset( content , 0 , sizeof(content));
    }

    PackType type;
    int timestamp;//时间戳用于区分不同任务
    int userid;//用户id
    int fileid;//文件id
    char content[_DEF_BUFFER];//文件内容 也叫文件块   _DEF_BUFFER  4096
    int len;//文件内容长度
};

//文件内容回复
struct STRU_FILE_CONTENT_RS
{
    STRU_FILE_CONTENT_RS():type(_DEF_PACK_FILE_CONTENT_RS),
        userid(0),fileid(0),result(1),len(0),timestamp(0){

    }
    PackType type;
    int timestamp;//时间戳用于区分不同任务
    int userid;//用户id
    int fileid;//文件id
    int result;//结果
    int len;//文件内容长度

};


// 文件信息
struct STRU_FILE_INFO{
    STRU_FILE_INFO():fileid(0),size(0){
        memset(name,0,sizeof(name));
        memset(time,0,sizeof(time));
        memset(fileType,0,sizeof(fileType));
        memset(rtmp,0,sizeof(rtmp));
    }
    int fileid;
    char name[260];
    char time[100];
    int size;
    char fileType[100];
    char rtmp[100];
};
//获取文件信息回复
typedef struct STRU_GET_INFO_RQ{

    STRU_GET_INFO_RQ():type(_DEF_PACK_GETINFO_RQ),user_id(0){
     memset(dir,0,sizeof(dir));
    }
    PackType type;
    int user_id;
    char dir[_MAX_PATH_SIZE];

}STRU_GET_INFO_RQ;

//获取文件信息回复
typedef struct STRU_GET_INFO_RS{

    STRU_GET_INFO_RS():type(_DEF_PACK_GETINFO_RS),count(0){
    memset(dir,0,sizeof(dir));

    }
     PackType type;
     char dir[260];
     int count;
     STRU_FILE_INFO info_arr[];//柔性数组
     void init(){
      count=0;
      memset(dir,0,sizeof(dir));
      type=_DEF_PACK_GETINFO_RS;
     }
}STRU_GET_INFO_RS;

//下载文件请求
struct STRU_DOWNLOAD_FILE_RQ
{
    STRU_DOWNLOAD_FILE_RQ():type(_DEF_PACK_DOWNLOAD_FILE_RQ)
      ,userid(0),fileid(0),timestamp(0){
        memset( dir , 0, sizeof(dir) );
    }
    PackType type;
    int timestamp;//时间戳用于区分不同任务
    int userid; //服务器与时间戳配合,区分不同任务
    int fileid; //文件id
    char dir[ _MAX_PATH_SIZE ]; //文件所属目录

};

//下载文件夹请求
struct STRU_DOWNLOAD_FOLDER_RQ
{
    STRU_DOWNLOAD_FOLDER_RQ():type(_DEF_PACK_DOWNLOAD_FOLDER_RQ)
      ,userid(0),fileid(0),timestamp(0){
        memset( dir , 0, sizeof(dir) );
    }
    PackType type;
    int timestamp;//时间戳用于区分不同任务
    int userid; //服务器与时间戳配合,区分不同任务
    int fileid; //文件id
    char dir[ _MAX_PATH_SIZE ]; //文件所属目录

};

//下载文件回复 ( 一般也不会出现问题, 所以这个包也不用 )
struct STRU_DOWNLOAD_FILE_RS
{
    STRU_DOWNLOAD_FILE_RS():type(_DEF_PACK_DOWNLOAD_FILE_RS)
    ,timestamp(0),userid(0),fileid(0),result(1){
    }
    PackType type;
    int timestamp;//时间戳用于区分不同任务
    int userid; //服务器与时间戳配合,区分不同任务
    int fileid; //文件id
    int result; //结果
};

//文件头请求
struct STRU_FILE_HEADER_RQ
{
    STRU_FILE_HEADER_RQ():type(_DEF_PACK_FILE_HEADER_RQ)
      ,fileid(0),size(0),timestamp(0){
        memset( fileName , 0, sizeof(fileName) );
        memset( dir , 0, sizeof(dir) );
        memset( md5 , 0, sizeof(md5) );
        memset( fileType , 0, sizeof(fileType) );
    }
    PackType type;
    int timestamp;
    int fileid;
    char fileName[_MAX_PATH_SIZE];
    int size;//大小
    char dir[_MAX_PATH_SIZE];//路径
    char md5[_MAX_SIZE];
    char fileType[_MAX_SIZE];//文件类型
};

//文件头回复
struct STRU_FILE_HEADER_RS
{
    STRU_FILE_HEADER_RS(): type(_DEF_PACK_FILE_HEADER_RS)
      , userid(0), fileid(0),result(1),timestamp(0){

    }
    PackType type;
    int timestamp;
    int userid;
    int fileid;
    int result;
};

//新建文件夹请求
struct STRU_ADD_FOLDER_RQ
{
    STRU_ADD_FOLDER_RQ():type(_DEF_PACK_ADD_FOLDER_RQ)
      ,timestamp(0),userid(0){
        memset( fileName , 0, sizeof(fileName) );
        memset( dir , 0, sizeof(dir) );
        memset( time , 0, sizeof(time) );
    }
    PackType type;
    int timestamp;
    int userid;
    char fileName[_MAX_PATH_SIZE];
    char dir[_MAX_PATH_SIZE];//路径
    char time[_MAX_SIZE]; //上传时间
};

//新建文件夹回复
struct STRU_ADD_FOLDER_RS
{
    STRU_ADD_FOLDER_RS(): type(_DEF_PACK_ADD_FOLDER_RS)
     ,timestamp(0) ,userid(0), result(1){

    }
    PackType type;
    int timestamp;
    int userid;
    int result;
};


//秒传
typedef struct STRU_QUICK_UPLOAD_RS{
    STRU_QUICK_UPLOAD_RS():type(_DEF_PACK_QUICK_UPLOAD_RS),timestamp(0),userid(0),result(0){

    }
    PackType type;
    int timestamp;
    int userid;
    int result;
}STRU_QUICK_UPLOAD_RS;


//分享文件请求 : 包含 谁 分享 什么目录下面的 哪些文件( 文件id 数组 )  分享时间
struct STRU_SHARE_FILE_RQ
{
    void init(){
        type = _DEF_PACK_SHARE_FILE_RQ;
        userid = 0;
        memset( dir , 0 , sizeof(dir) );
        memset( shareTime , 0 , sizeof(shareTime) );
        itemCount = 0;
    }
    PackType type;
    int userid;
    char dir[_MAX_PATH_SIZE ];
    char shareTime[_MAX_SIZE];
    int itemCount;
    int fileidArray[]; //柔性数组
};

// 收到回复 就刷新分享列表
struct STRU_SHARE_FILE_RS
{
    STRU_SHARE_FILE_RS(): type(_DEF_PACK_SHARE_FILE_RS),result(0){

    }
    PackType type;
    int result;
};



//获取自己的分享请求  谁获取  考虑加个时间 比如获取半个月的  todo
struct STRU_MY_SHARE_RQ
{
    STRU_MY_SHARE_RQ():type( _DEF_PACK_MY_SHARE_RQ) , userid(0){

    }
    PackType type;
    int userid;
    // 考虑加入时间 获取指定时间范围的分享
};

//分享文件信息: 名字 大小 分享时间 链接 (密码 todo )
struct STRU_MY_SHARE_FILE
{
    char name[_MAX_PATH_SIZE];
    int size;
    char time[_MAX_SIZE];
    int shareLink;
};

//获取自己的分享回复  分享文件的列表 文件: 名字 大小 分享时间 链接 (密码 todo )
struct STRU_MY_SHARE_RS
{
    void init() {
        type = _DEF_PACK_MY_SHARE_RS; itemCount = 0;
    }
    PackType type;
    int itemCount;
    STRU_MY_SHARE_FILE items[];
};

//获取分享
struct STRU_GET_SHARE_RQ
{
    STRU_GET_SHARE_RQ():type(_DEF_PACK_GET_SHARE_RQ)
      ,userid(0), shareLink(0){
        memset(dir , 0 , sizeof(dir));
        memset(time , 0 , sizeof(time));
    }
    PackType type;
    int userid;
    int shareLink; // 9位 首位是1-9 数字
    char dir[_MAX_PATH_SIZE];
    char time[_MAX_SIZE];
    //直接加载这个路径下面
};

//获取分享回复 :收到刷新
struct STRU_GET_SHARE_RS
{
    STRU_GET_SHARE_RS():type(_DEF_PACK_GET_SHARE_RS)
      ,result(0) {
        memset(dir , 0 , sizeof(dir));
    }
    PackType type;
    int result;
    char dir[_MAX_PATH_SIZE];
};


typedef struct STRU_FOLDER_HEADER_RQ{
    STRU_FOLDER_HEADER_RQ():type(_DEF_PACK_FOLDER_HEADER_RQ)
      ,timestamp(0),fileid(0){
        memset( fileName , 0, sizeof(fileName) );
        memset( dir , 0, sizeof(dir) );
    }
    PackType type;
    int timestamp;
    int fileid;
    char fileName[_MAX_PATH_SIZE];
    char dir[_MAX_PATH_SIZE];//路径
}STRU_FOLDER_HEADER_RQ;

//删除文件请求 : 某人 删除某路径下的 某文件 fileid数组
struct STRU_DELETE_FILE_RQ
{
    void init()
    {
        type = _DEF_PACK_DELETE_FILE_RQ;
        userid = 0;
        fileCount = 0;
        memset( dir , 0 , sizeof(dir) );
    }
    PackType type;
    int userid;
    char dir[_MAX_PATH_SIZE];
    int fileCount;
    int fileidArray[];
};

//删除文件回复
struct STRU_DELETE_FILE_RS
{
    STRU_DELETE_FILE_RS():type(_DEF_PACK_DELETE_FILE_RS)
      ,result(1){
        memset( dir , 0 , sizeof(dir) );
    }
    PackType type;
    int result;
    char dir[_MAX_PATH_SIZE];
};

struct STRU_CONTINUE_DOWNLOAD_RQ
{
    STRU_CONTINUE_DOWNLOAD_RQ():type(_DEF_PACK_CONTINUE_DOWNLOAD_RQ){
        userid = 0;
        timestamp = 0;
        fileid = 0;
        pos = 0;
        memset( dir , 0 , sizeof(dir));
    }

    PackType type;
    int userid;
    int timestamp;
    int fileid;
    int pos;
    char dir[_MAX_PATH_SIZE];
};

struct STRU_CONTINUE_UPLOAD_RQ
{
    STRU_CONTINUE_UPLOAD_RQ():type(_DEF_PACK_CONTINUE_UPLOAD_RQ){
        userid = 0;
        timestamp = 0;
        fileid = 0;
        memset( dir , 0 , sizeof(dir));
    }

    PackType type;
    int userid;
    int timestamp;
    int fileid;
    char dir[_MAX_PATH_SIZE];
};

struct STRU_CONTINUE_UPLOAD_RS
{
    STRU_CONTINUE_UPLOAD_RS():type(_DEF_PACK_CONTINUE_UPLOAD_RS){
        fileid = 0;
        timestamp = 0;
        pos = 0;
        //memset( dir , 0 , sizeof(dir));
    }

    PackType type;
    int fileid;
    int timestamp;
    int pos;
    //char dir[_MAX_PATH_SIZE];
};

typedef struct _friend_message {
    _friend_message() :id(0), iconid(0), type(_DEF_FRIEND_INFO) {
        memset(name, 0, _MAX_SIZE);
        memset(feeling, 0,_MAX_SIZE);
    }
     PackType type;
    int id;
    int iconid;
    char feeling[_MAX_SIZE];
    char name[_MAX_SIZE];
}_friend_message;
// 添加好友请求：好友昵称、我的id、我的昵称
typedef struct _addfriend_RQ {
    _addfriend_RQ():my_id(0),type(_DEF_ADD_FRIEND_RQ){
        memset(friend_name, 0, _MAX_SIZE);
        memset(my_name, 0, _MAX_SIZE);

    }
    PackType type;
        char friend_name[_MAX_SIZE];
        char my_name[_MAX_SIZE];
        int my_id;

}_addfriend_RQ;

// 添加好友回复：添加结果（成功，好友不存在，好友拒绝，好友不在线）

typedef struct _addfriend_RS{
    _addfriend_RS():type(_DEF_ADD_FRIEND_RS),status(_add_friend_phone_not),friendid(0),my_id(0)
    {

    }
    PackType type;
    int status;
    int my_id;
    int friendid;
}_addfriend_RS;
typedef struct STRU_SMS_RQ{
    STRU_SMS_RQ():type(_DEF_PACK_SMS_RQ){
        memset( tel  ,0, sizeof(tel));
    }
PackType type;
char tel[_MAX_SIZE];
}STRU_SMS_RQ;

typedef struct STRU_SMS_RS{
    STRU_SMS_RS():type(_DEF_PACK_SMS_RS),time(0){

    }
PackType type;
int time;
}STRU_SMS_RS;

// 聊天请求：聊天内容、我的id、好友的id
typedef struct STRU_CHAR_RQ {
    STRU_CHAR_RQ():my_id(0),friendid(0),type(_DEF_PACK_CHAT_RQ){
        memset(content  ,0, sizeof(content));
    }
    PackType type;
    int my_id;
    int friendid;
    char content[_MAX_SIZE];
}STRU_CHAR_RQ;

// 聊天回复：发送结果（成功、失败）

typedef struct STRU_CHAR_RS{
    STRU_CHAR_RS() :result(_chat_error),type( _DEF_PACK_CHAT_RS){

    }
    PackType type;
    int friendid;
    int result;

}STRU_CHAR_RS;

typedef struct local_content{
    int p_id;
    QString content;
    QString time;
    int id;
    QString name;
}local_content;
