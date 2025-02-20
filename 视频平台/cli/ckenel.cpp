#include "ckenel.h"
#include<QDebug>
#include"TcpClientMediator.h"
#include"TcpServerMediator.h"
#include<qrandom.h>
#include <string.h>

static string getMD5(QString val);
Ckenel::Ckenel(QObject *parent) : QObject(parent)
{


    m_max_fileId=0;
    m_min_fileId=0;
    m_wind=new MainWindow;//申请堆区 不会因为函数结束回收
    dio=new Play_Dialog;
    friend_list=new friendlist;
    qsrand(0);
    m_wind->show();
    connect(m_wind,SIGNAL(sig_close_win()),this,SLOT(slot_close_wind()));
    connect(dio,SIGNAL(sig_close_win()),this,SLOT(slot_close_wind()));
    loadinfo();//加载配置文件

    Tcpclient=new TcpClientMediator;
    connect(Tcpclient,SIGNAL(SIG_ReadyData(unsigned int, char*, int)),this,SLOT(slot_client_data( unsigned int, char*, int)));
    connect(m_wind,SIGNAL(sig_register(QString,QString,QString,Hobby,QString)),this,SLOT(slot_register(QString,QString,QString,Hobby,QString)));
    connect(m_wind,SIGNAL(sig_login(QString,QString)),this,SLOT(slot_login(QString,QString)));
    connect(dio,SIGNAL(sig_Uploadfile2(QString,Hobby)),this,SLOT(slot_updload(QString,Hobby)));
    connect(this,SIGNAL(sig_play_auto(QString,int)),dio,SLOT(slot_play_auto(QString,int)));
    connect(this,SIGNAL(sig_setprocess(qint64,qint64)),dio,SIGNAL(sig_upload_process(qint64,qint64)));
    connect(this,SIGNAL(sig_upload_messbox()),dio,SIGNAL(sig_up_success()));

    connect(this,SIGNAL(sig_Download_success()),dio,SLOT(slot_Download_success()));
    connect(dio,SIGNAL(sig_Download(int)),this,SLOT(slot_Download(int)));
    connect(this,SIGNAL(sig_Download_success()),dio,SLOT(slot_Download_success()));
    connect(dio,SIGNAL(sig_play_history(int)),this,SLOT(slot_play_history(int)));

    connect(dio,SIGNAL(sig_play_end()),this,SLOT( slot_play_end()));
    connect(dio,SIGNAL(sig_play_media_Name(QString)),this,SLOT(slot_play_Name(QString)));
    connect(dio,SIGNAL(sig_comment_media_content(QString,int)),this,SLOT(slot_comment_content(QString,int)));
    connect(this,SIGNAL(sig_comment_sucess()),dio,SIGNAL(sig_comment_media_sucess()));
    //connect(this,SIGNAL(sig_comment_sucess()),dio,SLOT(SLOT_comment_media_sucess()));
    connect(dio,SIGNAL(sig_get_comment(int)),this,SLOT(slot_get_comment(int)));
    connect(this,SIGNAL(sig_set_comment(QString,QString,QString)),dio,SLOT(slot_set_comment(QString,QString,QString)));
    connect(m_wind,SIGNAL(sig_sendSms(QString)),this,SLOT(slot_sendSms(QString)));

    connect(this,SIGNAL(sig_set_Plike()),dio,SLOT(slot_set_Plike()));

    connect(dio,SIGNAL(sig_get_recomm()),this,SLOT( slot_get_recomm()));

    connect(friend_list,SIGNAL(sig_addFriend()),this,SLOT(slot_addfriend()));
    initpFUN();

#ifdef USE_SERVER
    Tcpserver=new TcpServerMediator;
    connect(Tcpserver,SIGNAL(SIG_ReadyData(unsigned int, char*,int)),this,SLOT(slot_server_data(unsigned int , char*, int)));
    Tcpserver->OpenNet();
#endif
    Tcpclient->OpenNet("192.168.183.130");
    //    char*buf="hello world";
    //    int len=strlen(buf)+1;
    //    Tcpclient->SendData(0,buf,len);
    //STRU_LOGIN_RQ test;
    //Tcpclient->SendData(0,(char*)&test,sizeof(test));
}

