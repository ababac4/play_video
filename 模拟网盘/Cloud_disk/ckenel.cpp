#include "ckenel.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>
#include<QDebug>
#include"TcpClientMediator.h"
#include<QMessageBox>
#include<iostream>
#include<QDateTime>
#include<QFileInfo>
#include<QThread>
#include<QRandomGenerator>
#include <QCoreApplication>
#include <QCryptographicHash>
#include <QByteArray>
#include <QDebug>

using namespace std;
static string getMD5(QString val);
static string getFileMD5(QString name);

//gb2312 转 QString
QString Ckenel::gbtoutf(char *str)
{
QTextCodec *dec=QTextCodec::codecForName("gb2312");
return dec->toUnicode(str);
}

void Ckenel::utftogb(QString csv, char *dst, int len)
{
QTextCodec *dec=QTextCodec::codecForName("gb2312");
QByteArray arr=dec->fromUnicode(csv);
strcpy_s(dst,len,arr.data());
}
Ckenel::Ckenel(QObject *parent) : QObject(parent)
{

    isEnd=false;
    m_sql=new CSqlite;
    m_cur_dir="/";
    m_wind=new MainWindow;
    Tcpclient=new TcpClientMediator;
    m_wind->show();
    dio=new LoginDialog;
    initpFUN();
    loadinfo();//加载配置文件
    md5=new MD5;
    friend_list=new friendlist;
    Tcpclient->OpenNet("192.168.183.130");
    default_Path();

        QString digits = "0123456789";
        QString randomString;

        // 生成16个随机数字并拼接到QString中
        for (int i = 0; i < 16; ++i) {
            int randomIndex = QRandomGenerator::global()->bounded(digits.length());
            randomString.append(digits[randomIndex]);
        }

        // 转换为std::string，如果需要的话

        std::string plaintext = randomString.toStdString();
     MY_KEY m_key;
     sprintf(m_key.KEY,plaintext.c_str());

   Tcpclient->SendData(0,(char*)&m_key,sizeof(m_key));
    connect(dio,SIGNAL(sig_close_dio()),this,SLOT(slot_close_dio()));
    connect(Tcpclient,SIGNAL(SIG_ReadyData(unsigned int, char*, int)),this,SLOT(slot_client_data( unsigned int, char*, int)));
    connect(m_wind,SIGNAL(sig_register(QString,QString,QString,QString)),this,SLOT(slot_register(QString,QString,QString,QString)));
    connect(m_wind,SIGNAL(sig_login(QString,QString)),this,SLOT(slot_login(QString,QString)));
    connect(dio,SIGNAL(sig_send_upInfo(QString, QString)),this,SLOT(slot_send_upInfo(QString, QString)));
    connect(this,SIGNAL(sig_uploadProgess(int,int)),dio,SLOT(slot_uploadProgess(int,int)));
    connect(dio,SIGNAL(sig_download_file(int,QString)),this,SLOT(slot_download_file(int,QString)));
    connect(dio,SIGNAL(sig_download_folder(int,QString)),this,SLOT(slot_download_folder(int,QString)));
    connect(this,SIGNAL(sig_DownloadProgess(int,int)),dio,SLOT(slot_DownloadProgess(int,int)));
    connect(dio,SIGNAL(sig_add_Folder(QString, QString)),this,SLOT(slot_add_Folder(QString, QString)));
    connect(dio,SIGNAL(sig_changDir(QString)),this,SLOT(slot_changDir(QString)));
    connect(dio,SIGNAL(sig_upload_folder(QString,QString)),this,SLOT(slot_upload_folder(QString,QString)));
    connect(dio,SIGNAL(sig_share_info(QVector<int>,QString)),this,SLOT(slot_share_info(QVector<int>,QString)));
    connect(dio,SIGNAL(sig_Send_Link(QString,int)),this,SLOT(slot_Send_Link(QString,int)));
    connect(dio,SIGNAL(sig_delete_file(QVector<int>,QString)),this,SLOT(slot_delete_file(QVector<int>,QString)));


    connect(dio,SIGNAL(sig_down_attr(int,int)),this,SLOT(slot_down_attr(int,int)));
    connect(dio,SIGNAL(sig_up_attr(int,int)),this,SLOT(slot_up_attr(int,int)));
    connect(m_wind,SIGNAL(sig_sendSms(QString)),this,SLOT(slot_sendSms(QString)));




    connect(friend_list,SIGNAL(sig_addFriend()),this,SLOT(slot_addfriend()));
}
#include<QTextCodec>

// QString -> char* gb2312
void Utf8ToGB2312( char* gbbuf , int nlen ,QString& utf8)
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    QByteArray ba = gb2312code->fromUnicode( utf8 );// Unicode -> 转码对象的字符集

    strcpy_s ( gbbuf , nlen , ba.data() );
}

// char* gb2312 --> QString utf8
QString GB2312ToUtf8( char* gbbuf )
{
    //转码的对象
    QTextCodec * gb2312code = QTextCodec::codecForName( "gb2312");
    //QByteArray char 类型数组的封装类 里面有很多关于转码 和 写IO的操作
    return gb2312code->toUnicode( gbbuf );// 转码对象的字符集 -> Unicode
}

Ckenel::~Ckenel(){

}

void Ckenel::slot_close_dio()
{
    delete m_wind;
    delete dio;
    isEnd=true;
    Tcpclient->CloseNet();
}


