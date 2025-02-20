#ifndef CLOGIC_H
#define CLOGIC_H

#include"TCPKernel.h"
#include<list>
#include<iostream>
#include"credis.h"
using namespace std;
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
    //设置协议映射
    void setNetPackMap();

    void SendData( sock_fd clientfd, char*szbuf, int nlen )
    {
        m_pKernel->SendData( clientfd ,szbuf , nlen );
    }

    //注册
    void RegisterRq(sock_fd clientfd, char*szbuf, int nlen);
    //登录
    void LoginRq(sock_fd clientfd, char*szbuf, int nlen);
    //文件头
    void uploadRq(sock_fd clientfd, char*szbuf, int nlen);
    //发送文件块
    void block_upload(sock_fd clientfd, char*szbuf, int nlen);
    //下载请求处理
    void Download_RQ(sock_fd clientfd, char*szbuf, int nlen);
    //发布评论
    void Pub_Comment(sock_fd clientfd, char*szbuf, int nlen);
    //获取评论
    void Get_comment(sock_fd clientfd, char*szbuf, int nlen);
    //发送短信验证
    void Send_Sms(sock_fd clientfd, char*szbuf, int nlen);
    //用户播放喜欢上传
    void Count_Plke(sock_fd clientfd, char*szbuf, int nlen);
    //推荐获取请求
    void Get_recomm(sock_fd clientfd, char*szbuf, int nlen);
    //相似度计算
    double CountSmiliar(list<string>vals,list<string>val2s);
    //获取信息
    void sendInfo(int id);
    //获得信息
    void getInfo(int id,_friend_message* f_mes);
    //
    void addfriend(sock_fd clientfd, char*szbuf, int nlen);
    //
    void sendFriendrq(int id,sock_fd clientfd);
    /*******************************************/

private:
    TcpKernel* m_pKernel;
    CMysql * m_sql;
    Block_Epoll_Net * m_tcp;
    map<int,FileInfo*>m_mapFileinfo;

    CRedis* redis;
};

#endif // CLOGIC_H
