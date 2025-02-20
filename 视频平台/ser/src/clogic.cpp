#include "clogic.h"
#include<stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype> // for std::isspace
#include <cstdlib> // 包含rand()和srand()
#include <ctime>   // 包含time()
#include <alibabacloud/core/AlibabaCloud.h>
#include <alibabacloud/core/CommonRequest.h>
#include <alibabacloud/core/CommonClient.h>
#include <alibabacloud/core/CommonResponse.h>
#include"packdef.h"

using namespace std;
using namespace AlibabaCloud;
void CLogic::setNetPackMap()
{
    NetPackMap(_DEF_PACK_REGISTER_RQ)    = &CLogic::RegisterRq;
    NetPackMap(_DEF_PACK_LOGIN_RQ)       = &CLogic::LoginRq;
    NetPackMap(_DEF_PACK_UPLOAD_RQ)      =&CLogic::uploadRq;
    NetPackMap(_DEF_PACK_FILEBLOCK)      =&CLogic::block_upload;
    NetPackMap(_DEF_PACK_DOWNLOAD_RQ)    =&CLogic::Download_RQ;
    NetPackMap(_DEF_PACK_COMMENT_PUBLISH_RQ)=&CLogic::Pub_Comment;
    NetPackMap(_DEF_PACK_COMMENT_RQ)     =&CLogic::Get_comment;
    NetPackMap(_DEF_PACK_SMS_RQ)         =&CLogic::Send_Sms;
    NetPackMap(_DEF_PACK_PLIKE_RQ)       =&CLogic::Count_Plke;
    NetPackMap(_DEF_PACK_GETRM_RQ)       =&CLogic::Get_recomm;
    NetPackMap(_DEF_ADD_FRIEND_RQ)       =&CLogic::addfriend;

}

#define _DEF_COUT_FUNC_    cout << "clientfd:"<< clientfd << __func__ << endl;