void Ckenel::initpFUN(){
    funarr[_DEF_PACK_REGISTER_RS]=&Ckenel::dealRegisterRS;
    funarr[_DEF_PACK_LOGIN_RS]=&Ckenel::dealLoginRS;
    funarr[_DEF_PACK_UPLOAD_FILE_RS]=&Ckenel::dealUploadRs;
    funarr[_DEF_PACK_FILE_CONTENT_RS]=&Ckenel::dealContentRs;
    funarr[_DEF_PACK_GETINFO_RS]=&Ckenel::deal_GetInfo;
    funarr[_DEF_PACK_FILE_HEADER_RQ]=&Ckenel::deal_Download_FileHeadRq;
    funarr[_DEF_PACK_FILE_CONTENT_RQ]=&Ckenel::deal_download_ContentRq;
    funarr[_DEF_PACK_ADD_FOLDER_RS]=&Ckenel::deal_mkdirRS;
    funarr[_DEF_PACK_QUICK_UPLOAD_RS]=&Ckenel::deal_Quick_Rs;
    funarr[_DEF_PACK_SHARE_FILE_RS]=&Ckenel::deal_share_Rs;
    funarr[_DEF_PACK_MY_SHARE_RS]=&Ckenel::deal_GetShareRS;
    funarr[_DEF_PACK_GET_SHARE_RS]=&Ckenel::deal_Link_Rs;
    funarr[_DEF_PACK_FOLDER_HEADER_RQ]=&Ckenel::deal_addfolder;
    funarr[_DEF_PACK_DELETE_FILE_RS]=&Ckenel::deal_deleteFileRs;
    funarr[_DEF_PACK_CONTINUE_UPLOAD_RS]=&Ckenel::deal_Upload_Conrq;
    funarr[_DEF_FRIEND_INFO]=&Ckenel::dealfriend_Info;
    funarr[_DEF_ADD_FRIEND_RS]=&Ckenel::dealaddfriend;
    funarr[_DEF_ADD_FRIEND_RQ]=&Ckenel::recv_friendRQ;
    funarr[_DEF_PACK_CHAT_RQ]=&Ckenel::deal_chatRq;
    funarr[_DEF_PACK_CHAT_RS]=&Ckenel::dealRS;
}

void Ckenel::loadinfo()
{

    QString path=QCoreApplication::applicationDirPath()+"/config.ini";

    m_ip="192.168.183.130";
    m_port="8020";
    QFileInfo file(path);
    if(file.exists()){
        QSettings set(path,QSettings::IniFormat);//不存在创建文件 否则直接读取
        set.beginGroup("net");
        QVariant g_ip=set.value("ip","");
        QVariant g_port=set.value("port","");
        if(!g_ip.toString().isEmpty()) m_ip=g_ip.toString();
        if(!g_port.toString().isEmpty()) m_port=g_port.toString();

    }else{
        QSettings set(path,QSettings::IniFormat);//不存在创建文件
        //打开组
        set.beginGroup("net");
        set.setValue("ip",m_ip);
        set.setValue("port",m_port);
        //关闭组
        set.endGroup();
    }

}
void Ckenel::dealfriend_Info(unsigned int lSendIP, char *buf, int nlen)
{
cout<<__func__<<endl;
_friend_message info=*(_friend_message*)buf;
cout<<__func__<<endl;
if(info.id==m_userid){
    cout<<info.id<<' '<<info.name<<' '<<info.iconid<<endl;
    dio->setCoin(info.iconid);
    m_username=QString::fromStdString(info.name);
    friend_list->setUserinfo(info.name,info.feeling,info.iconid);
return;
}

  cout<<"info_id:"<<info.id<<endl;
if(m_useritem.count(info.id)>0){

m_useritem[info.id]->setFrientItem(info.id,info.name,info.feeling,info.iconid);
}else{
 useritem *item=new useritem;
 item->setFrientItem(info.id,info.name,info.feeling,info.iconid);;
m_useritem[info.id]=item;
 friend_list->addfriend(item);
 connect(item,SIGNAL(sig_sendid(int)),this,SLOT(slot_sendid(int)));
 chatdiolog* chat=new chatdiolog;
 chat->setChatdio(info.name,info.id);
 m_chatdio[info.id]=chat;
 connect(chat,SIGNAL(sig_sendChatinfo(QString,int)),this,SLOT(slot_sendChatinfo(QString,int)));
}

}
void Ckenel::recv_friendRQ(unsigned int lSendIP, char *buf, int nlen)
{
    _addfriend_RQ rq=*(_addfriend_RQ*)buf;
    cout<<__func__<<rq.my_id<<' '<<rq.my_name<<endl;
    if(m_friendRQ.count(rq.my_id)>0){
        addfridio* temp=m_friendRQ[rq.my_id];
    }else{
        addfridio* temp=new addfridio;
        temp->setInfo(rq.my_id,rq.my_name);
        friend_list->addfriendrq(temp);
        m_friendRQ[rq.my_id]=temp;
        connect(temp,SIGNAL(sig_addrs(int,int)),this,SLOT(slot_addrs(int,int)));
    }

}

void Ckenel::deal_chatRq(unsigned int lSendIP, char *buf, int nlen)
{
STRU_CHAR_RQ rq=*(STRU_CHAR_RQ*)buf;
cout<<__func__<<endl;
if(m_chatdio.count(rq.my_id)>0)
{
    chatdiolog *chatdio=m_chatdio[rq.my_id];
    WriteLog::GetInstance()->Write_log(0,rq.content);

    local_content*con=new local_content;
    con->p_id=rq.my_id;
    con->id=rq.friendid;
    con->name=chatdio->name();
    con->content=QString::fromUtf8(rq.content);
    con->time=QTime::currentTime().toString("hh::mm::ss");
    chatdio->setFrichat(rq.content);
    slot_writeContent(con);
    chatdio->showNormal();//弹出
}

}
void Ckenel::slot_sendChatinfo(QString content,int id){
    STRU_CHAR_RQ chatRq;
   chatRq.my_id=m_userid;
    chatRq.friendid=id;
    local_content*con=new local_content;
    con->p_id=id;
    con->id=m_userid;
    con->name=m_chatdio[id]->name();
    con->content=content;
    con->time=QTime::currentTime().toString("hh::mm::ss");
    slot_writeContent(con);
    sprintf(chatRq.content,content.toStdString().c_str());
    cout<<chatRq.content<<endl;
   Tcpclient->SendData(0,(char*)&chatRq,sizeof(chatRq));

}
#include<QCoreApplication>
#include<QDir>
#include <QInputDialog>
void Ckenel::default_Path()
{

QString path=QCoreApplication::applicationDirPath()+"/NetDisk";
QDir dir;
if(!dir.exists(path)){
    dir.mkdir(path);//创建一层
}
m_path=path;
}