Ckenel::~Ckenel()
{

}
#include<QMessageBox>
#include<QCoreApplication>
#include<QFileInfo>
#include<QSettings>
#include <QInputDialog>
void Ckenel::loadinfo()
{

    QString path=QCoreApplication::applicationDirPath()+"/config.ini";

    m_ip="192.168.183.130";
    m_port="8000";
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
    qDebug()<<m_ip<<' '<<m_port;
}

void Ckenel::initpFUN()
{
    funarr[_DEF_PACK_REGISTER_RS]=&Ckenel::dealRegisterRS;
    funarr[_DEF_PACK_LOGIN_RS]=&Ckenel::dealLoginRS;
    funarr[_DEF_PACK_UPLOAD_RS]=&Ckenel::dealUploadRS;
    funarr[_DEF_PACK_RTMP]=&Ckenel::dealInit;
    funarr[_DEF_PACK_DOWNLOAD_RS]=&Ckenel::download_rs;
    funarr[_DEF_PACK_FILEBLOCK]=&Ckenel::block_Download;
    funarr[_DEF_PACK_COMMENT_PUBLISH_RS]=&Ckenel::deal_comment_push;
    funarr[_DEF_PACK_COMMENT_RS]=&Ckenel::deal_get_comment;
    funarr[_DEF_PACK_PLIKE_RS]=&Ckenel::recv_Plike;
    funarr[_DEF_FRIEND_INFO]=&Ckenel::dealfriend_Info;
    funarr[_DEF_ADD_FRIEND_RS]=&Ckenel::dealaddfriend;
    funarr[_DEF_ADD_FRIEND_RQ]=&Ckenel::recv_friendRQ;
}

void Ckenel::play_auto()
{
    if(m_max_fileId==0) return;
    cout<<m_max_fileId<<endl;
    srand(static_cast<unsigned int>(time(0)));
    int i=100;
    while(i--){
        int play_id=m_min_fileId + rand() % (m_max_fileId - m_min_fileId);
        //qDebug()<<m_playmap[play_id]<<endl;

        if(m_histoty.find(play_id)==m_histoty.end()){


            QString m_path=QString("rtmp://192.168.183.130:1935/vod%1").arg(m_play_audio[play_id]->filePath);

            m_histoty.insert(play_id);
            find_my_history.emplace_back(play_id);
            find_history.emplace_back(play_id);
            qDebug()<<"play_id:"<<play_id<<' '<<m_path;
            Q_EMIT sig_play_auto(m_path,m_play_audio[play_id]->fileId);


            break;
        }
    }

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
    qDebug()<<__func__;
    STRU_LOGIN_RS rs=*(STRU_LOGIN_RS*)buf;
    if(rs.result==user_not_exist){
        QMessageBox::about(m_wind,"提示","用户不存在!");
    }else if(rs.result==password_error){
        QMessageBox::about(m_wind,"提示","密码错误!");
    }else if(rs.result==login_success)
    {
        m_userid=rs.userid;
        UploadPlike::creatUpload()->user_id=m_userid;
        UploadPlike::creatUpload()->start();

        qDebug()<<m_userid;
        m_wind->hide();
        dio->show();
        play_auto();
    }
}

void Ckenel::dealUploadRS(unsigned int lSendIP, char *buf, int nlen)
{
    cout<<__func__<<endl;
    STRU_UPLOAD_RS rs=*(STRU_UPLOAD_RS*)buf;
    if(rs.Result==upload_success){
        Q_EMIT sig_upload_messbox();
    }

}

//void Ckenel::dealInit(unsigned int lSendIP, char *buf, int nlen)
//{

//    STRU_RTMP_RQ *rq=(STRU_RTMP_RQ*)buf;
//    cout<<rq->fileId<<rq->filepath<<' '<<rq->fileName<<endl;
//    m_playmap[rq->fileId]= QString::fromLatin1(rq->filepath);
//    m_playName[rq->fileId]=QString::fromLatin1(rq->fileName);
//    m_max_fileId=max(m_max_fileId,rq->fileId);
//    m_min_fileId=min(m_min_fileId,rq->fileId);