//注册
void CLogic::RegisterRq(sock_fd clientfd,char* szbuf,int nlen)
{
    //cout << "clientfd:"<< clientfd << __func__ << endl;
    _DEF_COUT_FUNC_

            STRU_REGISTER_RQ *reg=(STRU_REGISTER_RQ*)szbuf;

    //cout<<reg->name<<endl;
    //cout<<reg->m_szHobby[0]<<reg->m_szHobby[1]<<reg->m_szHobby[2]<<reg->m_szHobby[3]<<reg->m_szHobby[4]<<endl;
    list<string>sql;
    char buf[1024]="";
    char keybuf[1024]="";
    STRU_REGISTER_RS rs;

    sprintf(keybuf,"sms_%s",reg->tel);
    cout<<keybuf<<endl;

    if(redis->isExist(keybuf)){
        string sms;
        redis->getString(keybuf,sms);
        cout<<sms<<endl;
        //cout<<reg->Sms<<' '<<sms<<endl;
        if(strcmp(reg->Sms,sms.c_str())==0){
            rs.result=sms_wrong;

            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
            return;
        }
    }else{
        rs.result=sms_empire;
        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
        return;
    }

    int user_id_item;
    if(redis->isExist(reg->tel)){
        //hash
        cout<<"tel exist"<<endl;
        rs.result=tel_is_exist;
        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
        return;

    }
    else{
        sprintf(buf,"select user_id,name,password from user where tel='%s';",reg->tel);
        if(!m_sql->SelectMysql(buf,3,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        if(sql.size()!=0){
            cout<<"tel exist"<<endl;
            list<string>filed;
            filed.emplace_back("user_id");
            filed.emplace_back("name");
            filed.emplace_back("password");
            list<string>val;
            val.emplace_back(sql.front());
            user_id_item=stoi(sql.front());

            sql.pop_front();

            val.emplace_back(sql.front());
            sql.pop_front();
            val.emplace_back(sql.front());
            sql.pop_front();
            redis->setHashVals(reg->tel,filed,val);

            rs.result=tel_is_exist;
            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
            return;
        }
    }//
    //    sprintf(buf,"select name from user where name='%s';",reg->name);
    //    if(!m_sql->SelectMysql(buf,1,sql)){
    //        cout<<"sql register wrong\n"<<endl;
    //        return;
    //    }

    //    if(sql.size()!=0){
    //        cout<<"name exists"<<endl;
    //        rs.result=user_is_exist;
    //        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
    //        return;
    //    }
    sprintf(buf,"insert into user values(NULL,'%s','%s','%s','%c','%c','%c','%c','%c');",reg->name,reg->tel,reg->password,reg->m_szHobby[0],reg->m_szHobby[1],reg->m_szHobby[2],reg->m_szHobby[3],reg->m_szHobby[4]);
    if (!m_sql->UpdataMysql(buf)) {
        cout << "插入失败" << endl;
        return;
    }else{

        //插入用户列表信息


        list<string>sid;
        sprintf(buf,"select user_id from user where tel='%s';",reg->tel);
        if(!m_sql->SelectMysql(buf,1,sid)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        char key_info[1024]="";

        int id=stoi(sid.front());
        list<string>o;
        o.emplace_back("name");
        o.emplace_back("feeling");
        o.emplace_back("icon_id");

        sprintf(key_info,"info_%d",id);
        if(redis->isExist(key_info)){

        }else{
            sprintf(buf,"insert into user_info values(%d,'%s','hello',28);",id,reg->name);
            if (!m_sql->UpdataMysql(buf)) {
                cout << "插入失败" << endl;
                return;
            }else{
                list<string>lv;
                lv.emplace_back(reg->name);
                lv.emplace_back("hello");
                lv.emplace_back("28");
                redis->setHashVals(key_info,o,lv);
            }


            char user_buf[1024];
            sprintf(user_buf,"user_type_%d",id);
            list<string>filed;
            filed.emplace_back("food");
            filed.emplace_back("life");
            filed.emplace_back("cartoon");
            filed.emplace_back("game");
            filed.emplace_back("music");
            list<string>vals;
            for(int i=0;i<5;i++) vals.emplace_back(string(1, reg->m_szHobby[i]));

            redis->setHashVals(user_buf,filed,vals);

            const char *folderName = reg->name;            // 文件夹名称
            char path[1024];

            // 构造完整路径
            snprintf(path, sizeof(path), "%s/flv/%s", ROOTPATH, folderName);

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
            sprintf(buf,"insert into user_info values(%d,'%s','hello',28);",id,reg->name);
            if (!m_sql->UpdataMysql(buf)) {
                cout << "插入失败" << endl;
                return;
            }else{
                list<string>lv;
                lv.emplace_back(reg->name);
                lv.emplace_back("hello");
                lv.emplace_back("28");
                redis->setHashVals(key_info,o,lv);
            }
            rs.result=register_success;
        }
    }
    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
}

//登录
void CLogic::LoginRq(sock_fd clientfd ,char* szbuf,int nlen)
{
    //    cout << "clientfd:"<< clientfd << __func__ << endl;
    _DEF_COUT_FUNC_

            STRU_LOGIN_RQ*rq=(STRU_LOGIN_RQ*)szbuf;
    list<string>sql;
    char buf[1024]="";
    STRU_LOGIN_RS rs;
    //cout<<rq->tel<<endl;

    if(redis->isExist(rq->tel)){

        string password;
        string u_id;
        redis->getHashVal(rq->tel,"password",password);
        redis->getHashVal(rq->tel,"user_id",u_id);
        sql.emplace_back(u_id);
        sql.emplace_back(password);
    }else{
        sprintf(buf,"select user_id,password from user where tel='%s';",rq->tel);
        if(!m_sql->SelectMysql(buf,2,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        if(sql.size()==0){
            rs.result=user_not_exist;
            m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
            return;
        }
        redis->setHashVal(rq->tel,"user_id",sql.front());
        redis->setHashVal(rq->tel,"password",sql.back());
    }

    int my_id=stoi(sql.front());//user_id

    if(strcmp(sql.back().c_str(),rq->password)){
        rs.result=password_error;
        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));
    }else{
        rs.result=login_success;
        rs.userid=atoi(sql.front().c_str());
        list<string>a;
        a.emplace_back("user_id");
        a.emplace_back("videoName");
        a.emplace_back("videoPath");
        a.emplace_back("rtmp");
        a.emplace_back("food");
        a.emplace_back("life");
        a.emplace_back("cartoon");
        a.emplace_back("game");
        a.emplace_back("music");
        char buf2[1024]="";
        // int i=4;
        int p=5;
        //int play_sum=15;
        char buu[1024]="";
        sprintf(buu,"user_type_%d",stoi(sql.front()));
        list<string>bfl;
        list<string>like_rec;
        char holike[5];
        bfl.emplace_back("food");
        bfl.emplace_back("life");
        bfl.emplace_back("cartoon");
        bfl.emplace_back("game");
        bfl.emplace_back("music");

        redis->getHashVals(buu,bfl,like_rec);
        for(int i=0;i<5;i++){
            holike[i]=like_rec.front()[0];

            like_rec.pop_front();
        }
        //替换为根据喜好类型进行数据推送 （推送数量自己设置）
        for(int j=0;j<5;j++){
            if(holike[j]=='1'){
                sprintf(buu,"file_type_%d",j+1);//1-5
                list<string>vi_id;
                redis->getList(buu,vi_id);
                while(!vi_id.empty()){
                    int i=stoi(vi_id.front());

                    vi_id.pop_front();
                    STRU_RTMP_RQ rt_Rq;
                    sql.clear();
                    memset(buf2,0,1024);
                    char keybuf[1024]="";
                    sprintf(keybuf,"fileInfo_id=%d",i);
                    if(redis->isExist(keybuf)){
                        //cout<<"fileInfo_id"<<endl;
                        redis->getHashVals(keybuf,a,sql);
                    }else{
                        sprintf(buf2,"select * from video_user where video_id='%d';",i);

                        if(!m_sql->SelectMysql(buf2,10,sql)){
                            //  cout<<"sql register wrong\n"<<endl;
                            return;
                        }
                        if(sql.size()==0){
                            break;
                        }

                        sql.pop_front();
                        redis->setHashVals(keybuf,a,sql);
                    }
                    STRU_PLIKE_RS plike_rs;
                    list<string>sql_like;
                    list<string>key;
                    key.emplace_back("video_like");
                    key.emplace_back("video_play");
                    sprintf(keybuf,"Plike_file_id=%d",i);

                    if(redis->isExist(keybuf)){
                        //cout<<"Plike_file_id"<<endl;
                        redis->getHashVals(keybuf,key,sql_like);

                    }else{
                        sql_like.clear();
                        char buf3[1024]="";
                        sprintf(buf3,"select video_like,video_play from video_plike where video_id='%d';",i);
                        if(!m_sql->SelectMysql(buf3,2,sql_like)){
                            cout<<"sql register wrong\n"<<endl;
                            return;
                        }

                        redis->setHashVals(keybuf,key,sql_like);
                    }
                    // cout<<sql_like.back()<<endl;
                    plike_rs.file_id=i;
                    plike_rs.like=stoi(sql_like.front());
                    plike_rs.play=stoi(sql_like.back());//s->int

                    m_pKernel->SendData(clientfd,(char*)&plike_rs,sizeof(plike_rs));


                    rt_Rq.fileId=i;
                    rt_Rq.user_id=atoi(sql.front().c_str());
                    sql.pop_front();
                    strcpy(rt_Rq.fileName,sql.front().c_str());
                    sql.pop_front();
                    sql.pop_front();
                    strcpy(rt_Rq.filepath,sql.front().c_str());

                    sql.pop_front();

                    for(int i=0;i<5;i++){
                        //                        char keybuf[1024]="";
                        //                        sprintf(keybuf,"file_type_%d",i+1);
                        //                        if(sql.front()[0]=='1'){
                        ////                            if(redis->isExist(keybuf)){
                        ////                                redis->removeKey(keybuf);
                        ////                            }

                        //                            redis->appendOneToList(keybuf,to_string(rt_Rq.fileId));
                        //                        }

                        rt_Rq.m_szHobby[i]=sql.front()[0];
                        sql.pop_front();
                    }

                    //cout<<rt_Rq.fileId<<' '<<rt_Rq.fileName<<' '<<rt_Rq.filepath<<' '<<rt_Rq.user_id<<' '<<rt_Rq.m_szHobby<<endl;
                    m_pKernel->SendData(clientfd,(char*)&rt_Rq,sizeof(rt_Rq));



                }
            }
        }
        //            while(p--){

        //                STRU_RTMP_RQ rt_Rq;
        //                sql.clear();
        //                memset(buf2,0,1024);
        //                char keybuf[1024]="";
        //                sprintf(keybuf,"fileInfo_id=%d",i);
        //                if(redis->isExist(keybuf)){
        //                    redis->getHashVals(keybuf,a,sql);
        //                }else{
        //                sprintf(buf2,"select * from video_user where video_id='%d';",i);

        //                    if(!m_sql->SelectMysql(buf2,10,sql)){
        //                       cout<<"sql register wrong\n"<<endl;
        //                        return;
        //                    }
        //                    if(sql.size()==0){
        //                        break;
        //                    }

        //                    sql.pop_front();
        //                    redis->setHashVals(keybuf,a,sql);
        //                 }
        //                    STRU_PLIKE_RS plike_rs;
        //                    list<string>sql_like;
        //                    list<string>key;
        //                    key.emplace_back("video_like");
        //                    key.emplace_back("video_play");
        //                    sprintf(keybuf,"Plike_file_id=%d",i);
        //                    if(redis->isExist(keybuf)){
        //                       redis->getHashVals(keybuf,key,sql_like);

        //                    }else{
        //                        char buf3[1024]="";
        //                        sprintf(buf3,"select video_like,video_play from video_plike where video_id='%d';",i);
        //                        if(!m_sql->SelectMysql(buf3,2,sql_like)){
        //                           cout<<"sql register wrong\n"<<endl;
        //                            return;
        //                        }

        //                        redis->setHashVals(keybuf,key,sql_like);
        //                    }
        //                   // cout<<sql_like.back()<<endl;
        //                    plike_rs.file_id=i;
        //                    plike_rs.like=stoi(sql_like.front());
        //                    plike_rs.play=stoi(sql_like.back());//s->int

        //                    m_pKernel->SendData(clientfd,(char*)&plike_rs,sizeof(plike_rs));


        //                    rt_Rq.fileId=i;
        //                    rt_Rq.user_id=atoi(sql.front().c_str());
        //                    sql.pop_front();
        //                    strcpy(rt_Rq.fileName,sql.front().c_str());
        //                    sql.pop_front();
        //                    sql.pop_front();
        //                    strcpy(rt_Rq.filepath,sql.front().c_str());

        //                    sql.pop_front();

        //                    for(int i=0;i<5;i++){
        ////                        char keybuf[1024]="";
        ////                        sprintf(keybuf,"file_type_%d",i+1);
        ////                        if(sql.front()[0]=='1'){
        //////                            if(redis->isExist(keybuf)){
        //////                                redis->removeKey(keybuf);
        //////                            }

        ////                            redis->appendOneToList(keybuf,to_string(rt_Rq.fileId));
        ////                        }

        //                        rt_Rq.m_szHobby[i]=sql.front()[0];
        //                        sql.pop_front();
        //                    }

        //                    //cout<<rt_Rq.fileId<<' '<<rt_Rq.fileName<<' '<<rt_Rq.filepath<<' '<<rt_Rq.user_id<<' '<<rt_Rq.m_szHobby<<endl;
        //                    m_pKernel->SendData(clientfd,(char*)&rt_Rq,sizeof(rt_Rq));


        //                i++;
        //            }
        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));

        char keybuf[1024]="friend_epoll_1";
        redis->setHashVal(keybuf,to_string(clientfd),to_string(my_id));
        sendInfo(my_id);
        sendFriendrq(my_id,clientfd);
    }

}


void CLogic::uploadRq(sock_fd clientfd, char *szbuf, int nlen)
{
    cout<<__func__<<endl;
    STRU_UPLOAD_RQ *req=(STRU_UPLOAD_RQ*)szbuf;
    list<string>sql;
    cout<<req->m_nFileId<<' '<<req->m_nFileSize<<' '<<req->m_scFileName;
    FileInfo* info=new FileInfo;
    info->m_nFileID=req->m_nFileId;
    info->m_nFileSize=req->m_nFileSize;
    info->m_nUserId=req->user_id;
    info->m_nPos=0;
    info->m_VideoId=0;
    strcpy(info->m_szFileName,req->m_scFileName);
    strcpy(info->m_szFileType,req->m_szFileType);
    strcpy(info->m_Hobby,req->m_szHobby);
    cout<<info->m_Hobby<<endl;
    char keybuf[1024]="";
    char buf[1024]="";
    char name[1024]="";
    sprintf(keybuf,"id_name=%d",req->user_id);

    if(redis->isExist(keybuf)){
        string name;
        redis->getString(keybuf,name);
        sql.push_back(name);
    }else{
        sprintf(buf,"select name from user where user_id='%d';",req->user_id);
        if(!m_sql->SelectMysql(buf,1,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        if(sql.size()==0){
            cout<<"name if empty"<<endl;
            return;
        }
        redis->setString(keybuf,sql.front().c_str());
    }
    strcpy(info->m_USerName,sql.front().c_str());
    sprintf(info->m_szFilePath,"%sflv/%s/%s",ROOTPATH,info->m_USerName,info->m_szFileName);
    sprintf(info->m_szRtmp,"//%s/%s",info->m_USerName,info->m_szFileName);
    cout<<info->m_szFilePath<<endl;
    if((info->pFile=fopen(info->m_szFilePath,"w"))==NULL){
        cout<<"fopen wrong"<<endl;
        return;
    }

    m_mapFileinfo[info->m_nUserId]=info;
}

void CLogic::block_upload(sock_fd clientfd, char *szbuf, int nlen)
{

    STRU_FILEBLOCK_RQ rq=*(STRU_FILEBLOCK_RQ*)szbuf;
    if(m_mapFileinfo.find(rq.m_userid)==m_mapFileinfo.end()) return;
    //cout<<rq.m_userid<<endl;
    FileInfo* info=m_mapFileinfo[rq.m_userid];
    info->m_nFileID=rq.m_nFileId;

    int64_t res=fwrite(rq.m_szFileContent,1,rq.m_nBlock_Len,info->pFile);
    info->m_nPos+=res;
    if(info->m_nPos>=info->m_nFileSize||rq.m_nBlock_Len<_DEF_BUFFER){
        fclose(info->pFile);
        char buf[1024]="";
        char buf1[1024]="";
        list<string>sql;


        //        sprintf(buf1,"select user_id from video_user where videoName='%s';",info->m_szFileName);
        //        if(!m_sql->SelectMysql(buf1,1,sql)){
        //            cout<<"sql register wrong\n"<<endl;
        //            return;
        //        }

        if(sql.size()==0){

            sprintf(buf,"insert into video_user values(NULL,'%d','%s','%s','%s','%c','%c','%c','%c','%c');",info->m_nUserId,info->m_szFileName,info->m_szFilePath,info->m_szRtmp,info->m_Hobby[0],info->m_Hobby[1],info->m_Hobby[2],info->m_Hobby[3],info->m_Hobby[4]);
            if (!m_sql->UpdataMysql(buf)) {
                cout << "插入失败" << endl;
                return;
            }
            list<string>sql2;
            char buf2[1024]="";
            sprintf(buf2,"select video_id from video_user where videoName='%s';",info->m_szFileName);
            if(!m_sql->SelectMysql(buf2,1,sql2)){
                cout<<"sql register wrong\n"<<endl;
                return;
            }
            int a=stoi(sql2.back());
            sprintf(buf,"insert into video_plike values('%d',0,0)",a);
            if (!m_sql->UpdataMysql(buf)) {
                cout << "插入失败" << endl;
                return;
            }

            for(int i=0;i<5;i++){
                if(info->m_Hobby[i]=='1'){
                    char keybuf[1024]="";
                    sprintf(keybuf,"file_type_%d",i+1);

                    cout<<"fileid "<<a<<endl;
                    redis->appendOneToList(keybuf,to_string(a));
                }
            }

        }

        STRU_UPLOAD_RS rs;
        rs.Result=upload_success;
        m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));

        m_mapFileinfo.erase(rq.m_userid);
        delete info;
        info=NULL;
    }

}


//for(int i=0;i<5;i++){
//    if(info->m_Hobby[i]=='1'){
//        char keybuf[1024]="";
//        sprintf(keybuf,"file_type_%d",i+1);

//        cout<<"fileid "<<rq.m_nFileId<<endl;
//        //redis->appendOneToList(keybuf,to_string(rq.m_nFileId));
//    }
//}
void CLogic::Download_RQ(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_DOWNLOAD_RQ rq=*(STRU_DOWNLOAD_RQ*)szbuf;
    cout<<__func__<<endl;
    cout<<rq.FileId<<' '<<rq.userId<<endl;
    char buf[1024]="";
    list<string>sql;
    char keybuf[1024]="";
    list<string>a;
    a.emplace_back("user_id");
    a.emplace_back("videoName");
    a.emplace_back("videoPath");
    a.emplace_back("rtmp");
    a.emplace_back("food");
    a.emplace_back("life");
    a.emplace_back("cartoon");
    a.emplace_back("game");
    a.emplace_back("music");
    sprintf(keybuf,"fileInfo_id=%d",rq.FileId);
    if(redis->isExist(keybuf)){
        redis->getHashVals(keybuf,a,sql);
    }else{
        sprintf(buf,"select videoName,videoPath,rtmp,food,life,cartoon,game,music from video_user where video_id='%d'",rq.FileId);
        if(!m_sql->SelectMysql(buf,8,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        sql.push_front(to_string(rq.userId));
        redis->setHashVals(keybuf,a,sql);
    }

    sql.pop_front();
    char hobby[5]="";
    string name=sql.front();
    sql.pop_front();
    string path=sql.front();
    sql.pop_front();
    string rtmp=sql.front();
    sql.pop_front();
    for(int i=0;i<5;i++){

        hobby[i]=sql.front()[0];
        sql.pop_front();
    }
    FileInfo *file=new FileInfo;
    file->m_nPos=0;
    file->m_nFileID=rq.FileId;
    file->m_nUserId=rq.userId;
    strcpy(file->m_szFileName,name.c_str());
    strcpy(file->m_szFilePath,path.c_str());
    if((file->pFile=fopen(file->m_szFilePath,"r"))==NULL){
        cout<<"file fopen wrong"<<endl;

    }

    fseek(file->pFile,0,SEEK_END);
    file->m_nFileSize=ftell(file->pFile);
    fseek(file->pFile,0,SEEK_SET);
    fclose(file->pFile);
    STRU_DOWNLOAD_RS rs;
    rs.m_nFileSize=file->m_nFileSize;
    strcpy(rs.m_scFileName,name.c_str());
    rs.file_id=rq.FileId;
    cout<<file->m_szFilePath<<endl;
    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));//先发文件头
    if(file->pFile=fopen(file->m_szFilePath,"r")){
        int i=0;
        while(1){
            STRU_FILEBLOCK_RQ blockrq;
            int64_t res=fread(blockrq.m_szFileContent,1,_DEF_BUFFER,file->pFile);
            file->m_nPos+=res;
            blockrq.m_nBlock_Len=res;//读取的长度进行传出
            blockrq.m_nFileId=rq.FileId;
            blockrq.m_userid=rq.userId;

            m_pKernel->SendData(clientfd,(char*)&blockrq,sizeof(blockrq));

            if(file->m_nPos>=file->m_nFileSize){
                //cout<<file->m_nPos<<' '<<file->m_nFileSize<<endl;
                fclose(file->pFile);
                delete file;
                file=NULL;
                break;
            }
            // sleep(1);

        }
    }

}

void CLogic::Pub_Comment(sock_fd clientfd, char *szbuf, int nlen)
{
    cout<<__func__<<endl;
    STRU_COMMENT_PUBLISH_RQ rq=*(STRU_COMMENT_PUBLISH_RQ*)szbuf;
    cout<<rq.comment<<' '<<rq.file_id<<' '<<rq.user_id<<endl;
    char buf[1024]="";
    list<string>sql;
    char keybuf[1024]="";
    char name[1024]="";
    sprintf(keybuf,"id_name=%d",rq.user_id);
    if(redis->isExist(keybuf)){
        string a;
        redis->getString(keybuf,a);
        strcpy(name,a.c_str());
    }
    else{
        sprintf(buf,"select name from user where user_id='%d';",rq.user_id);
        if(!m_sql->SelectMysql(buf,1,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }

        strcpy(name,sql.back().c_str());
        redis->setString(keybuf,sql.back());
    }

    char buf2[1024]="";

    sprintf(buf2,"insert into video_message values('%d','%s','%s',NULL,0);",rq.file_id,rq.comment,name);
    if (!m_sql->UpdataMysql(buf2)) {
        cout << "插入失败" << endl;
        return;
    }
    char keybuf2[1024]="";
    sprintf(keybuf2,"comment_%d",rq.file_id);
    if(redis->isExist(keybuf2)){
        redis->removeKey(keybuf2);
    }
    STRU_COMMENT_PUBLISH_RS rs;
    rs.result=comment_sucesss;
    rs.fileid=rq.file_id;
    m_pKernel->SendData(clientfd,(char*)&rs,sizeof(rs));

}
void CLogic::Get_comment(sock_fd clientfd, char *szbuf, int nlen)
{

    STRU_COMMENT_RQ rq=*(STRU_COMMENT_RQ*)szbuf;
    char buf[1024]="";
    list<string>sql;
    //list
    char keybuf[1024]="";
    sprintf(keybuf,"comment_%d",rq.file_id);
    if(redis->isExist(keybuf)){
        redis->getList(keybuf,sql);
    }else{
        sprintf(buf,"select Comment,userName,time from video_message where video_id='%d';",rq.file_id);
        if(!m_sql->SelectMysql(buf,3,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        for( auto ite = sql.begin() ; ite != sql.end() ;  ++ite ){
            for(int i=0;i<(*ite).size();i++){
                if((*ite)[i]==' '){
                    (*ite)[i]=',';
                }
            }
        }
        redis->setList(keybuf,sql);
    }

    cout<<rq.file_id<<' '<<sql.size()<<endl;
    while(sql.size()!=0){

        char name[1024]="";
        char time[1024]="";
        char comment[1024]="";

        strcpy(comment,sql.front().c_str());
        sql.pop_front();
        strcpy(name,sql.front().c_str());
        sql.pop_front();
        strcpy(time,sql.front().c_str());
        sql.pop_front();

        //cout<<name<<' '<<time<<' '<<comment<<endl;
        STRU_COMMENT_RS com_rs;
        strcpy(com_rs.comment,comment);
        strcpy(com_rs.time,time);
        strcpy(com_rs.name,name);
        m_pKernel->SendData(clientfd,(char*)&com_rs,sizeof(com_rs));
    }

}

void CLogic::Send_Sms(sock_fd clientfd, char *szbuf, int nlen)
{
    srand(static_cast<unsigned int>(time(0)));
    STRU_SMS_RQ rq=*(STRU_SMS_RQ*)szbuf;

    // 生成一个范围在1000到9999之间的随机数
    int random_number = 1000 + rand() % 9000;
    char keybuf[1024]="";

}

void CLogic::Count_Plke(sock_fd clientfd, char *szbuf, int nlen)
{

    STRU_PLIKE_RQ rq=*(STRU_PLIKE_RQ*)szbuf;
    cout<<rq.file_id<<' '<<rq.like<<' '<<rq.play<<endl;
    char buf[1024]="";
    sprintf(buf,"UPDATE video_plike SET video_like=video_like+'%d',video_play=video_play+'%d' WHERE video_id = '%d';"
            ,rq.like,rq.play,rq.file_id);
    if (!m_sql->UpdataMysql(buf)) {
        cout << "插入失败" << endl;
        return;
    }

    char keybuf[1024]="";
    sprintf(keybuf,"clientfd:%d",clientfd);//检测连接，更新过期时间
    redis->setEmire(keybuf,_CHECK_ALIVE_TIME);

    sprintf(keybuf,"Plike_file_id=%d",rq.file_id);
    redis->removeKey(keybuf);


    char keybuf2[1024]="";
    char hobby[5]="";
    sprintf(keybuf2,"fileInfo_id=%d",rq.file_id);
    list<string>a;
    a.emplace_back("user_id");
    a.emplace_back("videoName");
    a.emplace_back("videoPath");
    a.emplace_back("rtmp");
    a.emplace_back("food");
    a.emplace_back("life");
    a.emplace_back("cartoon");
    a.emplace_back("game");
    a.emplace_back("music");
    list<string>sql;
    if(redis->isExist(keybuf2)){
        redis->getHashVals(keybuf2,a,sql);
    }else{

        char buf2[1024]="";
        sprintf(buf2,"select * from video_user where video_id='%d';",rq.file_id);
        list<string>sql;
        if(!m_sql->SelectMysql(buf2,10,sql)){
            cout<<"sql register wrong\n"<<endl;
            return;
        }
        sql.pop_front();
        redis->setHashVals(keybuf,a,sql);
    }

    for(int i=4;i>=0;i--){
        hobby[i]=sql.back()[0];
        sql.pop_back();
    }

    //    cout<<hobby[0]<<endl;
    //    cout<<hobby[1]<<endl;
    //    cout<<hobby[2]<<endl;
    //    cout<<hobby[3]<<endl;
    //    cout<<hobby[4]<<endl;

    char userbuf[1024]="";
    sprintf(userbuf,"Plike_user_id=%d",rq.user_id);
    list<string>filed;
    list<string>vals;

    filed.emplace_back("food_play");
    filed.emplace_back("food_like");
    filed.emplace_back("life_play");
    filed.emplace_back("life_like");
    filed.emplace_back("cartoon_play");
    filed.emplace_back("cartoon_like");
    filed.emplace_back("game_play");
    filed.emplace_back("game_like");
    filed.emplace_back("music_play");
    filed.emplace_back("music_like");

    if(redis->isExist(userbuf)){
        list<string>upvals;
        redis->getHashVals(userbuf,filed,vals);
        for(int i=0;i<5;i++){
            if(hobby[i]=='1'){
                int play=stoi(vals.front());
                vals.pop_front();
                int plike=stoi(vals.front());
                vals.pop_front();
                play+=rq.play;
                plike+=rq.like;
                upvals.push_back(to_string(play));
                upvals.push_back(to_string(plike));

            }else{
                upvals.push_back(vals.front());
                vals.pop_front();
                upvals.push_back(vals.front());
                vals.pop_front();
            }
        }
        redis->setHashVals(userbuf,filed,upvals);
    }else {
        for(int i=0;i<5;i++){
            if(hobby[i]=='1'){
                vals.emplace_back(to_string(rq.play));
                vals.emplace_back(to_string(rq.like));
            }else{
                vals.emplace_back("0");
                vals.emplace_back("0");
            }
        }

        redis->setHashVals(userbuf,filed,vals);
    }


}
//获取数据
void CLogic::Get_recomm(sock_fd clientfd, char *szbuf, int nlen)
{
    STRU_RECOM_RQ rq=*(STRU_RECOM_RQ*)szbuf;


    char userbuf[1024]="";
    sprintf(userbuf,"Plike_user_id=%d",rq.user_id);
    list<string>filed;
    list<string>vals;

    filed.emplace_back("food_play");
    filed.emplace_back("food_like");
    filed.emplace_back("life_play");
    filed.emplace_back("life_like");
    filed.emplace_back("cartoon_play");
    filed.emplace_back("cartoon_like");
    filed.emplace_back("game_play");
    filed.emplace_back("game_like");
    filed.emplace_back("music_play");
    filed.emplace_back("music_like");
    //更新数据库在删除缓存
    if(redis->isExist(userbuf)){
        redis->getHashVals(userbuf,filed,vals);
        int psum=0;
        int lsum=0;
        bool f=true;
        for(auto i:vals){
            if(f){
                psum+=stoi(i);
                f=false;
            }else{
                lsum+=stoi(i);
                f=true;
            }
        }
        //cout<<psum<<' '<<lsum<<endl;
        char keybuf[1024]="";
        sprintf(keybuf,"zuser_like_id_:%d",rq.user_id);
        list<string>member;
        member.emplace_back("food_score");
        member.emplace_back("life_score");
        member.emplace_back("cartoon_score");
        member.emplace_back("game_score");
        member.emplace_back("music_score");
        for(auto i:member){
            int play=stoi(vals.front());
            vals.pop_front();
            int plike=stoi(vals.front());
            vals.pop_front();

            //播放量0.3 点赞0.7
            int score=(double)((double)play/psum)*30+(double)((double)plike/lsum)*70;

            redis->appondOneToZSet(keybuf,i,score);
        }

    }else{
        return;
    }
    //zset中取出用户对应的值，并进行增加
    char keybuf[1024]="";
    sprintf(keybuf,"zuser_like_id_:%d",rq.user_id);
    list<string>u1;
    redis->getZSetVals(keybuf,u1);

    char keybuf2[1024]="";
    sprintf(keybuf2,"zuser_like_id_:*");
    list<string>user_like;
    list<int>user_smiliar;
    redis->grepKeys(keybuf2,user_like);


    for(auto i:user_like){

        if(i!=keybuf){
            list<string>u2;
            cout<<i<<endl;
            redis->getZSetVals(i,u2);

            double smiliar=CountSmiliar(u1,u2);
            cout<<smiliar<<endl;
            cout<<"-----------"<<endl;
            if(smiliar>0.9){
                cout<<"similar:"<<i<<endl;
                size_t pos = i.find(':');
                if (pos !=string::npos) {
                    string numStr = i.substr(pos + 1); // 获取':'后的所有字符
                    int num =stoi(numStr); // 将子串转换为整数
                    cout<<"similar:"<<num<<endl;
                    user_smiliar.emplace_back(num);

                }

            }
        }

    }
    //
    //select ->redis ->video_type ->return client
    sprintf(keybuf,"user_type_%d",rq.user_id);
    u1.clear();
    list<string>fed;
    fed.emplace_back("food");
    fed.emplace_back("life");
    fed.emplace_back("cartoon");
    fed.emplace_back("game");
    fed.emplace_back("music");
    vector<int>vis(5,0);
    list<string>H_u1;
    //获取一边本用户喜好
    redis->getHashVals(keybuf,fed,H_u1);
    while(!user_smiliar.empty())
    {


        //取出视频推荐类型
        char keybuf2[1024]="";
        list<string>H_u2;//u2喜欢类型

        list<string>recomm;
        int i=1;

        sprintf(keybuf2,"user_type_%d",user_smiliar.front());
        user_smiliar.pop_front();
        if(!redis->isExist(keybuf2)) continue;
        redis->getHashVals(keybuf2,fed,H_u2);
        for(auto op:H_u1){
            if(vis[stoi(op)]==0&&H_u2.front()!=op&&op=="0"){
                cout<<"type"<<i<<endl;
                vis[stoi(op)]=1;
                char keybuf3[1024]="";
                sprintf(keybuf3,"file_type_%d",i);
                cout<<"life:"<<keybuf3<<endl;
                list<string>temp;
                redis->getList(keybuf3,temp);
                int o=3;
                while(o--&&!temp.empty()){
                    recomm.emplace_back(temp.front());
                    temp.pop_front();
                }
            }
            H_u2.pop_front();
            i++;
        }
        //        while(!H_u2.empty()&&!H_u1.empty()){
        //            if(vis[i]==1) continue;
        //            if(H_u1.front()!=H_u2.front()&&H_u2.front()[0]=='1'){

        //                vis[i]=1;//已经推荐过，标记

        //                char keybuf3[1024]="";
        //                sprintf(keybuf3,"file_type_%d",i);
        //                cout<<"life:"<<keybuf3<<endl;
        //                list<string>temp;
        //                redis->getList(keybuf3,temp);
        //                int o=3;
        ////                while(o--&&!temp.empty()){
        ////                    recomm.emplace_back(temp.front());
        ////                    temp.pop_front();
        ////                }

        //            }

        //            H_u1.pop_front();
        //           // H_u2.pop_front();
        //            i++;
        //        }

        //cout<<"count success"<<endl;
        //推荐视频发给客户端
        list<string>a;
        a.emplace_back("user_id");
        a.emplace_back("videoName");
        a.emplace_back("videoPath");
        a.emplace_back("rtmp");
        a.emplace_back("food");
        a.emplace_back("life");
        a.emplace_back("cartoon");
        a.emplace_back("game");
        a.emplace_back("music");
        while(!recomm.empty()){

            STRU_RTMP_RQ rt_Rq;
            list<string>b;
            char hobby[5]="";
            int file_id=stoi(recomm.front());
            sprintf(keybuf,"fileInfo_id=%d",file_id);
            redis->getHashVals(keybuf,a,b);
            rt_Rq.fileId=file_id;
            rt_Rq.user_id=atoi(b.front().c_str());

            b.pop_front();
            strcpy(rt_Rq.fileName,b.front().c_str());
            b.pop_front();
            b.pop_front();
            strcpy(rt_Rq.filepath,b.front().c_str());

            b.pop_front();
            for(int i=0;i<5;i++){
                rt_Rq.m_szHobby[i]=b.front()[0];
                b.pop_front();
            }

            STRU_PLIKE_RS plike_rs;
            //返回喜欢的推荐类型视频
            list<string>sql_like;
            list<string>key;
            key.emplace_back("video_like");
            key.emplace_back("video_play");
            sprintf(keybuf,"Plike_file_id=%d",rt_Rq.fileId);
            if(redis->isExist(keybuf)){
                redis->getHashVals(keybuf,key,sql_like);

            }else{
                char buf3[1024]="";
                sprintf(buf3,"select video_like,video_play from video_plike where video_id='%d';",rt_Rq.fileId);
                if(!m_sql->SelectMysql(buf3,2,sql_like)){
                    cout<<"sql register wrong\n"<<endl;
                    return;
                }

                redis->setHashVals(keybuf,key,sql_like);
            }

            plike_rs.file_id=rt_Rq.fileId;
            plike_rs.like=stoi(sql_like.front());
            plike_rs.play=stoi(sql_like.back());//s->int

             m_pKernel->SendData(clientfd,(char*)&plike_rs,sizeof(plike_rs));
            //先发评论，再发视频
            m_pKernel->SendData(clientfd,(char*)&rt_Rq,sizeof(rt_Rq));
            recomm.pop_front();
        }



    }

}

double CLogic::CountSmiliar(list<string> vals, list<string>val2s)
{
    int n=vals.size();
    vector<double>a;
    vector<double>b;
    map<string,int>v1;
    map<string,int>v2;
    while(!vals.empty()){
        string t1=vals.front();
        string t2=val2s.front();
        vals.pop_front();
        val2s.pop_front();
        v1[t1]=stod(vals.front());
        v2[t2]=stod(val2s.front());
        vals.pop_front();
        val2s.pop_front();
    }
    //去重并计算相似度
    for(auto ite:v1){
        if(ite.second==0){
            v1.erase(ite.first);
            v2.erase(ite.first);
        }
    }
    for(auto ite:v2){
        if(ite.second==0){
            v2.erase(ite.first);
            v1.erase(ite.first);
        }
    }
    //从redis中按顺序排列
    for(auto i:v1){

        a.push_back((double)i.second);
        b.push_back((double)v2[i.first]);
    }

    //余弦相似度计算
    double a1=0,b1=0;
    for(int i=0;i<a.size();i++){
        // cout<<a[i]<<' '<<b[i]<<endl;
        a1+=pow(a[i],2);
        b1+=pow(b[i],2);
    }


    a1=sqrt(a1);
    b1=sqrt(b1);

    for(int i=0;i<a.size();i++){
        a[i]/=a1;
        b[i]/=b1;
    }
    double x=0;
    a1=0,b1=0;
    for(int i=0;i<a.size();i++){
        x+=a[i]*b[i];
        a1+=pow(a[i],2);
        b1+=pow(b[i],2);
        //cout<<pow(a[i],2)<<' '<<pow(b[i],2)<<endl;

    }

    a1=sqrt(a1);
    b1=sqrt(b1);

    //cout<<x/(a1*b1)<<endl;
    return x/(a1*b1);
}

void CLogic::sendInfo(int id)
{
    _friend_message user_info;
    user_info.id=id;
    getInfo(id,&user_info);
    //cout<<user_info.name<<endl;
    _friend_message friend_message;
    //查找好友并发送自己信息 将好友信息发给我

    char fri_buf[1024]="";
    sprintf(fri_buf,"frined_%d",id);
    list<string>my_fri;
    if(redis->isExist(fri_buf)) redis->removeKey(fri_buf);

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
        redis->hgetall(keybuf,sock_cl,fid);
        while(fid.size()!=0){
            //cout<<stoi(sock_cl.front())<<' '<<stoi(fid.front())<<endl;
            m_frend[stoi(fid.front())]=stoi(sock_cl.front());
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
    char keybuf2[1024]="";
    sprintf(keybuf2,"addfriend_rq:%d",id);
    list<string>filed;
    list<string>vals;
    if(redis->isExist(keybuf2)){
        redis->hgetall(keybuf2,filed,vals);
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
                filed.emplace_back(sql.front());
                sql.pop_front();
                vals.emplace_back(sql.front());
                sql.pop_front();

            }
        }
        redis->setHashVals(keybuf2,filed,vals);
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
