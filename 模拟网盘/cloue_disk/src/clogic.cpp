#include "clogic.h"
#include"packdef.h"
#include <cctype> // for std::isspace
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()
#include <alibabacloud/core/AlibabaCloud.h>
#include <alibabacloud/core/CommonRequest.h>
#include <alibabacloud/core/CommonClient.h>
#include <alibabacloud/core/CommonResponse.h>
#include <string>
#include <algorithm>

#define MD5_KEY 1234


static string getFileMD5(string path){
    int pfile;


    pfile=open(path.c_str(),O_RDWR);
    if(pfile<0){
        cout<<1<<endl;
        return string();
    }
    MD5 md;
    int len=0;
    char buf[1024]="";
    do{
        //读到哪 读多少，读多少次 从哪读
        len=read(pfile,buf,1000);
        md.update(buf,len);//不断拼接文本 进行更新MD5
    }while(len>0);
    close(pfile);
    return md.toString();
}
void CLogic::setNetPackMap()
{
    NetPackMap(_DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(_DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
    NetPackMap(_DEF_PACK_UPLOAD_FILE_RQ)=&CLogic::deal_FileRq;
    NetPackMap(_DEF_PACK_FILE_CONTENT_RQ)=&CLogic::deal_ContentRq;
    NetPackMap(_DEF_PACK_GETINFO_RQ)     =&CLogic::deal_GetFileRq;
    NetPackMap(_DEF_PACK_DOWNLOAD_FILE_RQ)=&CLogic::deal_Download_file_Rq;
    NetPackMap(_DEF_PACK_FILE_HEADER_RS)=&CLogic::deal_Download_file_Rs;
    NetPackMap(_DEF_PACK_FILE_CONTENT_RS)=&CLogic::deal_ContentRs;
    NetPackMap(_DEF_PACK_ADD_FOLDER_RQ)=&CLogic::deal_addFolder;
    NetPackMap(_DEF_PACK_SHARE_FILE_RQ)=&CLogic::deal_ShareRq;
    NetPackMap(_DEF_PACK_MY_SHARE_RQ)=&CLogic::deal_GetShareInfo;
    NetPackMap(_DEF_PACK_GET_SHARE_RQ)=&CLogic::deal_ShareLink_Rq;
    NetPackMap(_DEF_PACK_DOWNLOAD_FOLDER_RQ)=&CLogic::deal_DownFolderRq;
    NetPackMap(_DEF_PACK_DELETE_FILE_RQ)=&CLogic::deal_dealFileRq;
    NetPackMap(_DEF_PACK_CONTINUE_DOWNLOAD_RQ)=&CLogic::deal_Continue_Down_Rq;
    NetPackMap(_DEF_PACK_CONTINUE_UPLOAD_RQ ) =&CLogic::deal_Continue_Upload_Rq;
    NetPackMap(_DEF_PACK_SMS_RQ)         =&CLogic::Send_Sms;
    NetPackMap(_DEF_ADD_FRIEND_RQ)       =&CLogic::addfriend;
    NetPackMap(_DEF_PACK_CHAT_RQ)        =&CLogic::deal_chatRq;
    NetPackMap(_DEF_ADD_FRIEND_RS)       =&CLogic::deal_addRs;
}

#define _DEF_COUT_FUNC_    cout << "clientfd:"<< clientfd << __func__ << endl;
#define _DEF_PATH     "/home/colin/NetDisk"

//注册

void CLogic::RegisterRq(sock_fd clientfd,char* szbuf,int nlen)
{   STRU_REGISTER_RQ *rq=(STRU_REGISTER_RQ*)szbuf;

    //cout<<rq->name<<' '<<rq->password<<' '<<rq->tel<<endl;
    list<string>sql;
    char buf[1024]="";
    char keybuf[1024]="";
    STRU_REGISTER_RS rs;

    sprintf(keybuf,"tel_%s",rq->tel);

    if(redis->isExist(keybuf)){
        rs.result=user_is_exist;
        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
        return;
    }else{

        sprintf(buf,"select * from t_user where u_tel='%s';",rq->tel);
        if(!m_sql->SelectMysql(buf,4,sql)){

            cout<<"sql register wrong\n"<<endl;
            return;
        }

        if(sql.size()!=0){
            rs.result=user_is_exist;
            list<string>filed;

            filed.emplace_back("user_id");
            filed.emplace_back("password");
            filed.emplace_back("name");

            list<string>vals;
            vals.emplace_back(sql.front());
            sql.pop_front();
            sql.pop_front();
            vals.emplace_back(sql.front());
            sql.pop_front();
            vals.emplace_back(sql.front());
            sql.pop_front();
            redis->setHashVals(keybuf,filed,vals);
            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
            return;
        }else{
            sprintf(buf,"INSERT INTO t_user VALUES (NULL,'%s', '%s', '%s');"
                    ,rq->tel,rq->password,rq->name);

            if (!m_sql->UpdataMysql(buf)) {
                cout << "插入失败" << endl;
                return;
            }else{
                const char *folderName = rq->name;            // 文件夹名称
                char path[1024]="";

                // 构造完整路径
                sprintf(path, "%s/%s",_DEF_PATH,folderName);

                // 检查文件夹是否存在
                if (access(path, F_OK) != -1) {
                    printf("dir '%s'has been exist\n", folderName);
                } else {
                    // 创建文件夹
                    if (mkdir(path, 0755) == 0) {
                        printf("dir  '%s' create succes\n", folderName);
                    } else {
                        perror("dir create wrong");

                    }
                }
                rs.result=register_success;

                m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
                return;
            }
        }

    }
//    STRU_REGISTER_RQ *rq=(STRU_REGISTER_RQ*)szbuf;

//    //cout<<rq->name<<' '<<rq->password<<' '<<rq->tel<<endl;
//    list<string>sql;
//    char buf[1024]="";
//    char keybuf[1024]="";
//    STRU_REGISTER_RS rs;

//    sprintf(keybuf,"sms_%s",rq->tel);
//    cout<<keybuf<<endl;

//    if(redis->isExist(keybuf)){
//        string sms;
//        redis->getString(keybuf,sms);
//        cout<<sms<<endl;
//        //cout<<reg->Sms<<' '<<sms<<endl;
//        if((strcmp(rq->sms,sms.c_str()))==1){
//            rs.result=sms_wrong;

//            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
//            return;
//        }
//    }else{
//        rs.result=sms_empire;
//        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
//        return;
//    }

//    sprintf(keybuf,"tel_%s",rq->tel);

//    if(redis->isExist(keybuf)){
//        rs.result=user_is_exist;
//        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
//        return;
//    }else{
//        int id;
//        sprintf(buf,"select * from t_user where u_tel='%s';",rq->tel);
//        if(!m_sql->SelectMysql(buf,4,sql)){

//            cout<<"sql register wrong\n"<<endl;
//            return;
//        }
//        id=stoi(sql.front());
//        if(sql.size()!=0){
//            rs.result=user_is_exist;
//            list<string>filed;

//            filed.emplace_back("user_id");
//            filed.emplace_back("password");
//            filed.emplace_back("name");

//            list<string>vals;
//            vals.emplace_back(sql.front());
//            sql.pop_front();
//            sql.pop_front();
//            vals.emplace_back(sql.front());
//            sql.pop_front();
//            vals.emplace_back(sql.front());
//            sql.pop_front();
//            redis->setHashVals(keybuf,filed,vals);
//            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
//            return;
//        }else{
//            sprintf(buf,"INSERT INTO t_user VALUES (NULL,'%s', '%s', '%s');"
//                    ,rq->tel,rq->password,rq->name);

//            if (!m_sql->UpdataMysql(buf)) {
//                cout << "插入失败" << endl;
//                return;
//            }else{
//                const char *folderName = rq->name;            // 文件夹名称
//                char path[1024]="";

//                // 构造完整路径
//                sprintf(path, "%s/%s",_DEF_PATH,folderName);

//                // 检查文件夹是否存在
//                if (access(path, F_OK) != -1) {
//                    printf("dir '%s'has been exist\n", folderName);
//                } else {
//                    // 创建文件夹
//                    if (mkdir(path, 0755) == 0) {
//                        printf("dir  '%s' create succes\n", folderName);
//                    } else {
//                        perror("dir create wrong");

//                    }
//                }
//                list<string>o;
//                o.emplace_back("name");
//                o.emplace_back("feeling");
//                o.emplace_back("icon_id");
//                char key_info[1024]="";
//                sprintf(key_info,"info_%d",id);
//                if(redis->isExist(key_info)){

//                }else{
//                    sprintf(buf,"insert into user_info values(%d,'%s','hello',28);",id,rq->name);
//                    if (!m_sql->UpdataMysql(buf)) {
//                        cout << "插入失败" << endl;
//                        return;
//                    }else{
//                        list<string>lv;
//                        lv.emplace_back(rq->name);
//                        lv.emplace_back("hello");
//                        lv.emplace_back("28");
//                        redis->setHashVals(key_info,o,lv);
//                    }
//                }
//                rs.result=register_success;

//                m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
//                return;
//            }
//        }

//    }
}

//登录
void CLogic::LoginRq(sock_fd clientfd ,char* szbuf,int nlen)
{
    cout<<__func__<<endl;
    STRU_LOGIN_RQ rq=*(STRU_LOGIN_RQ*)szbuf;
    cout<<rq.password<<' '<<rq.tel<<endl;
    char buf[1024]="";
    char keybuf[1024]="";
    STRU_LOGIN_RS rs;
    list<string>filed;

    filed.emplace_back("user_id");
    filed.emplace_back("password");
    filed.emplace_back("name");

    list<string>vals;
    sprintf(keybuf,"tel_%s",rq.tel);

    if(redis->isExist(keybuf)){
        cout<<keybuf<<endl;
        redis->getHashVals(keybuf,filed,vals);
    }else{

        sprintf(buf,"select u_id,u_password,u_name from t_user where u_tel='%s';",rq.tel);
        if(!m_sql->SelectMysql(buf,3,vals)){
            cout<<"sql register wrong\n"<<endl;
            //WriteLog::GetInstance()->Write_log(1,"login sql register wrong");
            return;
        }
        if(vals.size()==0){
            rs.result=user_not_exist;

            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
            return;
        }
        if(vals.size()!=0){redis->setHashVals(keybuf,filed,vals);
        sprintf(keybuf,"id:%s-name",vals.front());
        if(!redis->isExist(keybuf)){
            redis->setString(vals.front(),vals.back());
        }
        }

    }
    int m_id=stoi(vals.front());

        rs.userid=stoi(vals.front());
        vals.pop_front();


        if(strcmp(vals.front().c_str(),rq.password)){
            rs.result=password_error;
            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
        }else{
            char keybuf[1024]="friend_epoll_1";

            redis->setHashVal(keybuf,to_string(clientfd),to_string(m_id));




            rs.result=login_success;
            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
            sendInfo(m_id);
            sendFriendrq(m_id,clientfd);//好友发送
        }



    return;
}

void CLogic::deal_FileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    cout<<__func__<<endl;
    STRU_UPLOAD_FILE_RQ rq=*(STRU_UPLOAD_FILE_RQ*)szbuf;

    //是否是秒传 Todo
    {

        list<string>sql;
        char sqlbuf[1024]="";
        sprintf(sqlbuf,"select f_id,f_size,f_path,f_count,f_MD5,f_type from t_file where f_MD5='%s' and f_state=1;",rq.md5);
        if(!m_sql->SelectMysql(sqlbuf,6,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        if(sql.size()>0){

           int file_id=stoi(sql.front());

            sprintf(sqlbuf,"insert into t_user_file(u_id,f_id,f_dir,f_name,f_uploadtime) values(%d,%d,'%s','%s','%s');"
                    ,rq.userid,file_id,rq.dir,rq.fileName,rq.time);
            if (!m_sql->UpdataMysql(sqlbuf)) {
                cout << "插入失败" << endl;
                return;
            }

            STRU_QUICK_UPLOAD_RS Quick_rs;
            Quick_rs.result=1;
            Quick_rs.timestamp=rq.timestamp;
            Quick_rs.userid=rq.userid;
            m_pKernel->SendData(clientfd,(char*)&Quick_rs,sizeof(Quick_rs));
            return;
        }

    }
    //不是秒传

    FileInfo *info=new FileInfo;
    char buf[1024]="";
    char keybuf[1024]="";
    sprintf(keybuf,"id:%d-name",rq.userid);
    string user_name;
    list<string>sql;
    if(redis->isExist(keybuf)){
        redis->getString(keybuf,user_name);
    }else{
        sprintf(buf,"select u_name from t_user where u_id=%d;",rq.userid);
        if(!m_sql->SelectMysql(buf,1,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        cout<<sql.front()<<' '<<rq.userid<<endl;
        if(sql.size()>0)user_name=sql.front();
        sql.clear();
        redis->setString(keybuf,user_name);
    }
    //文件名 MD5
    char path[1024]="";
    char rtmp[1024]="";
    if(strcmp(rq.fileType,"flv")==0){

        sprintf(path,"%s/%s%s%s.flv",_DEF_PATH,user_name.c_str(),rq.dir,rq.md5);
        sprintf(rtmp,"rtmp://192.168.183.130:1935/Disk//%s%s%s.flv",user_name.c_str(),rq.dir,rq.md5);
    }else if(strcmp(rq.fileType,"mp4")==0){
        sprintf(path,"%s/%s%s%s.mp4",_DEF_PATH,user_name.c_str(),rq.dir,rq.md5);
        sprintf(rtmp,"rtmp://192.168.183.130:1935/Disk//%s%s%s.mp4",user_name.c_str(),rq.dir,rq.md5);
    }
    else sprintf(path,"%s/%s%s%s",_DEF_PATH,user_name.c_str(),rq.dir,rq.md5);
    info->dir=rq.dir;
    info->md5=rq.md5;
    info->size=rq.size;
    info->type=rq.fileType;
    info->time=rq.time;
    info->name=rq.fileName;
    info->rtmp=rtmp;
    info->absolutePath=path;
    cout<<rq.fileType<<endl;
    cout<<path<<endl;
    info->pFile_id=open(path,O_CREAT|O_WRONLY|O_TRUNC,0777);
    if(info->pFile_id<0){
        cout<<"open wrong"<<endl;
        return;
    }
    int64_t keyid=rq.userid*(this->getNumber())+rq.timestamp;
    m_mapIdToInfo.insert(keyid,info);
    //写入数据库 加入redis缓存
    cout<<path<<endl;
    if(strcmp(rq.fileType,"flv")==0){
        sprintf(buf,"insert into t_file(f_size,f_path,f_count,f_MD5,f_state,f_type,rtmp) values(%d,'%s',0,'%s',0,'%s','%s');"
                ,info->size,path,info->md5.c_str(),rq.fileType,rtmp);

        if (!m_sql->UpdataMysql(buf)) {
            cout<<buf<<endl;
            cout << "插入失败" << endl;
            return;
        }
    }
    else if(strcmp(rq.fileType,"mp4")==0){
        sprintf(buf,"insert into t_file(f_size,f_path,f_count,f_MD5,f_state,f_type,rtmp) values(%d,'%s',0,'%s',0,'%s','%s');"
                ,info->size,path,info->md5.c_str(),rq.fileType,rtmp);

        if (!m_sql->UpdataMysql(buf)) {
            cout<<buf<<endl;
            cout << "插入失败" << endl;
            return;
        }
    }
    else{
        sprintf(buf,"insert into t_file(f_size,f_path,f_count,f_MD5,f_state,f_type) values(%d,'%s',0,'%s',0,'%s');"
                ,info->size,path,info->md5.c_str(),rq.fileType);

        if (!m_sql->UpdataMysql(buf)) {
            cout<<buf<<endl;
            cout << "插入失败" << endl;
            return;
        }

    }
    sprintf(buf,"select f_id,f_size,f_path,f_count,f_MD5,f_type from t_file where f_path='%s' and f_MD5='%s';",path,info->md5.c_str());

    if(!m_sql->SelectMysql(buf,6,sql)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }

    if(sql.size()==0)return;
    int f_id=stoi(sql.front());
    if(strcmp(rq.fileType,"flv")==0||strcmp(rq.fileType,"mp4")==0){
        char rp_buf[1024]="";
        sprintf(rp_buf,"rtmp_id:%d",f_id);
        redis->setString(rp_buf,rtmp);
    }
    sql.pop_front();
    sprintf(keybuf,"file_info_id:%d",f_id);
    list<string>vals;
    list<string>filed;
    filed.emplace_back("f_size");
    filed.emplace_back("f_path");
    filed.emplace_back("f_count");
    filed.emplace_back("f_MD5");
    filed.emplace_back("f_type");
    filed.emplace_back("f_name");
    while(!sql.empty()){
        vals.emplace_back(sql.front());
        sql.pop_front();
    }
    vals.emplace_back(info->name);

    redis->setHashVals(keybuf,filed,vals);

    sprintf(buf,"insert into t_user_file(u_id,f_id,f_dir,f_name,f_uploadtime) values(%d,%d,'%s','%s','%s');"
            ,rq.userid,f_id,rq.dir,rq.fileName,rq.time);
    if (!m_sql->UpdataMysql(buf)) {
        cout << "插入失败" << endl;
        return;
    }

    STRU_UPLOAD_FILE_RS rs;
    rs.fileid=f_id;
    rs.timestamp=rq.timestamp;
    rs.userid=rq.userid;
    rs.result=1;

    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));


}

void CLogic::deal_ContentRq(sock_fd clientfd, char *szbuf, int nlen)
{

    //cout<<__func__<<endl;

    STRU_FILE_CONTENT_RQ rq=*(STRU_FILE_CONTENT_RQ*)szbuf;
    //cout<<rq.fileid<<endl;
    int64_t key=rq.userid*(this->getNumber())+rq.timestamp;
    FileInfo *info;
    if(!m_mapIdToInfo.find(key,info)){
        cout<<"not found"<<endl;
        return;
    }
    //cout<<info->pFile_id<<endl;
    STRU_FILE_CONTENT_RS rs;
    int len=write(info->pFile_id,rq.content,rq.len);

    if(len!=rq.len){
        rs.result=0;
        lseek(info->pFile_id,-1*len,SEEK_CUR);// return
    }else{
        rs.result=1;
        info->pos+=len;
        //cout<<info->pos<<' '<<info->size<<endl;
        if(info->pos>=info->size){

            close(info->pFile_id);
            m_mapIdToInfo.erase(key);
            string mess_vis=getFileMD5(info->absolutePath);//MD5
            cout<<"md5"<<mess_vis<<endl;
            char buf[1024]="";
            if(mess_vis==info->md5){


            sprintf(buf,"update t_file set f_state=1 where f_id=%d;",rq.fileid);

            if (!m_sql->UpdataMysql(buf)) {
                cout << "更新失败" << endl;
                return;
            }
            }else {
                sprintf(buf,"delete from t_file where f_id=%d;",info->fileid);
                if (!m_sql->UpdataMysql(buf)) {
                    cout << "更新失败" << endl;
                    return;
                }
            }

            char keybuf[1024]="";
            sprintf(keybuf,"file_info_id:%d",rq.fileid);
            if(redis->isExist(keybuf)) redis->removeKey(keybuf);

            delete info;
            info=nullptr;
        }

    }
    rs.userid=rq.userid;
    rs.timestamp=rq.timestamp;
    rs.fileid=rq.fileid;
    rs.len=rq.len;

    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));


}

void CLogic::deal_GetFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_GET_INFO_RQ rq=*(STRU_GET_INFO_RQ*)szbuf;
    //查表获取信息
    char buf[1024]="";
    char keybuf[1024]="";
    list<string>sql;

    sprintf(buf,"select t_user_file.f_id,t_user_file.f_name,t_user_file.f_uploadtime from t_user_file inner join t_file on t_user_file.f_id=t_file.f_id where u_id=%d and f_dir='%s' and f_state=1;"
            ,rq.user_id,rq.dir);

    if(!m_sql->SelectMysql(buf,3,sql)){
        cout<<"sql register wrong\n"<<endl;
        cout<<buf<<endl;
        return;
    }
    if(sql.size()==0) return;

    int count=sql.size()/3;


    int packlen=sizeof(STRU_GET_INFO_RS)+(sizeof(STRU_FILE_INFO)*count);

    STRU_GET_INFO_RS* rs=(STRU_GET_INFO_RS*)malloc(packlen);
    rs->init();
    rs->count=count;
    strcpy(rs->dir,rq.dir);




    for(int i=0;i<count;i++){

        int f_id=stoi(sql.front());

        sql.pop_front();

        sprintf(keybuf,"file_info_id:%d",f_id);
        string name=sql.front();

        sql.pop_front();

        string time=sql.front();
        sql.pop_front();


        list<string>filed;
        list<string>sql2;
        filed.emplace_back("f_size");
        filed.emplace_back("f_path");
        filed.emplace_back("f_count");
        filed.emplace_back("f_MD5");
        filed.emplace_back("f_type");
        filed.emplace_back("f_name");
        if(redis->isExist(keybuf)){
            redis->getHashVals(keybuf,filed,sql2);
        }else{

            sprintf(buf,"select f_size,f_path,f_count,f_MD5,f_type from t_file where f_id=%d and f_state=1;",f_id);

            if(!m_sql->SelectMysql(buf,5,sql2)){
                cout<<"sql register wrong\n"<<endl;
                return;
            }
            if(sql2.size()==0) continue;
            sql2.emplace_back(name);
            redis->setHashVals(keybuf,filed,sql2);

        }
        sql2.pop_back();

        int size=stoi(sql2.front());
        string type=sql2.back();
        char rp_buf[1024]="";
        sprintf(rp_buf,"rtmp_id:%d",f_id);

       // cout<<rp_buf<<endl;
        if(redis->isExist(rp_buf)){
       // cout<<1<<endl;
           string rtmp;
           redis->getString(rp_buf,rtmp);

           strcpy(rs->info_arr[i].rtmp,rtmp.c_str());
        }
        rs->info_arr[i].fileid=f_id;
        strcpy(rs->info_arr[i].fileType,type.c_str());
        strcpy(rs->info_arr[i].name,name.c_str());
        rs->info_arr[i].size=size;
        strcpy(rs->info_arr[i].time,time.c_str());
        //cout<<rs->info_arr[i].name<<' '<<rs->info_arr[i].size<<endl;
    }

    //回复
    m_pKernel->SendData(clientfd,(char*)rs,packlen);//序列化
    free(rs);

}