void Ckenel::slot_sendid(int id)
{
     m_chatdio[id]->cleartd();
    for(auto i:chat_con){
        if(i->p_id==id) {
            qDebug()<<i->name<<i->time;
            m_chatdio[id]->setContent(i->name,i->id,i->time,i->content);
        }
    }
 m_chatdio[id]->showNormal();
}
void Ckenel::slot_addfriend()
{
    cout<<__func__<<endl;
    QString name=QInputDialog::getText(friend_list,"添加好友","好友姓名");
    QString temname=name;
    qDebug()<<name;

    if(temname.isEmpty()||temname.remove(" ").isEmpty())
    {
        QMessageBox::about(friend_list,"提示","内容不能为空或者空格");
        return;
    }
    //是否是自己
    if(name==m_username){
        QMessageBox::about(friend_list,"提示","内容不能为自己");
        return;
    }
    //好友是否已添加
    for(auto item:m_useritem)
    {
        QString friname=item.second->name();
        if(friname==name)
        {
             QMessageBox::about(friend_list,"提示","内容不能为已添加好友");
             return;
        }
    }
    _addfriend_RQ re;
     strcpy_s(re.friend_name,sizeof (re.friend_name),name.toStdString().c_str());
      strcpy_s(re.my_name,sizeof(re.my_name),m_username.toStdString().c_str());
      re.my_id=m_userid;
      Tcpclient->SendData(0,(char*)&re,sizeof(re));
}
void Ckenel::dealRegisterRS(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    STRU_REGISTER_RS rs=*(STRU_REGISTER_RS*)buf;
    if(rs.result==tel_is_exist){
        QMessageBox::about(m_wind,"提示","手机号已存在");
    }else if(rs.result==user_is_exist){
        QMessageBox::about(m_wind,"提示","用户名已存在");
    }else if(rs.result==register_success){
        QMessageBox::about(m_wind,"提示","注册成功");
    }else if(rs.result==sms_empire){
        QMessageBox::about(m_wind,"提示","短信过期");
    }else if(rs.result==sms_wrong){
      QMessageBox::about(m_wind,"提示","短信输入错误");
    }
}

void Ckenel::dealLoginRS(unsigned int lSendIP, char *buf, int nlen)
{

cout<<__func__<<endl;
  STRU_LOGIN_RS rs=*(STRU_LOGIN_RS*)buf;
  if(rs.result==user_not_exist){
      QMessageBox::about(m_wind,"提示","用户不存在");
      WriteLog::GetInstance()->Write_log(1,"用户不存在");
  }else if(rs.result==password_error){
      QMessageBox::about(m_wind,"提示","密码错误");
      WriteLog::GetInstance()->Write_log(1,"密码错误");
  }else if(rs.result==login_success){
      m_userid=rs.userid;
      WriteLog::GetInstance()->Write_log(0,"登录成功");
      slot_Get_File_Info();

      Initsql(rs.userid);
      dio->show();
      m_wind->hide();

  }
}

void Ckenel::dealUploadRs(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    STRU_UPLOAD_FILE_RS rs=*(STRU_UPLOAD_FILE_RS*)buf;

    if(!rs.result){
        qDebug()<<"upload fail";
        WriteLog::GetInstance()->Write_log(1,"upload fail");
        return;
    }
    if(m_mapTimeStampinfo.find(rs.timestamp)==m_mapTimeStampinfo.end()){
        qDebug()<<"not found";
        WriteLog::GetInstance()->Write_log(1,"not found");
        return;
    }

    FileInfo *info=m_mapTimeStampinfo[rs.timestamp];
    info->fileid=rs.fileid;
  //插入上传信息->控件
    slot_writeUpload(info);//存入sqlite中
    dio->slot_insertFile(info);
    STRU_FILE_CONTENT_RQ rq;
    rq.fileid=rs.fileid;
    rq.timestamp=rs.timestamp;
    rq.userid=rs.userid;
    int len=fread(rq.content,1,_DEF_BUFFER,info->pFile);
    rq.len=len;
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

}

void Ckenel::dealContentRs(unsigned int lSendIP, char *buf, int nlen)
{


    STRU_FILE_CONTENT_RS rs=*(STRU_FILE_CONTENT_RS*)buf;
    if(m_mapTimeStampinfo.find(rs.timestamp)==m_mapTimeStampinfo.end()){
        qDebug()<<"not found";
        return;
    }
    FileInfo *info=m_mapTimeStampinfo[rs.timestamp];
    while(info->isPause){
        QThread::msleep(100);
        //暂停，后台挂起进程
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);

        if(isEnd) return;


    }
    if(!rs.result){//写错误，重新发 return
        fseek(info->pFile,-1*rs.len,SEEK_CUR);
    }else{
        info->pos+=rs.len;
        //更新上传进度
        //cout<<info->size<<' '<<info->pos<<endl;
        Q_EMIT sig_uploadProgess(info->timestamp,info->pos);
        if(info->pos>=info->size){
            //删除
            dio->slot_delete_ALL();
            slot_deleteUpload(info);
            //更新文件信息
            slot_Get_File_Info();
            qDebug()<<"上传成功";

            WriteLog::GetInstance()->Write_log(0,"上传成功");
            m_mapTimeStampinfo.erase(rs.timestamp);
            delete info;
            info=nullptr;
            return;
        }
    }
    STRU_FILE_CONTENT_RQ rq;

    rq.fileid=rs.fileid;
    rq.timestamp=rs.timestamp;
    rq.userid=rs.userid;
    rq.len=fread(rq.content,1,_DEF_BUFFER,info->pFile);
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

}

