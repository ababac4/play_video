#pragma once

#include<memory.h>
#include<QString>
#include<QFile>
#define _DEF_BUFFER         (4096)
#define _DEF_CONTENT_SIZE	(1024)
#define _MAX_SIZE           (40)
#define _MAX_PATH           (260)
#define _HOBBY_SIZE         (5)
#define _SMS_SIZE           (4)
#define MD5_KEY             "1234"
//自定义协议   先写协议头 再写协议结构
//登录 注册 获取好友信息 添加好友 聊天 发文件 下线请求
#define _DEF_PACK_BASE	(10000)
#define _DEF_PACK_COUNT (100)

#define _DEF_FUN_MAX (_DEF_PACK_BASE+_DEF_PACK_COUNT)
//注册
#define _DEF_PACK_REGISTER_RQ	(_DEF_PACK_BASE + 0 )
#define _DEF_PACK_REGISTER_RS	(_DEF_PACK_BASE + 1 )
//登录
#define _DEF_PACK_LOGIN_RQ	(_DEF_PACK_BASE + 2 )
#define _DEF_PACK_LOGIN_RS	(_DEF_PACK_BASE + 3 )
//上传文件
#define _DEF_PACK_UPLOAD_RQ (_DEF_PACK_BASE + 4)
#define _DEF_PACK_UPLOAD_RS (_DEF_PACK_BASE + 5 )
#define _DEF_PACK_FILEBLOCK (_DEF_PACK_BASE + 6)
//传视频地址
#define _DEF_PACK_RTMP      (_DEF_PACK_BASE + 7)
//下载文件
#define _DEF_PACK_DOWNLOAD_RQ (_DEF_PACK_BASE + 8)
#define _DEF_PACK_DOWNLOAD_RS (_DEF_PACK_BASE + 9)
//评论
#define _DEF_PACK_COMMENT_RQ (_DEF_PACK_BASE + 10)
#define _DEF_PACK_COMMENT_RS (_DEF_PACK_BASE + 11)
//评论请求
#define _DEF_PACK_COMMENT_PUBLISH_RQ (_DEF_PACK_BASE + 12)
#define _DEF_PACK_COMMENT_PUBLISH_RS (_DEF_PACK_BASE + 13)
//短信验证
#define _DEF_PACK_SMS_RQ (_DEF_PACK_BASE+14)
#define _DEF_PACK_SMS_RS (_DEF_PACK_BASE+15)
//点赞数 播放量
#define _DEF_PACK_PLIKE_RQ (_DEF_PACK_BASE+16)
#define _DEF_PACK_PLIKE_RS (_DEF_PACK_BASE+17)
//获取推荐视频
#define _DEF_PACK_GETRM_RQ (_DEF_PACK_BASE+18)
#define _DEF_PACK_GETRM_RS (_DEF_PACK_BASE+19)
//发送信息
#define _DEF_FRIEND_INFO   (_DEF_PACK_BASE+20)