//}
void Ckenel::dealInit(unsigned int lSendIP, char *buf, int nlen)
{

    STRU_RTMP_RQ *rq=(STRU_RTMP_RQ*)buf;
    if(string(rq->filepath)==""||m_playmap.find(rq->fileId)!=m_playmap.end()) return;
    cout<<rq->fileId<<rq->filepath<<' '<<rq->fileName<<endl;
    m_playmap[rq->fileId]= QString::fromLatin1(rq->filepath);
    m_playName[rq->fileId]=QString::fromLatin1(rq->fileName);
    FilePlay *temp=new FilePlay;
    temp->fileId=rq->fileId;
    temp->filePath=QString::fromLatin1(rq->filepath);
    m_play_audio[m_max_fileId]=temp;
    m_max_fileId++;



}
#include<QDir>
void Ckenel::download_rs(unsigned int lSendIP, char *buf, int nlen)
{
    qDebug()<<__func__;
STRU_DOWNLOAD_RS rs=*(STRU_DOWNLOAD_RS*)buf;
//qDebug()<<rs.m_scFileName<<' '<<rs.m_nFileSize<<' '<<rs.file_id;
FileInfo *file=new FileInfo;
file->fileName=rs.m_scFileName;
file->filePos=0;
file->fileSize=rs.m_nFileSize;
QDir dir;

if(!dir.exists(QDir::currentPath()+"/temp/")){
    dir.mkpath(QDir::currentPath()+"/temp/");
}
file->filePath=QString("./temp/%1").arg(file->fileName);
file->pFile=new QFile(file->filePath);
if(file->pFile->open(QIODevice::WriteOnly)){
m_FIleDownload_map[rs.file_id]=file;
}else{
    delete file;
}
}

void Ckenel::block_Download(unsigned int lSendIP, char *buf, int nlen)
{
       // qDebug()<<__func__;
        STRU_FILEBLOCK_RQ rq=*(STRU_FILEBLOCK_RQ*)buf;
        if(m_FIleDownload_map.find(rq.m_nFileId)==m_FIleDownload_map.end()) return;
        FileInfo *info=m_FIleDownload_map[rq.m_nFileId];
        int64_t res=info->pFile->write(rq.m_szFileContent,rq.m_nBlock_Len);
        info->filePos+=res;
        if(info->filePos>=info->fileSize||rq.m_nBlock_Len<_DEF_BUFFER){
            Q_EMIT sig_Download_success();
            info->pFile->close();
            m_FIleDownload_map.erase(info->fileId);
            delete info;
            info=NULL;
        }
}

void Ckenel::deal_comment_push(unsigned int lSendIP, char *buf, int nlen)
{
    STRU_COMMENT_PUBLISH_RS rs=*(STRU_COMMENT_PUBLISH_RS*)buf;
    if(rs.result==comment_sucesss){

        Q_EMIT sig_comment_sucess();
        dio->m_Map_comment[rs.fileid]->clearlay();
       slot_get_comment(rs.fileid);

    }
}

void Ckenel::deal_get_comment(unsigned int lSendIP, char *buf, int nlen)
{
STRU_COMMENT_RS rs=*(STRU_COMMENT_RS*)buf;
QString name=QString::fromLatin1(rs.name);
QString comment=QString::fromLatin1(rs.comment);
QString time=QString::fromLatin1(rs.time);
Q_EMIT sig_set_comment(name,time,comment);

}

//推荐视频返回
void Ckenel::recv_Plike(unsigned int lSendIP, char *buf, int nlen)
{
    //cout<<__func__<<endl;
    STRU_PLIKE_RS rs=*(STRU_PLIKE_RS*)buf;
    cout<<"recom fileid:"<<rs.file_id<<' '<<rs.like<<' '<<rs.play<<endl;
    if(dio->m_File_Plike.find(rs.file_id)!=dio->m_File_Plike.end()){
    dio->m_File_Plike[rs.file_id]->like=rs.like;
    dio->m_File_Plike[rs.file_id]->play=rs.play;

    }else{
    File_Plike* temp=new File_Plike;

    temp->like=rs.like;
    temp->play=rs.play;
   //判断
    dio->m_File_Plike[rs.file_id]=temp;
}
    Q_EMIT sig_set_Plike();
}