void Ckenel::deal_GetInfo(unsigned int lSendIP, char *buf, int nlen)
{
    cout<<__func__<<endl;
    STRU_GET_INFO_RS *rs=(STRU_GET_INFO_RS*)buf;

  if(m_cur_dir!=QString::fromStdString(rs->dir)) return;
    cout<<rs->count<<endl;
    int count=rs->count;
    //再删一次
    dio->slot_delete_ALL();
    for(int i=0;i<count;i++){
        FileInfo *info=new FileInfo;


        info->rtmp=QString::fromStdString(rs->info_arr[i].rtmp);
        qDebug()<<info->rtmp;
        info->name=QString::fromStdString(rs->info_arr[i].name);
        info->time=QString::fromStdString(rs->info_arr[i].time);
        info->type=QString::fromStdString(rs->info_arr[i].fileType);
        info->fileid=rs->info_arr[i].fileid;

        info->size=rs->info_arr[i].size;

        dio->slot_insertInfo(info);

    }

}
void Ckenel::dealRS(unsigned int lSendIP, char *buf, int nlen)
{
    cout<<__func__<<endl;
STRU_CHAR_RS rs=*(STRU_CHAR_RS*)buf;

if(m_chatdio.count(rs.friendid)>0)
{
    chatdiolog *chatdio=m_chatdio[rs.friendid];
   chatdio->setFrichat("好友不在线");
   WriteLog::GetInstance()->Write_log(0,"not online");
}

}
void Ckenel::deal_Download_FileHeadRq(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
    STRU_FILE_HEADER_RQ rq=*(STRU_FILE_HEADER_RQ*)buf;
    FileInfo *info=new FileInfo;
    //路径创建
    QString tempDir=QString::fromStdString(rq.dir);
    QStringList m_list=tempDir.split("/");
    QString m_dir=m_path;
    for(auto& i:m_list){
        if(!i.isEmpty()){
        m_dir+="/";
        m_dir+=i;
        QDir dir;
        if(!dir.exists(m_dir)){
            dir.mkdir(m_dir);
        }

        }
    }

    info->absolutePath=QString("%1%2%3").arg(m_path).arg(rq.dir).arg(rq.fileName);
    info->dir=QString::fromStdString(rq.dir);
    info->name=QString::fromStdString(rq.fileName);
    info->fileid=rq.fileid;
    info->md5=QString::fromStdString(rq.md5);
    info->size=rq.size;

    info->timestamp=rq.timestamp;
    info->type=QString::fromStdString(rq.fileType);
    info->pFile=fopen(info->absolutePath.toStdString().c_str(),"wb");
    qDebug()<<info->absolutePath;
    if(!info->pFile){
        qDebug()<<"open file wrong";
        return;
    }

    info->time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    //下载文件头接受
    dio->slot_DownloadInfo(info);
    slot_writeDown(info);

    m_mapTimeStampinfo[info->timestamp]=info;
    STRU_FILE_HEADER_RS rs;
    rs.fileid=rq.fileid;
    rs.result=1;//接收回复 可发数据进行偏移
    rs.timestamp=rq.timestamp;
    rs.userid=m_userid;

    Tcpclient->SendData(0,(char*)&rs,sizeof(rs));

}

void Ckenel::deal_download_ContentRq(unsigned int lSendIP, char *buf, int nlen)
{
     //qDebug()<<__func__;
     //写文件内容
      STRU_FILE_CONTENT_RQ rq=*(STRU_FILE_CONTENT_RQ*)buf;
      FileInfo *info;
      if(m_mapTimeStampinfo.find(rq.timestamp)==m_mapTimeStampinfo.end()){
          qDebug()<<"find download wrong";
           WriteLog::GetInstance()->Write_log(1,"find download wrong");
          return;
      }

        STRU_FILE_CONTENT_RS rs;
      info=m_mapTimeStampinfo[rq.timestamp];

      while(info->isPause){
          QThread::msleep(100);
          QCoreApplication::processEvents(QEventLoop::AllEvents,100);
          if(isEnd) return;
      }
      int len=fwrite(rq.content,1,rq.len,info->pFile);
     //读取错误更新偏移
      if(len!=rq.len){
            rs.result=0;
            fseek(info->pFile,-1*len,SEEK_CUR);
      }else{

          rs.result=1;
          info->pos+=len;
          Q_EMIT sig_DownloadProgess(info->timestamp,info->pos);
          //读完
          if(info->pos>=info->size){
              qDebug()<<"download success";

              slot_deleteDown(info);
             fclose(info->pFile);
             m_mapTimeStampinfo.erase(rq.timestamp);
             delete info;
             info=nullptr;
             return;
          }

      }

     //返回读取结果
      rs.fileid=rq.fileid;
      rs.len=rq.len;
      rs.timestamp=rq.timestamp;
      rs.userid=m_userid;

      Tcpclient->SendData(0,(char*)&rs,sizeof(rs));
}

void Ckenel::deal_mkdirRS(unsigned int lSendIP, char *buf, int nlen)
{

    STRU_ADD_FOLDER_RS rs=*(STRU_ADD_FOLDER_RS*)buf;
    if(!rs.result){
        qDebug()<<"文件夹创建失败";
        WriteLog::GetInstance()->Write_log(1,"文件夹创建失败");
        return;
    }

    //删除
    dio->slot_delete_ALL();

    //更新文件信息
    slot_Get_File_Info();

}