void CLogic::deal_Download_file_Rq(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_DOWNLOAD_FILE_RQ rq=*(STRU_DOWNLOAD_FILE_RQ*)szbuf;

    list<string>filed;
    list<string>sql2;
    list<string>sql;
    filed.emplace_back("f_size");
    filed.emplace_back("f_path");
    filed.emplace_back("f_count");
    filed.emplace_back("f_MD5");
    filed.emplace_back("f_type");
    filed.emplace_back("f_name");
    char keybuf[1024]="";
    sprintf(keybuf,"file_info_id:%d",rq.fileid);
    if(redis->isExist(keybuf)){
        redis->getHashVals(keybuf,filed,sql);
    }else{
        char buf[1024]="";
        sprintf(buf,"select f_name from t_user_file where f_id=%d;",rq.fileid);
        if(!m_sql->SelectMysql(buf,1,sql2)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        if(sql2.size()==0) return;
        string name=sql2.front();

        sprintf(buf,"select f_size,f_path,f_count,f_MD5,f_type from t_file where f_id=%d;",rq.fileid);

        if(!m_sql->SelectMysql(buf,5,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        if(sql.size()==0) return;
        sql.emplace_back(name);
        redis->setHashVals(keybuf,filed,sql);
    }


    FileInfo *info=new FileInfo;

    info->name=sql.back();
    sql.pop_back();
    info->size=stoi(sql.front()); sql.pop_front();
    info->absolutePath=sql.front(); sql.pop_front();
    sql.pop_front();
    info->md5=sql.front(); sql.pop_front();
    info->type=sql.front(); sql.pop_front();
    int64_t keyid=rq.userid*(this->getNumber())+rq.timestamp;

    info->pFile_id=open(info->absolutePath.c_str(),O_RDONLY);

    if(info->pFile_id<0){
        cout<<"open file wrong"<<endl;
        return;
    }

    m_mapIdToInfo.insert(keyid,info);

    STRU_FILE_HEADER_RQ headRq;
    strcpy(headRq.dir,rq.dir);
    headRq.fileid=rq.fileid;
    strcpy(headRq.fileName,info->name.c_str());
    strcpy(headRq.fileType,info->type.c_str());
    strcpy(headRq.md5,info->md5.c_str());
    headRq.size=info->size;
    headRq.timestamp=rq.timestamp;

   m_pKernel->SendData(clientfd,(char*)&headRq,sizeof(headRq));


}

void CLogic::deal_Download_file_Rs(sock_fd clientfd, char *szbuf, int nlen)
{
    //cout<<__func__<<endl;

    STRU_FILE_HEADER_RS rs=*(STRU_FILE_HEADER_RS*)szbuf;
    if(!rs.result){
        cout<<"download refuse"<<endl;
        return;
    }

    int64_t keys=rs.userid*(this->getNumber())+rs.timestamp;
    FileInfo *info;

    if(!m_mapIdToInfo.find(keys,info)) return;

    //发文件内容
    STRU_FILE_CONTENT_RQ rq;
    rq.fileid=info->fileid;

    rq.len=read(info->pFile_id,rq.content,_DEF_BUFFER);
    if(rq.len<=0){
        cout<<"read fail"<<endl;
        return;
    }
    rq.timestamp=rs.timestamp;
    rq.userid=rs.userid;

    m_pKernel->SendData(clientfd,(char*)&rq,sizeof(rq));

}

void CLogic::deal_ContentRs(sock_fd clientfd, char *szbuf, int nlen)
{

    STRU_FILE_CONTENT_RS rs=*(STRU_FILE_CONTENT_RS*)szbuf;
    //cout<<__func__<<endl;
    int64_t keys=rs.userid*(this->getNumber())+rs.timestamp;
    FileInfo *info;
    if(!m_mapIdToInfo.find(keys,info)) return;

    if(!rs.result){
        //下载错误，退回下标
        lseek(info->pFile_id,(-1*rs.len),SEEK_CUR);
    }
    else{
        info->pos+=rs.len;

        if(info->pos>=info->size){
            m_mapIdToInfo.erase(keys);
            close(info->pFile_id);
            delete info;
            info=nullptr;
            return;
        }

    }

    STRU_FILE_CONTENT_RQ rq;
    rq.fileid=info->fileid;
    rq.len=read(info->pFile_id,rq.content,_DEF_BUFFER);
    if(rq.len<=0){
        cout<<"read fail"<<endl;
        return;
    }
    rq.timestamp=rs.timestamp;
    rq.userid=rs.userid;

    m_pKernel->SendData(clientfd,(char*)&rq,sizeof(rq));

}

void CLogic::deal_addFolder(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_ADD_FOLDER_RQ rq=*(STRU_ADD_FOLDER_RQ*)szbuf;
    char buf[1024]="";
    char keybuf[1024]="";
    sprintf(keybuf,"id:%d-name",rq.userid);
    string user_name;

    list<string>sql;
    if(redis->isExist(keybuf)){
        redis->getString(keybuf,user_name);
    }else{
        sprintf(buf,"select u_name from t_user where u_id=%d;",rq.userid);
        if(!m_sql->SelectMysql(buf,1,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        cout<<sql.front()<<' '<<rq.userid<<endl;
        if(sql.size()>0)user_name=sql.front();
        sql.clear();
        redis->setString(keybuf,user_name);
    }
    char path[1024]="";
    sprintf(path,"%s/%s%s%s",_DEF_PATH,user_name.c_str(),rq.dir,rq.fileName);

    sprintf(buf,"insert into t_file(f_size,f_path,f_count,f_MD5,f_state,f_type) values(0,'%s',0,'?',1,'folder');",path);
    if (!m_sql->UpdataMysql(buf)) {
        cout << "插入失败" << endl;
        return;
    }

    sprintf(buf,"select f_id,f_size,f_path,f_count,f_MD5,f_type from t_file where f_path='%s';",path);
    if(!m_sql->SelectMysql(buf,6,sql)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }

    if(sql.size()==0) return;
    list<string>filed;
    list<string>sql2;
    filed.emplace_back("f_size");
    filed.emplace_back("f_path");
    filed.emplace_back("f_count");
    filed.emplace_back("f_MD5");
    filed.emplace_back("f_type");
    filed.emplace_back("f_name");

    int f_id=stoi(sql.front());sql.pop_front();

    sprintf(keybuf,"file_info_id:%d",f_id);
    sql.push_back(rq.fileName);
    redis->setHashVals(keybuf,filed,sql);

    sprintf(buf,"insert into t_user_file(u_id,f_id,f_dir,f_name,f_uploadtime) values(%d,%d,'%s','%s','%s');"
            ,rq.userid,f_id,rq.dir,rq.fileName,rq.time);
    if (!m_sql->UpdataMysql(buf)) {
        cout << "插入失败" << endl;
        return;
    }
    umask(0);
    mkdir(path,0777);

    STRU_ADD_FOLDER_RS rs;
    rs.result=1;
    rs.timestamp=rq.timestamp;
    rs.userid=rq.userid;
    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));

}

void CLogic::deal_ShareRq(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_SHARE_FILE_RQ *rq=(STRU_SHARE_FILE_RQ*)szbuf;

    //9 share_code;
    unsigned int link_code=0;
    do{
        link_code=1+random()*7;
        link_code*=1000000;
        link_code+=random()%1000000;
        link_code=abs(link_code);
        char buf[1024]="";
        list<string>sql;
        sprintf(buf,"select f_id from t_user_file where s_link=%d;",link_code);
        if(!m_sql->SelectMysql(buf,1,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        if(sql.size()>0) link_code=0;


    }while(link_code==0);

    for(int i=0;i<rq->itemCount;i++){
        cout<<rq->fileidArray[i]<<' '<<rq->shareTime<<endl;
        share_insert(rq->fileidArray[i],rq->userid,string(rq->dir),string(rq->shareTime),link_code);
    }
    cout<<"share rs"<<endl;
    STRU_SHARE_FILE_RS rs;

    rs.result=1;

    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));

}

void CLogic::share_insert(int fileid, int userid, string dir, string time, int link)
{
    char buf[1024]="";

    sprintf(buf,"update t_user_file set s_link='%d',s_linkTime='%s' where u_id=%d and f_id=%d and f_dir='%s';"
            ,link,time.c_str(),userid,fileid,dir.c_str());

    if (!m_sql->UpdataMysql(buf)) {
        cout<<buf<<endl;
        cout << "插入失败" << endl;
        return;
    }

}

void CLogic::deal_GetShareInfo(sock_fd clientfd, char *szbuf, int nlen)
{
    //cout<<__func__<<endl;
    STRU_MY_SHARE_RQ rq=*(STRU_MY_SHARE_RQ*)szbuf;

    char keybuf[1024]="";
    char buf[1024]="";
    sprintf(keybuf,"share_uid:%d",rq.userid);

    list<string>vals;
    if(redis->isExist(keybuf)){

        redis->setList(keybuf,vals);

    }else{

        list<string>sql;
        list<string>sql2;
        list<string>m_name;
        sprintf(buf,"select f_name,s_link,s_linkTime from t_user_file where u_id=%d and s_link is not null and s_linkTime is not null;",rq.userid);
        if(!m_sql->SelectMysql(buf,3,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        if(sql.size()==0) return;


        sprintf(buf,"select f_id from t_user_file where u_id=%d and s_link is not null and s_linkTime is not null;",rq.userid);
        if(!m_sql->SelectMysql(buf,1,sql2)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        if(sql2.size()==0) return;
        while(sql2.size()){

         list<string>temp;
         int fid=stoi(sql2.front());
         cout<<"f_id"<<fid<<endl;
         sql2.pop_front();

         sprintf(buf,"select f_size from t_file where f_id=%d;",fid);

         if(!m_sql->SelectMysql(buf,1,temp)){
            cout<<"sql register wrong\n"<<endl;
            return;
         }

         if(temp.size()>0) m_name.emplace_back(temp.front());

        }
       int i=3;
       while(sql.size()>0){
           if(i%3==0){
               vals.emplace_back(m_name.front());
               m_name.pop_front();
           }
           vals.emplace_back(sql.front());
           sql.pop_front();
           i++;

       }

       redis->setList(keybuf,vals);
    }
    if(vals.size()%4!=0) return;
    int count=vals.size()/4;
    int packsize=sizeof(STRU_MY_SHARE_RS)+sizeof(STRU_MY_SHARE_FILE)*count;

    STRU_MY_SHARE_RS *rs=(STRU_MY_SHARE_RS *)malloc(packsize);
    rs->init();
    rs->itemCount=count;
    for(int i=0;i<count;i++){
        rs->items[i].size=stoi(vals.front()); vals.pop_front();
        strcpy(rs->items[i].name,vals.front().c_str()); vals.pop_front();
        rs->items[i].shareLink=stoi(vals.front()); vals.pop_front();
        strcpy(rs->items[i].time,vals.front().c_str()); vals.pop_front();

    }

    m_pKernel->SendData(clientfd,(char*)rs,packsize);
    free(rs);


}

void CLogic::deal_ShareLink_Rq(sock_fd clientfd, char *szbuf, int nlen)
{
   // cout<<__func__<<endl;
    STRU_GET_SHARE_RQ rq=*(STRU_GET_SHARE_RQ*)szbuf;
    rq.dir;
    rq.shareLink;
    rq.time;
    rq.userid;

   STRU_GET_SHARE_RS rs;
    //sprintf(keybuf,"s_Link_Info:%d",rq.shareLink);

    char buf[1024]="";
    list<string>sql;

    sprintf(buf,"select u_id,f_id,f_dir,f_name from t_user_file where s_link='%d';",rq.shareLink);

    if(!m_sql->SelectMysql(buf,4,sql)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }
    if(sql.size()%4>0) {
        rs.result=0;

        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));

        return;
    }

    while(sql.size()>0){
      list<string>s_type;
      int u_id=stoi(sql.front()); sql.pop_front();
      int f_id=stoi(sql.front()); sql.pop_front();
      string f_dir=sql.front(); sql.pop_front();
      string name=sql.front(); sql.pop_front();
      sprintf(buf,"select f_type from t_file where f_id=%d;",f_id);

      if(!m_sql->SelectMysql(buf,1,s_type)){
          cout<<"sql register wrong\n"<<endl;
          return;
      }
      if(s_type.size()==0) return;

      string type=s_type.front();  s_type.pop_front();
      //file
      if(type=="file"){
       insert_file(rq.userid,f_id,rq.dir,name,rq.time);


      }else{
          //folder

       insert_folder(rq.userid,f_id,rq.dir,name,rq.time,u_id,f_dir);
      }


    }


    rs.result=1;

    strcpy(rs.dir,rq.dir);
    //cout<<"get Link rs"<<endl;
    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));

}

void CLogic::insert_file(int uid, int fid, string dir, string name, string time)
{
    char buf[1024]="";

    sprintf(buf,"insert into t_user_file(u_id,f_id,f_dir,f_name,f_uploadtime) values(%d,%d,'%s','%s','%s');"
            ,uid,fid,dir.c_str(),name.c_str(),time.c_str());
    if (!m_sql->UpdataMysql(buf)) {
        cout<<buf<<endl;
        cout << "插入失败" << endl;
        return;
    }


}

void CLogic::insert_folder(int uid, int fid, string dir, string name,string time,int fromuserid,string fromdir)
{
    //插入文件夹
    insert_file(uid,fid,dir,name,time);

    //拼接路径
    string newDir=dir+name+"/";

    //分享目录的拼接
    string new_fromDir=fromdir+name+"/";

    //根据拼接路径去找文件

    char buf[1024]="";
    list<string>sql;
    sprintf(buf,"select f_id,f_name from t_user_file where u_id=%d and f_dir='%s';",fromuserid,new_fromDir.c_str());


    if(!m_sql->SelectMysql(buf,2,sql)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }

    if(sql.size()%2>0) return;

    while(!sql.empty()){

        int f_id=stoi(sql.front()); sql.pop_front();
        string Newname=sql.front(); sql.pop_front();
        cout<<f_id<<' '<<Newname<<endl;
        list<string>s_type;
        sprintf(buf,"select f_type from t_file where f_id=%d;",f_id);
        if(!m_sql->SelectMysql(buf,1,s_type)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        if(s_type.size()==0) return;

        string type=s_type.front();  s_type.pop_front();
        if(type=="file"){
            insert_file(uid,f_id,newDir,Newname,time);
        }else{
            //递归遍历该文件夹下的文件进行插入
            insert_folder(uid,f_id,newDir,Newname,time,fromuserid,new_fromDir);
        }
    }


}

void CLogic::deal_DownFolderRq(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_DOWNLOAD_FOLDER_RQ rq=*(STRU_DOWNLOAD_FOLDER_RQ*)szbuf;

    //dir

    // f_id f_name f_size f_MD5 f_path f_type f_dir;
    //查询获取值
    cout<<rq.dir<<endl;
    list<string>sql;
    list<string>sql2;
    char buf[1024]="";
    sprintf(buf,"select f_type,f_id,f_path,f_size,f_MD5 from t_file where f_id=%d;",rq.fileid);
    if(!m_sql->SelectMysql(buf,5,sql)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }
    if(sql.size()%5>0) return;

    sprintf(buf,"select f_dir,f_name from t_user_file where f_id=%d and u_id=%d and f_dir='%s';",rq.fileid,rq.userid,rq.dir);
    if(!m_sql->SelectMysql(buf,2,sql2)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }
    while(sql2.size()>0){
        sql.emplace_back(sql2.front());
        sql2.pop_front();
    }


    string type=sql.front(); sql.pop_front();
   int timestamp=rq.timestamp;
   DownloadFolder(rq.userid,timestamp,clientfd,sql);
}

void CLogic::DownloadFolder(int userid, int &timestamp, sock_fd clientfd, list<string> &lstres)
{
//取值
int f_id=stoi(lstres.front()); lstres.pop_front();
string path=lstres.front(); lstres.pop_front();
int size=stoi(lstres.front()); lstres.pop_front();
string MD5= lstres.front(); lstres.pop_front();
string dir=lstres.front(); lstres.pop_front();
string name=lstres.front(); lstres.pop_front();
//文件夹创建请求
cout<<"folder"<<' '<<name<<' '<<dir<<endl;

//文件文件夹判断
string newdir=dir+name+'/';
STRU_FOLDER_HEADER_RQ rq;
strcpy(rq.dir,dir.c_str());
rq.fileid=f_id;
strcpy(rq.fileName,name.c_str());
rq.timestamp=++timestamp;//文件夹创建 时间戳处理

m_pKernel->SendData(clientfd,(char*)&rq,sizeof(rq));

list<string>sql2;
char buf[1024]="";


//查找新目录下的 属于user的文件
sprintf(buf,"select f_id,f_dir,f_name from t_user_file where u_id=%d and f_dir='%s';",userid,newdir.c_str());
if(!m_sql->SelectMysql(buf,3,sql2)){
    cout<<"sql register wrong\n"<<endl;
    return;
}


if(sql2.size()%3>0) return;

while(sql2.size()>0){

    list<string>sql;
    int fileid=stoi(sql2.front()); sql2.pop_front();
    string f_dir=sql2.front(); sql2.pop_front();
    string f_name=sql2.front(); sql2.pop_front();

    sprintf(buf,"select f_type,f_id,f_path,f_size,f_MD5 from t_file where f_id=%d;",fileid);
    if(!m_sql->SelectMysql(buf,5,sql)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }
    if(sql.size()%5>0) return;
    sql.emplace_back(f_dir);
    sql.emplace_back(f_name);
    string type=sql.front(); sql.pop_front();
   if(type=="file") DownloadFile(userid,timestamp,clientfd,sql);
   else DownloadFolder(userid,timestamp,clientfd,sql);


}


}

void CLogic::deal_dealFileRq(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_DELETE_FILE_RQ*rq=(STRU_DELETE_FILE_RQ*)szbuf;

    for(int i=0;i<rq->fileCount;i++){
        deleteOneItem(rq->userid,rq->fileidArray[i],rq->dir);
    }
    STRU_DELETE_FILE_RS rs;
    rs.result=1;
    strcpy(rs.dir,rq->dir);

    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
}

void CLogic::deleteOneItem(int userid,int f_id,string dir)
{
    //查找文件类型 删除判断
    char buf[1024]="";
    char keybuf[1024]="";
    list<string>sql;
    sprintf(keybuf,"file_info_id:%d",f_id);
    string type;
    string name;
    string path;
    if(redis->isExist(keybuf)){

    }else{
        list<string>sqlname;
        sprintf(buf,"select f_size,f_path,f_count,f_MD5,f_type from t_file where f_id=%d;",f_id);
        if(!m_sql->SelectMysql(buf,5,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        if(sql.size()==0)return;

        list<string>vals;
        list<string>filed;
        filed.emplace_back("f_size");
        filed.emplace_back("f_path");
        filed.emplace_back("f_count");
        filed.emplace_back("f_MD5");
        filed.emplace_back("f_type");
        filed.emplace_back("f_name");
        while(!sql.empty()){
            vals.emplace_back(sql.front());
            sql.pop_front();
        }
        sprintf(buf,"select f_name from t_user_file where f_id=%d and u_id=%d and f_dir='%s';"
               ,f_id,userid,dir.c_str());
        if(!m_sql->SelectMysql(buf,1,sqlname)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        if(sqlname.size()==0) return;
        vals.emplace_back(sqlname.front());
        redis->setHashVals(keybuf,filed,vals);

    }
    redis->getHashVal(keybuf,"f_type",type);
    redis->getHashVal(keybuf,"f_name",name);
    redis->getHashVal(keybuf,"f_path",path);
    if(type=="file"){
        deleteFIle(userid,f_id,dir,path);
    }else{
        deleteFolder(userid,f_id,dir,name);
    }


}

void CLogic::deleteFIle(int u_id,int f_id,string dir,string path){
    //u_id f_id dir path
    char buf[1024]="";
    list<string>sql;
    //删除关系
    sprintf(buf,"delete from t_user_file where u_id=%d and f_id=%d and f_dir='%s';"
            ,u_id,f_id,dir.c_str());

    if (!m_sql->UpdataMysql(buf)) {
        cout<<buf<<endl;
        cout << "删除失败" << endl;
        return;
    }

    //是否存在
    sprintf(buf,"select f_id from t_file where f_id=%d;",f_id);
    if(!m_sql->SelectMysql(buf,1,sql)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }

    //不存在根据本地路径删除
    if(sql.size()==0){
        char keybuf[1024]="";
       sprintf(keybuf,"file_info_id:%d",f_id);
       redis->removeKey(keybuf);
       unlink(path.c_str());
    }
}

void CLogic::deleteFolder(int u_id,int f_id,string dir,string name){
    //u_id f_id dir  name

    //删除文件关系 文件夹下可能还有文件，不需要删除，只需要删除关系即可
    char buf[1024]="";
    list<string>sql2;
    //删除关系
    sprintf(buf,"delete from t_user_file where u_id=%d and f_id=%d and f_dir='%s';"
            ,u_id,f_id,dir.c_str());

    if (!m_sql->UpdataMysql(buf)) {

        cout<<buf<<endl;
        cout << "删除失败" << endl;
        return;

    }
    //拼接新路径
    string NewDir=dir+name+"/";
    //查询文件夹下的文件

    sprintf(buf,"select f_id from t_user_file where u_id=%d and f_dir='%s'",
            u_id,NewDir.c_str());
    if(!m_sql->SelectMysql(buf,1,sql2)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }
    char keybuf[1024]="";
    if(sql2.size()==0) return;


    while(sql2.size()>0){

    int fileid=stoi(sql2.front()); sql2.pop_front();

    sprintf(keybuf,"file_info_id:%d",fileid);
    string type;
    string name;
    string path;
    if(redis->isExist(keybuf)){

    }else{
        list<string>sqlname;
        list<string>sql;
        sprintf(buf,"select f_size,f_path,f_count,f_MD5,f_type from t_file where f_id=%d;",fileid);
        if(!m_sql->SelectMysql(buf,5,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        if(sql.size()==0)return;

        list<string>vals;
        list<string>filed;
        filed.emplace_back("f_size");
        filed.emplace_back("f_path");
        filed.emplace_back("f_count");
        filed.emplace_back("f_MD5");
        filed.emplace_back("f_type");
        filed.emplace_back("f_name");
        while(!sql.empty()){
            vals.emplace_back(sql.front());
            sql.pop_front();
        }
        sprintf(buf,"select f_name from t_user_file where f_id=%d and u_id=%d and f_dir='%s';"
               ,fileid,u_id,NewDir.c_str());
        if(!m_sql->SelectMysql(buf,1,sqlname)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        if(sqlname.size()==0) return;
        vals.emplace_back(sqlname.front());
        redis->setHashVals(keybuf,filed,vals);

    }
    redis->getHashVal(keybuf,"f_type",type);
    redis->getHashVal(keybuf,"f_name",name);
    redis->getHashVal(keybuf,"f_path",path);
    //递归判断下面的文件
    if(type=="file")  deleteFIle(u_id,fileid,NewDir,path);
    else  deleteFolder(u_id,fileid,NewDir,name);
    }
}

void CLogic::deal_Continue_Down_Rq(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_CONTINUE_DOWNLOAD_RQ rq=*(STRU_CONTINUE_DOWNLOAD_RQ*)szbuf;
    FileInfo *info;

int64_t keyid=rq.userid*(this->getNumber())+rq.timestamp;
    if(!m_mapIdToInfo.find(keyid,info)){

        list<string>filed;
        list<string>sql2;
        list<string>sql;
        filed.emplace_back("f_size");
        filed.emplace_back("f_path");
        filed.emplace_back("f_count");
        filed.emplace_back("f_MD5");
        filed.emplace_back("f_type");
        filed.emplace_back("f_name");
        char keybuf[1024]="";
        sprintf(keybuf,"file_info_id:%d",rq.fileid);
        if(redis->isExist(keybuf)){
            redis->getHashVals(keybuf,filed,sql);
        }else{
            char buf[1024]="";
            sprintf(buf,"select f_name from t_user_file where f_id=%d;",rq.fileid);
            if(!m_sql->SelectMysql(buf,1,sql2)){
                cout<<"sql register wrong\n"<<endl;
                return;
            }
            if(sql2.size()==0) return;
            string name=sql2.front();

            sprintf(buf,"select f_size,f_path,f_count,f_MD5,f_type from t_file where f_id=%d;",rq.fileid);

            if(!m_sql->SelectMysql(buf,5,sql)){
                cout<<"sql register wrong\n"<<endl;
                return;
            }

            if(sql.size()==0) return;
            sql.emplace_back(name);
            redis->setHashVals(keybuf,filed,sql);
        }


        info=new FileInfo;

        info->name=sql.back();
        sql.pop_back();
        info->size=stoi(sql.front()); sql.pop_front();
        info->absolutePath=sql.front(); sql.pop_front();
        sql.pop_front();
        info->md5=sql.front(); sql.pop_front();
        info->type=sql.front(); sql.pop_front();

        info->pFile_id=open(info->absolutePath.c_str(),O_RDONLY);

        if(info->pFile_id<0){
            cout<<"open file wrong"<<endl;
            return;
        }

        m_mapIdToInfo.insert(keyid,info);



    }
    //没有存储则创建，有则直接使用
       lseek(info->pFile_id,rq.pos,SEEK_SET);
       info->pos=rq.pos;
       //发文件内容
       STRU_FILE_CONTENT_RQ d_rq;
       d_rq.fileid=info->fileid;

       d_rq.len=read(info->pFile_id,d_rq.content,_DEF_BUFFER);
       if(d_rq.len<=0){
           cout<<"read fail"<<endl;
           return;
       }
       d_rq.timestamp=rq.timestamp;
       d_rq.userid=rq.userid;

       m_pKernel->SendData(clientfd,(char*)&d_rq,sizeof(d_rq));



}

void CLogic::deal_Continue_Upload_Rq(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_CONTINUE_UPLOAD_RQ rq=*(STRU_CONTINUE_UPLOAD_RQ*)szbuf;
    char buf[1024]="";
    list<string>sql;
    FileInfo *info;
    int64_t keyid=rq.userid*(this->getNumber())+rq.timestamp;

    if(!m_mapIdToInfo.find(keyid,info)){
        list<string>filed;
        list<string>sql2;
        list<string>sql;
        filed.emplace_back("f_size");
        filed.emplace_back("f_path");
        filed.emplace_back("f_count");
        filed.emplace_back("f_MD5");
        filed.emplace_back("f_type");
        filed.emplace_back("f_name");
        char keybuf[1024]="";

        sprintf(keybuf,"file_info_id:%d",rq.fileid);
        //文件信息
        if(redis->isExist(keybuf)){
            redis->getHashVals(keybuf,filed,sql);
        }else{
            char buf[1024]="";
            sprintf(buf,"select f_name from t_user_file where f_id=%d;",rq.fileid);
            if(!m_sql->SelectMysql(buf,1,sql2)){
                cout<<"sql register wrong\n"<<endl;
                return;
            }
            if(sql2.size()==0) return;
            string name=sql2.front();

            sprintf(buf,"select f_size,f_path,f_count,f_MD5,f_type from t_file where f_id=%d;",rq.fileid);

            if(!m_sql->SelectMysql(buf,5,sql)){
                cout<<"sql register wrong\n"<<endl;
                return;
            }

            if(sql.size()==0) return;
            sql.emplace_back(name);
            redis->setHashVals(keybuf,filed,sql);
        }


        info=new FileInfo;

        info->name=sql.back();
        sql.pop_back();
        info->size=stoi(sql.front()); sql.pop_front();
        info->absolutePath=sql.front(); sql.pop_front();
        sql.pop_front();
        info->md5=sql.front(); sql.pop_front();
        info->type=sql.front(); sql.pop_front();

        info->pFile_id=open(info->absolutePath.c_str(),O_WRONLY);
        cout<<info->name<<' '<<info->absolutePath<<endl;
        if(info->pFile_id<0){
            cout<<"open file wrong"<<endl;
            return;
        }

        m_mapIdToInfo.insert(keyid,info);

    }
    //获取当前文件大小（偏移量）
    info->pos=lseek(info->pFile_id,0,SEEK_END);

    STRU_CONTINUE_UPLOAD_RS rs;

    rs.fileid=rq.fileid;
    rs.pos=info->pos;
    rs.timestamp=rq.timestamp;


    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));

}

void CLogic::DownloadFile(int userid, int &timestamp, sock_fd clientfd, list<string> &lstres)
{
    int f_id=stoi(lstres.front()); lstres.pop_front();
    string path=lstres.front(); lstres.pop_front();
    int size=stoi(lstres.front()); lstres.pop_front();
    string MD5= lstres.front(); lstres.pop_front();
    string dir=lstres.front(); lstres.pop_front();
    string name=lstres.front(); lstres.pop_front();
    cout<<"file:"<<name<<' '<<dir<<endl;

    FileInfo *info=new FileInfo;

    info->name=name;
    info->size=size;
    info->absolutePath=path;
    info->md5=MD5;
    info->type="file";
    int64_t keyid=userid*(this->getNumber())+(++timestamp);//文件的时间戳++

    info->pFile_id=open(info->absolutePath.c_str(),O_RDONLY);

    if(info->pFile_id<0){
        cout<<"open file wrong"<<endl;
        return;
    }

    m_mapIdToInfo.insert(keyid,info);

    STRU_FILE_HEADER_RQ headRq;
    strcpy(headRq.dir,dir.c_str());
    headRq.fileid=f_id;
    strcpy(headRq.fileName,info->name.c_str());
    strcpy(headRq.fileType,info->type.c_str());
    strcpy(headRq.md5,info->md5.c_str());
    headRq.size=info->size;
    headRq.timestamp=timestamp;
    m_pKernel->SendData(clientfd,(char*)&headRq,sizeof(headRq));

}


void CLogic::sendInfo(int id)
{
    cout<<__func__<<endl;
    _friend_message user_info;
    user_info.id=id;
    getInfo(id,&user_info);
    cout<<user_info.name<<' '<<user_info.iconid<<endl;
    _friend_message friend_message;
    //查找好友并发送自己信息 将好友信息发给我

    char fri_buf[1024]="";
    sprintf(fri_buf,"frined_%d",id);
    list<string>my_fri;
    //if(redis->isExist(fri_buf)) redis->removeKey(fri_buf);

    if(redis->isExist(fri_buf)){
        redis->getList(fri_buf,my_fri);
    }else{

        char buf[1024]="";
        sprintf(buf,"select idB from user_friend where idA=%d;",id);

        if(!m_sql->SelectMysql(buf,1,my_fri)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        redis->setList(fri_buf,my_fri);

    }


    if(my_fri.size()>0){
    char keybuf[1024]="friend_epoll_1";
    list<string>fid;
    list<string>sock_cl;
    map<int,int>m_frend;
    //cout<<"fd->id"<<endl;
    redis->hgetall(keybuf,sock_cl,fid);//所有在线好友
    cout<<"---------------------"<<endl;
    cout<<fid.size()<<endl;
    while(fid.size()!=0){
        cout<<stoi(sock_cl.front())<<' '<<stoi(fid.front())<<endl;
        m_frend[stoi(fid.front())]=stoi(sock_cl.front());//id+sockfd
        sock_cl.pop_front();
        fid.pop_front();

    }

m_pKernel->SendData(m_frend[user_info.id],(char*)&user_info,sizeof(user_info));
    while(my_fri.size()>0){

        friend_message.id=stoi(my_fri.front());

        getInfo(friend_message.id,&friend_message);
        //cout<<friend_message.name<<endl;
        my_fri.pop_front();

        if(m_frend.count(user_info.id)>0){
         //
            m_pKernel->SendData(m_frend[user_info.id],(char*)&friend_message,sizeof(friend_message));
        }
    }

}
}

void CLogic::getInfo(int id,_friend_message* f_mes)
{

    list<string>o;
    o.emplace_back("name");
    o.emplace_back("feeling");
    o.emplace_back("icon_id");
    list<string>val;
    char key_info[1024]="";
    sprintf(key_info,"info_%d",id);
    if(redis->isExist(key_info)){
        redis->getHashVals(key_info,o,val);
    }else{
        char buf[1024]="";
        sprintf(buf,"select *from user_info where userid=%d;",id);
        if(!m_sql->SelectMysql(buf,4,val)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
         if(val.size()!=0){ \
         val.pop_front();
        redis->setHashVals(key_info,o,val);
        }
    }
    if(val.size()!=0){
    strcpy(f_mes->name,val.front().c_str());
    val.pop_front();
    strcpy(f_mes->feeling,val.front().c_str());
    val.pop_front();
    f_mes->iconid=stoi(val.front());
    }
}

void CLogic::addfriend(sock_fd clientfd, char *szbuf, int nlen)
{
    _addfriend_RQ rq=*(_addfriend_RQ*)szbuf;
    cout<<rq.my_name<<' '<<rq.my_id<<' '<<rq.friend_name<<endl;

    //缓存添加好友请求
    list<string>sql;
    char db_sql[1024] = "";
    //数据库中查找添加的好友
    sprintf(db_sql, "select userid from user_info where name='%s';",rq.friend_name);
    if(!m_sql->SelectMysql(db_sql,1,sql)){
        cout<<"sql register wrong\n"<<endl;
        return;
    }
    if(!sql.size()){
     _addfriend_RS rs;
     rs.status=_add_friend_phone_not;
     m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
    }
    int f_id=stoi(sql.front());
    sprintf(db_sql,"insert into friend_add values(%d,%d,'%s')",rq.my_id,f_id,rq.my_name);

    if (!m_sql->UpdataMysql(db_sql)) {
        cout << "插入失败" << endl;
        return;
    }

    char keybuf2[1024]="";
    sprintf(keybuf2,"addfriend_rq:%d",f_id);
    if(redis->isExist(keybuf2)) redis->removeKey(keybuf2);

//    char keybuf[1024]="friend_epoll_1";
//    list<string>fid;
//    list<string>sock_cl;
//    map<int,int>m_frend;
//    redis->hgetall(keybuf,sock_cl,fid);
//    while(fid.size()!=0){
//        //cout<<stoi(sock_cl.front())<<' '<<stoi(fid.front())<<endl;
//        m_frend[stoi(fid.front())]=stoi(sock_cl.front());
//        sock_cl.pop_front();
//        fid.pop_front();

//    }
//    if()

}

void CLogic::sendFriendrq(int id,sock_fd clientfd)
{
    cout<<__func__<<endl;
    cout<<id<<' '<<clientfd<<endl;
    char keybuf[1024]="";
    sprintf(keybuf,"addfriend_rq:%d",id);
    list<string>filed;
    list<string>vals;
    cout<<keybuf<<endl;
    if(redis->isExist(keybuf)){

        redis->hgetall(keybuf,filed,vals);
    }else{
        char buf[1024]="";
        list<string>sql;
        sprintf(buf,"select userid,username from friend_add where friendid=%d;",id);
        if(!m_sql->SelectMysql(buf,2,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        if(sql.size()==0) return;
        else{
            while(sql.size()!=0){
                cout<<sql.front()<<endl;
                filed.emplace_back(sql.front());
                sql.pop_front();
                vals.emplace_back(sql.front());
                sql.pop_front();

            }
        }
      redis->setHashVals(keybuf,filed,vals);
    }
    _addfriend_RQ rq;
    while(filed.size()>0){
        rq.my_id=stoi(filed.front());
        strcpy(rq.my_name,vals.front().c_str());
        filed.pop_front();
        vals.front();
        m_pKernel->SendData(clientfd,(char*)&rq,sizeof(rq));
    }


}


void CLogic::Send_Sms(sock_fd clientfd, char *szbuf, int nlen)
{
    cout<<__func__<<endl;
    srand(static_cast<unsigned int>(time(0)));
    STRU_SMS_RQ rq=*(STRU_SMS_RQ*)szbuf;

    // 生成一个范围在1000到9999之间的随机数
    int random_number = 1000 + rand() % 9000;
    char keybuf[1024]="";

    sprintf(keybuf,"sms_%s",rq.tel);
    if(redis->isExist(keybuf)){
        return;
    }
    redis->setex(keybuf,to_string(random_number),60);
    cout<<rq.tel<<random_number<<endl;
    char sms[1024]="";
    sprintf(sms,"{\"code\":\"%d\"}",random_number);
    cout<<sms<<endl;
//        AlibabaCloud::InitializeSdk();
//        AlibabaCloud::ClientConfiguration configuration( "cn-beijing" );
//        // specify timeout when create client.
//        configuration.setConnectTimeout(1500);
//        configuration.setReadTimeout(4000);
//        AlibabaCloud::Credentials credential(
//        "LTAI5tAx353tHFCZZTd7chhf", "Cpxj1CC8W7WxYqVXlEKrfYaWog9IYL" ); //todo 完成替换
//        AlibabaCloud::CommonClient client( credential, configuration );
//        AlibabaCloud::CommonRequest
//        request(AlibabaCloud::CommonRequest::RequestPattern::RpcPattern);
//        request.setHttpMethod(AlibabaCloud::HttpRequest::Method::Post);
//        request.setDomain("dysmsapi.aliyuncs.com");
//        request.setVersion("2017-05-25");
//        request.setQueryParameter("Action", "SendSms");
//        request.setQueryParameter("SignName", "阿里云短信测试");
//        request.setQueryParameter("TemplateCode", "SMS_154950909");
//        request.setQueryParameter("PhoneNumbers", "19990780451"); //todo 完成替换
//        request.setQueryParameter("TemplateParam", sms); //todo 完成替换
//        auto response = client.commonResponse(request);
//        if (response.isSuccess()) {
//            printf("request success.\n");
//            printf("result: %s\n", response.result().payload().c_str());
//        } else {
//            printf("error: %s\n", response.error().errorMessage().c_str());
//            printf("request id: %s\n", response.error().requestId().c_str());
//        }
//        AlibabaCloud::ShutdownSdk();

}

void CLogic::deal_chatRq(sock_fd clientfd, char *szbuf, int nlen)
{

    STRU_CHAR_RQ rq=*(STRU_CHAR_RQ*)szbuf;
    char fri_buf[1024]="";
    sprintf(fri_buf,"frined_%d",rq.my_id);
    list<string>my_fri;
    //if(redis->isExist(fri_buf)) redis->removeKey(fri_buf);
    cout<<"chat:"<<rq.content<<' '<<rq.my_id<<endl;

    int sockfd=-1;
    char keybuf[1024]="friend_epoll_1";
    list<string>fid;
    list<string>sock_cl;
    map<int,int>m_frend;
    //cout<<"fd->id"<<endl;
    redis->hgetall(keybuf,sock_cl,fid);//所有在线好友

    while(fid.size()!=0){
        int fr_id=stoi(fid.front());
        if(fr_id==rq.friendid){
            sockfd=stoi(sock_cl.front());
            break;
        }
        sock_cl.pop_front();
        fid.pop_front();
}
    if(sockfd==-1){
        STRU_CHAR_RS rs;
        rs.friendid=rq.friendid;
        rs.result=_offline;
        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
    }
    m_pKernel->SendData(sockfd,(char*)&rq,sizeof(rq));
}

void CLogic::deal_addRs(sock_fd clientfd, char *szbuf, int nlen)
{
    cout<<__func__<<endl;

    _addfriend_RS rs=*(_addfriend_RS*)szbuf;
    cout<<rs.status<<endl;
    char buf[1024]="";
    if(rs.status==_add_friend_success){
        sprintf(buf,"insert into user_friend values(%d,%d)",rs.friendid,rs.my_id);
        if(!m_sql->UpdataMysql(buf)) {
           cout << "插入失败" << endl;
            return;
        }
        sprintf(buf,"insert into user_friend values(%d,%d)",rs.my_id,rs.friendid);
        if(!m_sql->UpdataMysql(buf)) {
            cout << "插入失败" << endl;
             return;
        }
        char keybuf[1024]="";
        sprintf(keybuf,"addfriend_rq:%d",rs.my_id);
        if(redis->isExist(keybuf)) redis->removeKey(keybuf);
        sprintf(keybuf,"frined_%d",rs.my_id);
        if(redis->isExist(keybuf)) redis->removeKey(keybuf);
        sprintf(keybuf,"frined_%d",rs.friendid);
        if(redis->isExist(keybuf)) redis->removeKey(keybuf);
        sendInfo(rs.my_id);
    }else {

    }
    sprintf(buf,"delete from friend_add where friendid=%d;",rs.my_id);
    if(!m_sql->UpdataMysql(buf)) {
        cout << "插入失败" << endl;
         return;
    }
}