void Ckenel::dealfriend_Info(unsigned int lSendIP, char *buf, int nlen)
{
_friend_message info=*(_friend_message*)buf;

if(info.id==m_userid){
    dio->setCoin(info.iconid);
    m_username=QString::fromStdString(info.name);
friend_list->setUserinfo(info.name,info.feeling,info.iconid);
return;
}

cout<<info.id<<' '<<info.name<<endl;
if(m_useritem.count(info.id)>0){
//m_useritem[info.id]->setFrientItem(info.id,info.name,info.feeling,info.iconid);
}else{
 useritem *item=new useritem;
 item->setFrientItem(info.id,info.name,info.feeling,info.iconid);;
m_useritem[info.id]=item;
 friend_list->addfriend(item);
 connect(item,SIGNAL(sig_sendid(int)),this,SLOT(slot_sendid(int)));
 chatdiolog* chat=new chatdiolog;
 m_chatdio[info.id]=chat;
  connect(chat,SIGNAL(sig_sendChatinfo(QString,int)),this,SLOT(slot_sendChatinfo(QString,int)));
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

void Ckenel::uploadfile(QString filename,Hobby h)
{
    qDebug()<<__func__;

    QFileInfo info(filename);
    std::string strName=info.fileName().toStdString();
    const char*file_name=strName.c_str();

    STRU_UPLOAD_RQ rq;
    rq.m_nFileId=qrand()%10000;
    rq.m_nFileSize=info.size();
    strcpy_s(rq.m_scFileName,_MAX_PATH,file_name);
    QByteArray bt=filename.right(filename.length()-filename.lastIndexOf('.')-1).toLatin1();//取文件后缀
    memcpy(rq.m_szFileType,bt.data(),bt.length());
    rq.user_id=m_userid;
    rq.m_szHobby[0]=h.food;
    rq.m_szHobby[1]=h.life;
    rq.m_szHobby[2]=h.cartoon;
    rq.m_szHobby[3]=h.game;
    rq.m_szHobby[4]=h.music;

    qDebug()<<rq.m_szHobby;

    //qDebug()<<rq.m_scFileName<<' '<<rq.m_szFileType<<' '<<rq.m_nFileId<<' '<<rq.user_id<<endl;
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));//先发文件头

    FileInfo fi;
    fi.fileId=rq.m_nFileId;
    fi.fileName=rq.m_scFileName;
    fi.filePath=filename;
    fi.filePos=0;
    fi.fileSize=rq.m_nFileSize;
    fi.pFile=new QFile(filename);

    if(fi.pFile->open(QIODevice::ReadOnly)){
        while(1){
            STRU_FILEBLOCK_RQ blockrq;
            int64_t res=fi.pFile->read(blockrq.m_szFileContent,_DEF_BUFFER);
            fi.filePos+=res;
             //qDebug()<<res<<' '<<fi.filePos<<'\n';
            blockrq.m_nBlock_Len=res;//读取的长度进行传出
            blockrq.m_nFileId=rq.m_nFileId;
            blockrq.m_userid=m_userid;
            Tcpclient->SendData(0,(char*)&blockrq,sizeof(blockrq));
            Q_EMIT sig_setprocess(fi.filePos,fi.fileSize);
            if(fi.filePos>=fi.fileSize){
                qDebug()<<"finish upload\n";
                fi.pFile->close();
                delete fi.pFile;
                fi.pFile=NULL;
                break;
            }

        }
    }

}

void Ckenel::slot_close_wind()
{
    delete m_wind;
    delete dio;
    UploadPlike::creatUpload()->m_running=0;
    Tcpclient->CloseNet();
    qDebug()<<__func__;
    UploadPlike::creatUpload()->quit();


}

void Ckenel::slot_client_data(unsigned int lSendIP, char *buf, int nlen)
{
    //    QString str=QString("server send:%1").arg(QString::fromStdString(buf));
    //    QMessageBox::about(NULL,"服务端消息",str);
   // qDebug()<<__func__;
    PackType type = *(PackType*)buf;
    if( (type >= _DEF_PACK_BASE) && ( type < _DEF_PACK_BASE + _DEF_PACK_COUNT) )
    {
        PFUN pf = funarr[type];
        if(pf){
            (this->*pf)(lSendIP,buf,nlen);
        }
    }
    delete[] buf;
}