void Ckenel::deal_Quick_Rs(unsigned int lSendIP, char *buf, int nlen)
{
STRU_QUICK_UPLOAD_RS rs=*(STRU_QUICK_UPLOAD_RS*)buf;
FileInfo *info;
if(!rs.result) return;
if(m_mapTimeStampinfo.count(rs.timestamp)==0) return;
info=m_mapTimeStampinfo[rs.timestamp];
if(!info->pFile) pclose(info->pFile);

if(info->dir==m_cur_dir){
    dio->slot_delete_ALL();
    slot_Get_File_Info();

}
m_mapTimeStampinfo.erase(rs.timestamp);
delete info;
info=nullptr;

}

void Ckenel::deal_share_Rs(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
STRU_SHARE_FILE_RS rs=*(STRU_SHARE_FILE_RS*)buf;
if(rs.result!=1) return;


}

void Ckenel::deal_GetShareRS(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_MY_SHARE_RS* rs=(STRU_MY_SHARE_RS*)buf;
    qDebug()<<rs->itemCount;
    for(int i=0;i<rs->itemCount;i++){
        //qDebug()<<rs->items[i].name<<' '<<rs->items[i].shareLink<<' '<<rs->items[i].size<<' '<<rs->items[i].time;
        char buf[1024]="";
        sprintf(buf,"%s,%s,%d,%d",rs->items[i].name,rs->items[i].time,rs->items[i].shareLink,rs->items[i].size);
        WriteLog::GetInstance()->Write_log(0,buf);
        dio->slot_insertShareInfo(rs->items[i].name,rs->items[i].size,rs->items[i].time,rs->items[i].shareLink);
    }
}

void Ckenel::deal_Link_Rs(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_GET_SHARE_RS rs=*(STRU_GET_SHARE_RS*)buf;
    if(!rs.result) return;
    else{
        qDebug()<<rs.dir<<' '<<rs.result;
        if(QString(rs.dir)==m_cur_dir){
            //更新
           slot_Get_File_Info();

        }
    }

}

void Ckenel::deal_addfolder(unsigned int lSendIP, char *buf, int nlen)
{
STRU_FOLDER_HEADER_RQ rq=*(STRU_FOLDER_HEADER_RQ*)buf;
QString tempDir=QString::fromStdString(rq.dir);
QStringList m_list=tempDir.split("/");
QString m_dir=m_path;
for(auto& i:m_list){
    if(!i.isEmpty()){
    m_dir+="/";
    m_dir+=i;
    QDir dir;
    if(!dir.exists(m_dir)){
        dir.mkdir(m_dir);
    }
    }
}

m_dir+="/";
m_dir+=QString::fromStdString(rq.fileName);
QDir dir;
if(!dir.exists(m_dir)){
    dir.mkdir(m_dir);
}

}

void Ckenel::deal_deleteFileRs(unsigned int lSendIP, char *buf, int nlen)
{
STRU_DELETE_FILE_RS rs=*(STRU_DELETE_FILE_RS*)buf;
if(!rs.result) return;

dio->slot_delete_ALL();
slot_Get_File_Info();

}

void Ckenel::deal_Upload_Conrq(unsigned int lSendIP, char *buf, int nlen)
{

    STRU_CONTINUE_UPLOAD_RS rs=*(STRU_CONTINUE_UPLOAD_RS*)buf;
    cout<<rs.pos<<' '<<rs.fileid<<endl;
    FileInfo*info;
    info=m_mapTimeStampinfo[rs.timestamp];
    if(!info->pFile) return;
    qDebug()<<info->name;

    fseek(info->pFile,rs.pos,SEEK_SET);
    info->pos=rs.pos;
    Q_EMIT sig_uploadProgess(info->timestamp,info->pos);

    STRU_FILE_CONTENT_RQ rq;

    rq.fileid=rs.fileid;
    rq.timestamp=rs.timestamp;
    rq.userid=m_userid;
    rq.len=fread(rq.content,1,_DEF_BUFFER,info->pFile);
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

   // Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

}

void Ckenel::slot_Get_sharelist()
{
    dio->clearshare();
    qDebug()<<__func__;
STRU_MY_SHARE_RQ rq;

rq.userid=m_userid;

Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
}

void Ckenel::slot_Send_Link(QString dir,int code)
{

STRU_GET_SHARE_RQ rq;
string m_dir=dir.toStdString();
strcpy(rq.dir,m_dir.c_str());
rq.userid=m_userid;
rq.shareLink=code;
string time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
strcpy(rq.time,time.c_str());

Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

}

void Ckenel::slot_delete_file(QVector<int> res, QString dir)
{
   qDebug()<<__func__;
   int count=res.size();
   int packsize=sizeof(STRU_DELETE_FILE_RQ)+sizeof(int)*count;
   STRU_DELETE_FILE_RQ *rq=(STRU_DELETE_FILE_RQ*)malloc(packsize);
   rq->init();
   rq->userid=m_userid;
   string m_dir=dir.toStdString().c_str();
   strcpy(rq->dir,m_dir.c_str());
   rq->fileCount=count;

   for(int i=0;i<count;i++){
       rq->fileidArray[i]=res[i];
   }

   Tcpclient->SendData(0,(char*)rq,packsize);
}