//添加好友
#define _DEF_ADD_FRIEND_RQ  (_DEF_PACK_BASE+21)
#define _DEF_ADD_FRIEND_RS  (_DEF_PACK_BASE+22)

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
//注册
typedef struct STRU_REGISTER_RQ
{
    STRU_REGISTER_RQ():type(_DEF_PACK_REGISTER_RQ)
    {
        memset( tel  ,0, sizeof(tel));
        memset( name  ,0, sizeof(name));
        memset( password ,0,sizeof(password));
        memset(m_szHobby , 0,sizeof(m_szHobby));
        memset(Sms , 0,sizeof(Sms));
    }
    //需要手机号码 , 密码, 昵称
    PackType type;
    char m_szHobby[_HOBBY_SIZE];
    char tel[_MAX_SIZE];
    char name[_MAX_SIZE];
    char password[_MAX_SIZE];
    char Sms[_SMS_SIZE];
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

typedef struct STRU_UPLOAD_RQ{
STRU_UPLOAD_RQ():type(_DEF_PACK_UPLOAD_RQ),m_nFileId(0),user_id(0){
memset(m_szFileType,0,_MAX_SIZE);
memset(m_scFileName,0,_MAX_PATH);
memset(m_szHobby,0,_HOBBY_SIZE);
}
PackType type;
char m_scFileName[_MAX_PATH];//文件名
char m_szFileType[_MAX_SIZE]; //文件类型
int m_nFileId;//使用随机数区分文件
int user_id;
__int64 m_nFileSize;//文件大小
char m_szHobby[_HOBBY_SIZE];

}STRU_UPLOAD_RQ;

typedef struct STRU_UPLOAD_RS{
    STRU_UPLOAD_RS():type(_DEF_PACK_UPLOAD_RS),Result(0){

    }
   PackType type;
   int Result;

}STRU_UPLOAD_RS;

typedef struct STRU_FILEBLOCK_RQ{
    STRU_FILEBLOCK_RQ():type(_DEF_PACK_FILEBLOCK),m_userid(0),m_nFileId(0),m_nBlock_Len(0){
    memset(m_szFileContent,0,_DEF_BUFFER);
    }
    PackType type;
    int m_userid;
    int m_nFileId;//使用随机数区分文件
    int m_nBlock_Len;
    char m_szFileContent[_DEF_BUFFER];
}STRU_FILEBLOCK_RQ;

struct FileInfo{
   int fileId;
   __int64 filePos;
   __int64 fileSize;
   QString filePath;
   QString fileName;
   QFile *pFile;
};

struct FilePlay{
   int fileId;
   QString filePath;


};

typedef struct STRU_RTMP_RQ{

    STRU_RTMP_RQ():type(_DEF_PACK_RTMP),fileId(0),user_id(0){

    memset(filepath,0,_MAX_SIZE);
    memset(fileName,0,_MAX_SIZE);
    memset(m_szHobby,0,_HOBBY_SIZE);

    }

    PackType type;
    char filepath[_MAX_SIZE];
    char fileName[_MAX_SIZE];
    char m_szHobby[_HOBBY_SIZE];
    int fileId;
    int user_id;

}STRU_RTMP_RQ;

typedef struct STRU_DOWNLOAD_RQ{
    STRU_DOWNLOAD_RQ():type(_DEF_PACK_DOWNLOAD_RQ),FileId(0),userId(0){

    }
   PackType type;
   int FileId;
   int userId;

}STRU_DOWNLOAD_RQ;

typedef struct STRU_DOWNLOAD_RS{
STRU_DOWNLOAD_RS():type(_DEF_PACK_DOWNLOAD_RS),file_id(0){
//memset(m_szFileType,0,_MAX_SIZE);
memset(m_scFileName,0,_MAX_PATH);
//memset(m_szHobby,0,_HOBBY_SIZE);
}
PackType type;
char m_scFileName[_MAX_PATH];//文件名
//char m_szFileType[_MAX_SIZE]; //文件类型
int file_id;
int m_nFileSize;//文件大小
//char m_szHobby[_HOBBY_SIZE];

}STRU_DOWNLOAD_RS;



typedef struct STRU_COMMENT_RQ{
    STRU_COMMENT_RQ():type(_DEF_PACK_COMMENT_RQ),file_id(0){

    }
    PackType type;
    int file_id;
}STRU_COMMENT_RQ;

typedef struct STRU_COMMENT_RS{
    STRU_COMMENT_RS():type(_DEF_PACK_COMMENT_RS){
     memset(name,0,sizeof(comment));
     memset(time,0,sizeof(comment));
     memset(comment,0,sizeof(comment));
    }
    PackType type;
    char name[_MAX_SIZE];
    char time[_MAX_SIZE];
    char comment[_MAX_SIZE];
}STRU_COMMENT_RS;

typedef struct STRU_COMMENT_PUBLISH_RQ{
    STRU_COMMENT_PUBLISH_RQ():type(_DEF_PACK_COMMENT_PUBLISH_RQ),user_id(0),file_id(0){
      memset(comment,0,sizeof(comment));
    }
    PackType type;
    int user_id;
    int file_id;
    char comment[_MAX_SIZE];

}STRU_COMMENT_PUBLISH_RQ;

typedef struct STRU_COMMENT_PUBLISH_RS{
    STRU_COMMENT_PUBLISH_RS():type(_DEF_PACK_COMMENT_PUBLISH_RS),result(0),fileid(0){

    }
    PackType type;
    int result;
    int fileid;
}STRU_COMMENT_PUBLISH_RS;

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


typedef struct STRU_PLIKE_RQ{//上传
    STRU_PLIKE_RQ():type(_DEF_PACK_PLIKE_RQ),play(0),like(0),file_id(0),user_id(0){

    }
PackType type;
    int play;
    int like;
    int file_id;
    int user_id;
}STRU_PLIKE_RQ;

typedef struct STRU_PLIKE_RS{//返回播放量 点赞
    STRU_PLIKE_RS():type(_DEF_PACK_PLIKE_RS),play(0),like(0),file_id(0){

    }
    PackType type;
    int play;
    int like;
    int file_id;
}STRU_PLIKE_RS;


typedef struct File_Plike{

    int play;
    int like;
    int File_id;
}File_Plike;

//typedef struct STRU_RECOM_RQ{
//    STRU_RECOM_RQ(_DEF_PACK_GET_RECOM_RQ){

//    }
//PackType type;
//int user_id;
//}STRU_RECOM_RQ;

typedef struct STRU_RECOM_RQ{//上传
    STRU_RECOM_RQ():type(_DEF_PACK_GETRM_RQ),user_id(0){

    }
    PackType type;
    int user_id;
}STRU_RECOM_RQ;


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
