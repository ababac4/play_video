#ifndef CLOGIC_H
#define CLOGIC_H

#include"TCPKernel.h"
#include "credis.h"
#include"md5.h"

class CLogic
{
public:
    CLogic( TcpKernel* pkernel )
    {
        m_pKernel = pkernel;
        m_sql = pkernel->m_sql;
        m_tcp = pkernel->m_tcp;
        redis=new CRedis;
    }
public:
    int getNumber(){
        return 1000000000;
    }

    //设置协议映射
    void setNetPackMap();
    /************** 发送数据*********************/
    void SendData( sock_fd clientfd, char*szbuf, int nlen )
    {
        m_pKernel->SendData( clientfd ,szbuf , nlen );
    }
    /************** 网络处理 *********************/
    //注册
    void RegisterRq(sock_fd clientfd, char*szbuf, int nlen);
    //登录
    void LoginRq(sock_fd clientfd, char*szbuf, int nlen);
    //上传文件请求
    void deal_FileRq(sock_fd clientfd, char*szbuf, int nlen);
    //文件块上传
    void deal_ContentRq(sock_fd clientfd, char*szbuf, int nlen);
    //文件获取
    void deal_GetFileRq(sock_fd clientfd, char*szbuf, int nlen);
    //下载文件请求
    void deal_Download_file_Rq(sock_fd clientfd, char*szbuf, int nlen);
    // 文件头回复
    void deal_Download_file_Rs(sock_fd clientfd, char*szbuf, int nlen);
    //文件内容回复
    void deal_ContentRs(sock_fd clientfd, char*szbuf, int nlen);
    //添加文件夹
    void deal_addFolder(sock_fd clientfd, char*szbuf, int nlen);
    //分享文件
    void deal_ShareRq(sock_fd clientfd, char*szbuf, int nlen);
    //
    void share_insert(int fileid,int userid,string dir,string time,int link);
    //获取分享信息
    void deal_GetShareInfo(sock_fd clientfd, char*szbuf, int nlen);
    //分享链接处理
    void deal_ShareLink_Rq(sock_fd clientfd, char*szbuf, int nlen);
    void insert_file(int uid,int fid,string dir,string name,string time);
    void insert_folder(int uid,int fid,string dir,string name,string time,int fromuserid,string fromdir);
    //
    void deal_DownFolderRq(sock_fd clientfd, char*szbuf, int nlen);
    void DownloadFile(int userid,int &timestamp,sock_fd clientfd,list<string>&lstres);
    void DownloadFolder(int userid,int &timestamp,sock_fd clientfd,list<string>&lstres);
    //
    void deal_dealFileRq(sock_fd clientfd, char*szbuf, int nlen);
    void deleteOneItem(int userid,int f_id,string dir);
    void deleteFIle(int u_id, int f_id, string dir, string path);
    void deleteFolder(int u_id, int f_id, string dir, string name);
    //
    void deal_Continue_Down_Rq(sock_fd clientfd, char*szbuf, int nlen);
    //
    void deal_Continue_Upload_Rq(sock_fd clientfd, char*szbuf, int nlen);
    //获取信息
    void sendInfo(int id);
    //获得信息
    void getInfo(int id,_friend_message* f_mes);
    //
    void addfriend(sock_fd clientfd, char*szbuf, int nlen);
    //
    void sendFriendrq(int id,sock_fd clientfd);
    //发送短信验证
    void Send_Sms(sock_fd clientfd, char*szbuf, int nlen);

    void deal_chatRq(sock_fd clientfd, char*szbuf, int nlen);
    //
    void deal_addRs(sock_fd clientfd, char*szbuf, int nlen);
private:
    TcpKernel* m_pKernel;
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;
    CRedis*redis;
   MyMap<int64_t,FileInfo*>m_mapIdToInfo;
   MD5 *md5;
};

#endif // CLOGIC_H