void Ckenel::slot_down_attr(int timestamp, int result)
{
    if(m_mapTimeStampinfo.count(timestamp)==0){


    FileInfo *info=dio->slot_getInfoBytime(timestamp);
    char buf[1024]="";
    Utf8ToGB2312(buf,1024,info->absolutePath);
    //追加
    info->pFile=fopen(buf,"ab");
    if(!info->pFile){
        return;
    }
    info->isPause=result;

    m_mapTimeStampinfo[timestamp]=info;
    STRU_CONTINUE_DOWNLOAD_RQ rq;
    strcpy(rq.dir,info->dir.toStdString().c_str());
    rq.fileid=info->fileid;
    rq.pos=info->pos;
    rq.userid=m_userid;
    rq.timestamp=timestamp;
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

    }else{
    FileInfo* info=m_mapTimeStampinfo[timestamp];
    info->isPause=result;
    }
}

void Ckenel::slot_up_attr(int timestamp, int result)
{
    if(m_mapTimeStampinfo.count(timestamp)==0){
    //断点续传
        cout<<__func__<<endl;
        STRU_CONTINUE_UPLOAD_RQ rq;
         FileInfo *info=dio->slot_getUpInfoBytime(timestamp);
         if(!info) return;
         char buf[1024]="";
         Utf8ToGB2312(buf,1024,info->absolutePath);
         //追加
            cout<<buf<<endl;
            info->pFile=fopen(buf,"rb");
            if(!info->pFile){
                return;
            }

         info->isPause=0;
         m_mapTimeStampinfo[timestamp]=info;


        strcpy(rq.dir,info->dir.toStdString().c_str());
         rq.fileid=info->fileid;
         rq.timestamp=timestamp;
         rq.userid=m_userid;
         Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
    }
    else{
    FileInfo* info=m_mapTimeStampinfo[timestamp];
    info->isPause=result;
    }
}


void Ckenel::slot_client_data( unsigned int lSendIP , char* buf , int nlen ){

    PackType type = *(PackType*)buf;
    //qDebug()<<__func__;
    if( (type >= _DEF_PACK_BASE) && ( type < _DEF_PACK_BASE + _DEF_PACK_COUNT) )
    {
        PFUN pf = funarr[type];
        if(pf){
            (this->*pf)(lSendIP,buf,nlen);
        }
    }
    delete[] buf;

}

void Ckenel::slot_register(QString phone,QString name,QString password,QString duan){
    qDebug()<<__func__;
    STRU_REGISTER_RQ reg;
    //装包
    strcpy_s(reg.name,name.toStdString().c_str());
    strcpy_s(reg.tel,phone.toStdString().c_str());
    strcpy_s(reg.password,getMD5(password).c_str());
    strcpy_s(reg.sms,duan.toStdString().c_str());
    string md=getMD5(password);
    cout<<reg.tel<<' '<<reg.name<<' '<<reg.password<<endl;

    Tcpclient->SendData(0,(char*)&reg,sizeof(reg));

}
void Ckenel::slot_login(QString phone,QString password){

    qDebug()<<__func__;
    STRU_LOGIN_RQ login;
    //装包
    strcpy_s(login.password,getMD5(password).c_str());
    strcpy_s(login.tel,phone.toStdString().c_str());


    Tcpclient->SendData(0,(char*)&login,sizeof(login));
}

//上传文件槽函数
void Ckenel::slot_send_upInfo(QString name, QString dir)
{

    QFileInfo Qinfo(name);
    QString filename=Qinfo.fileName();
    QByteArray bt=filename.right(filename.length()-filename.lastIndexOf('.')-1).toLatin1();//取文件后缀

    FileInfo *info=new FileInfo;
    info->md5=QString::fromStdString(getFileMD5(name));
    info->absolutePath=name;
    info->dir=dir;
    string m_filename=bt.data();
    if(m_filename=="flv") info->type="flv";
    else if(m_filename=="mp4") info->type="mp4";
    else if(m_filename=="pdf") info->type="pdf";
    else info->type="file";
    info->name=Qinfo.fileName();
    info->size=Qinfo.size();
    info->time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    char buf[10000]="";
    Utf8ToGB2312(buf,1000,info->absolutePath);
    int timestmp=QDateTime::currentDateTime().toString("hhmmsszzz").toInt();
    //timestamp冲突
    while(m_mapTimeStampinfo.count(timestmp)>0){
        timestmp++;
    }
    info->timestamp=timestmp;

    info->pFile=fopen(buf,"rb");//二进制只读
    if(!info->pFile){
        qDebug()<<"open wrong";
        return;
    }

//使用时间戳存入map中，防止上传相同文件导致进度不一致
    m_mapTimeStampinfo[timestmp]=info;
    //装包发送文件请求 将文件信息发送
    STRU_UPLOAD_FILE_RQ rq;

    strcpy(rq.dir,info->dir.toStdString().c_str());
    strcpy(rq.fileName,info->name.toStdString().c_str());
    strcpy(rq.md5,info->md5.toStdString().c_str());
    rq.size=info->size;
    strcpy(rq.time,info->time.toStdString().c_str());

    strcpy(rq.fileType,info->type.toStdString().c_str());
    rq.timestamp=timestmp;
    rq.userid=m_userid;
   cout<<rq.fileType<<endl;
  Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

}

//获取文件信息请求
void Ckenel::slot_Get_File_Info()
{
    cout<<__func__<<endl;
STRU_GET_INFO_RQ rq;

rq.user_id=m_userid;
string dir=m_cur_dir.toStdString();
strcpy(rq.dir,dir.c_str());
Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

}

void Ckenel::slot_download_file(int file_id, QString dir)
{
    qDebug()<<__func__;
    STRU_DOWNLOAD_FILE_RQ rq;

    strcpy(rq.dir,dir.toStdString().c_str());
    rq.fileid=file_id;

   int timestmp=QDateTime::currentDateTime().toString("hhmmsszzz").toInt();

   //timestamp冲突
   while(m_mapTimeStampinfo.count(timestmp)>0){
       timestmp++;
   }
   rq.timestamp=timestmp;
   rq.userid=m_userid;

   Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
}