void Ckenel::slot_register(QString phone, QString name, QString password,Hobby h,QString duan)
{
    qDebug()<<__func__;
    STRU_REGISTER_RQ reg;
    //装包
    strcpy_s(reg.name,name.toStdString().c_str());
    strcpy_s(reg.tel,phone.toStdString().c_str());
    strcpy_s(reg.password,password.toStdString().c_str());
    string md=getMD5(password);
    cout<<md<<endl;
    strcpy_s(reg.Sms,duan.toStdString().c_str());
    reg.m_szHobby[0]=h.food;
    reg.m_szHobby[1]=h.life;
    reg.m_szHobby[2]=h.cartoon;
    reg.m_szHobby[3]=h.game;
    reg.m_szHobby[4]=h.music;

    Tcpclient->SendData(0,(char*)&reg,sizeof(reg));

}

void Ckenel::slot_login(QString phone, QString password)
{
    qDebug()<<__func__;
    STRU_LOGIN_RQ login;
    //装包
    strcpy_s(login.password,password.toStdString().c_str());
    strcpy_s(login.tel,phone.toStdString().c_str());
    Tcpclient->SendData(0,(char*)&login,sizeof(login));

}

void Ckenel::slot_updload(QString filename,Hobby h)
{
    qDebug()<<filename;
    uploadfile(filename,h);
}

void Ckenel::slot_play_end()
{
    qDebug()<<__func__;
    play_auto();
}

void Ckenel::slot_Download(int m_FileId)
{
cout<<__func__<<endl;
STRU_DOWNLOAD_RQ rq;
rq.FileId=m_FileId;
rq.userId=m_userid;
Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
}

void Ckenel::slot_play_history(int FileId)
{
    cout<<__func__<<endl;
    int pre=-1;
    int n=-1;
    if(m_histoty.size()==1) return;
   //auto ite=m_histoty.find(FileId);

   for(int i=0;i<m_play_audio.size();i++){
    if(m_play_audio[i]->fileId==FileId){
        pre=i;
        break;
    }
}
   qDebug()<<pre<<endl;
for(int i=0;i<find_my_history.size();i++){
if(find_my_history[i]==pre){
    n=i;
    break;
}
}


        QString path=QString("rtmp://192.168.183.130:1935/vod%1").arg(m_play_audio[find_my_history[n-1]]->filePath);
        qDebug()<<path;
        //m_histoty.erase(FileId);
        Q_EMIT sig_play_auto(path,m_play_audio[find_my_history[n-1]]->fileId);
}

void Ckenel::slot_play_Name(QString fileName)
{
int a=0;
for(auto i:m_playName){
    if(i.second==fileName){
        a=i.first;
        break;
    }
}
 QString path=QString("rtmp://192.168.183.130:1935/vod%1").arg(m_playmap[a]);
 qDebug()<<path<<endl;
 Q_EMIT sig_play_auto(path,a);
}

void Ckenel::slot_comment_content(QString content,int fileid)
{
    STRU_COMMENT_PUBLISH_RQ rq;
    strcpy(rq.comment,content.toStdString().c_str());
    rq.file_id=fileid;
    rq.user_id=m_userid;
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
}

void Ckenel::slot_get_comment(int m_FileId)
{
    STRU_COMMENT_RQ rq;
    rq.file_id=m_FileId;
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
}

void Ckenel::slot_sendSms(QString phone)
{
STRU_SMS_RQ rq;
strcpy_s(rq.tel,phone.toStdString().c_str());
Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
}

void Ckenel::slot_get_recomm()
{
qDebug()<<__func__;
    STRU_RECOM_RQ rq;
    rq.user_id=m_userid;
    Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
}

void Ckenel::slot_sendid(int id)
{
    m_chatdio[id]->showNormal();
}

static string getMD5(QString val){
    QString str= QString("%1_%2").arg(val).arg(MD5_KEY);
    MD5 md(str.toStdString());
    qDebug()<<md.toString().c_str()<<' '<<str;
}
void Ckenel::slot_sendChatinfo(QString content,int id){

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

void Ckenel::slot_addrs(int rq,int m_userid)
{
cout<<m_userid<<' '<<rq<<endl;

//添加好友请求 删除请求表 insert friend表 更新info
}

#ifdef USE_SERVER
void Ckenel::slot_server_data(unsigned int lSendIP, char *buf, int nlen)
{
    QString str=QString("client send:%1").arg(QString::fromStdString(buf));
    QMessageBox::about(NULL,"服务端消息",str);
    Tcpserver->SendData(lSendIP,buf,nlen);
    delete[] buf;
}
#endif