void Ckenel::slot_download_folder(int file_id, QString dir)
{
    qDebug()<<__func__;


    STRU_DOWNLOAD_FOLDER_RQ rq;
    string m_dir=dir.toStdString();
    strcpy(rq.dir,m_dir.c_str());
    rq.userid=m_userid;
    rq.fileid=file_id;

    int timestmp=QDateTime::currentDateTime().toString("hhmmsszzz").toInt();

    //防止timestamp冲突
    while(m_mapTimeStampinfo.count(timestmp)>0){
        timestmp++;
    }

    rq.timestamp=timestmp;
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));


}

void Ckenel::slot_add_Folder(QString path, QString dir)
{
    STRU_ADD_FOLDER_RQ rq;
    string m_dir=dir.toStdString();
    strcpy(rq.dir,m_dir.c_str());
    string name=path.toStdString();
    strcpy(rq.fileName,name.c_str());
    string time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
    strcpy(rq.time,time.c_str());
    rq.timestamp=QDateTime::currentDateTime().toString("hhmmsszzz").toInt();
    rq.userid=m_userid;

    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));

}

void Ckenel::slot_changDir(QString dir)
{
    m_cur_dir=dir;

    //删除
    dio->slot_delete_ALL();
    //更新文件信息
    slot_Get_File_Info();
}

void Ckenel::slot_upload_folder(QString path, QString dir)
{
    qDebug()<<__func__;
     QFileInfo info(path);//获取文件名字
     QDir dr(path);
    slot_add_Folder(info.fileName(),dir);
     QFileInfoList lst=dr.entryInfoList();

     QString newDir=dir+info.fileName()+"/";

     for(int i=0;i<lst.size();i++){

          QFileInfo file=lst.at(i);
          if(file.fileName()==".") continue;
          if(file.fileName()=="..") continue;
          //文件，发送 +拼接路径
          if(file.isFile()){
              slot_send_upInfo(file.absoluteFilePath(),newDir);

          }
          //递归 传文件夹 +当前路径
          if(file.isDir()){
              slot_upload_folder(file.absoluteFilePath(),newDir);
          }

     }

}

void Ckenel::slot_share_info(QVector<int> res, QString dir)
{

   int pasize=sizeof(STRU_SHARE_FILE_RQ)+sizeof(int)*res.size();
   STRU_SHARE_FILE_RQ *rq=(STRU_SHARE_FILE_RQ*)malloc(pasize);
   rq->init();
   rq->itemCount=res.size();
   for(int i=0;i<rq->itemCount;i++){
       rq->fileidArray[i]=res[i];
       cout<<"shareid:"<<' '<< rq->fileidArray[i]<<endl;
   }
   string path=dir.toStdString();
   strcpy(rq->dir,path.c_str());
   rq->userid=m_userid;
   string time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString();
   strcpy(rq->shareTime,time.c_str());

   Tcpclient->SendData(0,(char*)rq,pasize);
   free(rq);
}



#define MD5_KEY 1234
static string getMD5(QString val){
    QString str= QString("%1_%2").arg(val).arg(MD5_KEY);
    MD5 md(str.toStdString());
    qDebug()<<md.toString().c_str()<<' '<<str;
    return md.toString();
}

static string getFileMD5(QString name){
    FILE* pfile=nullptr;
    char buf[1000]="";
    Utf8ToGB2312(buf,1000,name);
    pfile=fopen(buf,"rb");
    if(!pfile){
        qDebug()<<"文件不存在";
        return string();
    }
    MD5 md;
    int len=0;
    do{
        //读到哪 读多少，读多少次 从哪读
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        len=fread(buf,1,1000,pfile);
        md.update(buf,len);//不断拼接文本 进行更新MD5
    }while(len>0);
    fclose(pfile);
    qDebug()<<md.toString().c_str();
    return md.toString();
}



void Ckenel::Initsql(int id)
{
    //目录判断
    QString path=QCoreApplication::applicationDirPath()+"/database/";
    QDir dir;
    if(!dir.exists(path)){
        dir.mkdir(path);
    }
    QString filepath=path+QString("%1.db").arg(id);
    QFileInfo info(filepath);
    //文件库创建
    if(!info.exists()){
    QFile fid(filepath);
    if(!fid.open(QIODevice::WriteOnly)) return;
    fid.close();
    //表创建
    m_sql->ConnectSql(filepath);

    QString sqlbuf="create table t_upload (f_id int,f_name varchar(260),f_dir varchar(260),f_absolutePath varchar(260),f_size int,f_md5 varchar(40),f_time varchar(40),f_type varchar(10),f_timestamp int);";
    m_sql->UpdateSql(sqlbuf);
    sqlbuf="create table t_download (f_id int,f_name varchar(260),f_dir varchar(260),f_absolutePath varchar(260),f_size int,f_md5 varchar(40),f_time varchar(40),f_type varchar(10),f_timestamp int);";
    m_sql->UpdateSql(sqlbuf);
    sqlbuf="create table t_content (p_id int,f_id int,f_name varchar(260),f_time varchar(40),f_content varchar(260));";
    m_sql->UpdateSql(sqlbuf);
    }
    // 存在，加载文件
    else{
     m_sql->ConnectSql(filepath);
    QList<FileInfo*>Upload;
    QList<FileInfo*>Download;

    slot_ReadDown(Download);
    slot_ReadUpload(Upload);
    slot_Readcontent(chat_con);
    for(auto i:Upload){
        QFileInfo info(i->absolutePath);
        if(!info.exists()) continue;

        i->isPause=1;
        i->pos=0;//读取文件，获取当前传输偏移
        qDebug()<<__func__;
        dio->slot_insertFile(i);//显示列表
        dio->slot_uploadProgess(i->timestamp,i->pos);


    }

    for(auto i:Download){
        QFileInfo info(i->absolutePath);
        if(!info.exists()) continue;

        i->isPause=1;
        i->pos=0;//读取文件，获取当前传输偏移

        dio->slot_DownloadInfo(i);//显示列表
        dio->slot_DownloadProgess(i->timestamp,i->pos);//滑块显示

    }

    }


}
//f_id int,f_name varchar(260),f_dir varchar(260),f_absolutePath varchar(260),f_size int,f_md5 varchar(40),f_time varchar(40),f_type varchar(10),f_timestamp int
void Ckenel::slot_writeUpload(FileInfo *info)
{

    QString sqlbuf=QString("insert into t_upload values(%1,'%2','%3','%4',%5,'%6','%7','%8',%9);")
    .arg(info->fileid).arg(info->name).arg(info->dir).arg(info->absolutePath).arg(info->size).arg(info->md5).arg(info->time).arg(info->type).arg(info->timestamp);

    m_sql->UpdateSql(sqlbuf);
}

void Ckenel::slot_sendSms(QString phone)
{
STRU_SMS_RQ rq;
sprintf(rq.tel,phone.toStdString().c_str());
Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
}


void Ckenel::slot_writeDown(FileInfo *info)
{
    QString sqlbuf=QString("insert into t_download values(%1,'%2','%3','%4',%5,'%6','%7','%8',%9);")
       .arg(info->fileid).arg(info->name).arg(info->dir).arg(info->absolutePath).arg(info->size).arg(info->md5).arg(info->time).arg(info->type).arg(info->timestamp);

    m_sql->UpdateSql(sqlbuf);
}
void Ckenel::slot_writeContent(local_content*info)
{
    QString sqlbuf=QString("insert into t_content values(%1,%2,'%3','%4','%5');").arg(info->p_id).arg(info->id).arg(info->name).arg(info->time).arg(info->content);

    m_sql->UpdateSql(sqlbuf);
}
void Ckenel::slot_deleteDown(FileInfo *info)
{
    QString sqlbuf=QString("delete from t_download where f_id=%1;").arg(info->fileid);
    qDebug()<<sqlbuf;
    m_sql->UpdateSql(sqlbuf);
}

void Ckenel::slot_deleteUpload(FileInfo *info)
{
    QString sqlbuf=QString("delete from t_upload where f_id=%1 and f_absolutePath='%2';").arg(info->fileid).arg(info->absolutePath);
    qDebug()<<sqlbuf;
    m_sql->UpdateSql(sqlbuf);
}

void Ckenel::slot_Readcontent(QList<local_content*>&chat_con){
    //id f_id ,f_name ,f_tim,f_content
QString sqlbuf="SELECT * FROM t_content;";
QStringList list;
cout<<__func__<<endl;
m_sql->SelectSql(sqlbuf,5,list);
while(list.size()>0){

local_content* con=new local_content;
con->p_id=stoi(list.front().toStdString());
list.pop_front();
con->id=stoi(list.front().toStdString());
list.pop_front();
con->name=list.front();
list.pop_front();
qDebug()<<con->name;
con->time=list.front();
list.pop_front();
con->content=list.front();
list.pop_front();
qDebug()<<__func__<<con->name<<con->content;
chat_con.push_back(con);

}
}

void Ckenel::slot_addrs(int result, int friendid)
{

    _addfriend_RS rs;
    rs.friendid=friendid;
    rs.status=result;
    rs.my_id=m_userid;
    m_friendRQ[friendid]->close();
    cout<<rs.status<<endl;
    Tcpclient->SendData(0,(char*)&rs,sizeof(rs));


}
void Ckenel::slot_ReadUpload(QList<FileInfo*>&info){

    QString sqlbuf="SELECT * FROM t_upload;";
    QStringList list;

    m_sql->SelectSql(sqlbuf,9,list);
    while(list.size()>0){

        FileInfo* op=new FileInfo;
        op->fileid=stoi(list.front().toStdString());
        list.pop_front();
        op->name=list.front();
        list.pop_front();
        op->dir=list.front();
        list.pop_front();
        op->absolutePath=list.front();
        list.pop_front();
        op->size=stoi(list.front().toStdString());
        list.pop_front();
        op->md5=list.front();
        list.pop_front();
        op->time=list.front();
        list.pop_front();
        op->type=list.front();
        list.pop_front();
        op->timestamp=stoi(list.front().toStdString());
        list.pop_front();
        info.push_back(op);
    }

}


void Ckenel::slot_ReadDown(QList<FileInfo*>&info)
{

    QString sqlbuf="SELECT * FROM t_download;";
    QStringList list;

    m_sql->SelectSql(sqlbuf,9,list);
    while(list.size()>0){

        FileInfo* op=new FileInfo;
        op->fileid=stoi(list.front().toStdString());
        list.pop_front();
        op->name=list.front();
        list.pop_front();
        op->dir=list.front();
        list.pop_front();
        op->absolutePath=list.front();
        list.pop_front();
        op->size=stoi(list.front().toStdString());
        list.pop_front();
        op->md5=list.front();
        list.pop_front();
        op->time=list.front();
        list.pop_front();
        op->type=list.front();
        list.pop_front();
        op->timestamp=stoi(list.front().toStdString());
        list.pop_front();
        info.push_back(op);
    }

}

void Ckenel::dealaddfriend(unsigned int lSendIP, char *buf, int nlen)
{
_addfriend_RS rs=*(_addfriend_RS*)buf;

switch (rs.status) {
case _add_friend_success:
    QMessageBox::about(friend_list,"提示","已成功添加好友");
    break;
case _add_friend_phone_not:
 QMessageBox::about(friend_list,"提示","未找到该人");
    break;
case _add_friend_refuse:
 QMessageBox::about(friend_list,"提示","拒绝添加你为好友");
    break;

default:
    break;
}

}

