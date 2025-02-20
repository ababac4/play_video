#include "block_epoll_net.h"
string  m_privateKey="MIIEuwIBADANBgkqhkiG9w0BAQEFAASCBKUwggShAg"
"EAAoIBAQDLgSpMwN1BX3NfDLd1GG2uQ53tcB4UoHUxa16ofrUPq6UZwDADnYB"
"ZURu8iZzB14brGT/ZJPdTBgihGB7ya4tO2IntthrgkMIv+UfAbLTP1oSMC7n3"
"khZAkKZ88d0AKrDqgRdW9PrtwY+KfEgJnVduQHayEOzVhhZoeeSEAd8H9cUI/"
"ZHNHEhKoWdm6ryMad20kLyWBteVw5dSNcvtHYBFG36xB+qyzXLUMtpBZmWW6i"
"aL0qO20d1y6rFYymHTk9U6eBul2wRUQnrBUUNAk+yEEmhL7iMcGF8Z7FroiGL"
"5hzc5iXpiuzS6tmhK6fCwZmXOPS/ZufUgJGVTWTtQuiirAgERAoIBAB/sGra0"
"12mgipFraBJeL1KNHcrkaRxVZ7dwNwFVIWvesHyCigqbN0U55juxMa/5prt3aW"
"NRF7y1pwAr8MandTmLYO4ShrnQbsZFOG5/e7w1unBSJzXkuDJI4uZsNr7FcRW"
"55YshaJ3EAnATfsBA1n+5zFgqz9EuIaH1ALVVoHm31wTL8iTxqb3Uo8znZt0x"
"ydeCioElWGaE7XCYSmfuArYTynXTW72oF/gtNOv86UPPQYFDjCAGQDSJOAQlW"
"N1NqiMY/P7hoCZFY26GpIIO+13O9PLhPYBkSZg/kV+X1Zn1FNiAV2dHPvuTSM"
"zjJOZ01e0fjy/DOP1OwufzL4XetnECgYEA0OLzEYjzPLNYPBZhQsyGfzF+RgI"
"ScrLNWUCQm40fRCUFGnJlTo9j8LzULrQKvreGOmQwjmzgX73aZYrwE+Omnbmxt"
"4quV8j7lwtLmXvhBfpPy/PpoO0kfrZUaSQVmEXPLaiheBn50bCyTJ8/G26Mgb"
"piKxuG5ZPZuiSWVYuMz1MCgYEA+Wd2WJikcX0dlxZGSf3F98UyQ5ymUVVm1GP"
"aVglw6tdYOY9/M0pZ6Uk+eizvV88aqo+Td/3JpGYlhrNsN20eGuEHF0JOT5dM"
"idVrUQeTZBO7Qsuomhx0izkCswMK2P49pKy11RZbMYY5K5GCygSxEEwx0+22h"
"D10kKgUls/BjkkCgYEAuE/HadMw+VLzgE/7dyzvJO9vavLE+8rxbN6dtm118N"
"Ve2xmkrrrBmC4koa3rXPxJQpSjUH4vY4lmWZi1tzJHuFiNwBD0L1b8G9zKPCI"
"CyQoKLG3OJJUCFXOz5E0D/tQvRmediBbrfMkVyyMZkKzWVFkpcVSGFdzPK8X"
"uDz7lp98CgYBmsiGsAp4QnO4RCSwAWW+iQiPBfLz0UFeEoZYjbUyc70JyDek"
"VHp1+LTfX9GKNkYNzaEvH/xbLOR6Cwlm8eDmSmOTNV4moTVvASNHWEi2hrcWT"
"+YGo3opXcdPvW5sODlWeKP+T+iWM3OpdO+qPa1f3pudXQ8Of3RHhNiaYc6oNa"
"QKBgAVGemjrvgNrjBOr7CziGdkogmFlM9J9OFv/Wh5vH668LUfebgiRKPNaJT"
"YCs6Qw47UJ5R50TA6n2NPNTTGV3T1MtAwM47rJDgGO37GnyWjqdT6YjJCbYR"
"Ar/K5pkU4wSzA5ijzIWAwua2/lw0aJ74TY7luPJPGUMbFIhJ4buwdR";

Rsa_PrivateKey privateKey=CMyRsa::RSA_DecodePrivateKey( m_privateKey);
CRedis *m_redis=new CRedis;
bool Block_Epoll_Net::InitNet(int port, void (*recv_callback)(int, char *, int))
{
    m_recv_callback = recv_callback;
    InitThreadPool();

    int flags = 1;
    int ret = 0;
    m_listenEv = new myevent_s(this);

    char keybuf[1024]="m_epoll_fd:1";
    char keybuf2[1024]="friend_epoll_1";
    //sprintf(keybuf,"",);
    if(m_redis->isExist(keybuf))  m_redis->removeKey(keybuf);
    if(m_redis->isExist(keybuf2)) m_redis->removeKey(keybuf2);
    //creat a tcp socket
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( m_listenfd  == -1 ){
        perror("create socket error");
        return false;
    }

    //set REUSERADDR
    ret = setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&flags, sizeof(flags));
    if ( ret == -1 ){
        perror("setsockopt error");
        return false;
    }

    //监听套接字m_listenfd 采用 LT 非阻塞模式
    //set NONBLOCK
    setNonBlockFd( m_listenfd );

    struct sockaddr_in local_addr;
    bzero( &local_addr , sizeof(sockaddr_in) );
    //set address
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = INADDR_ANY;

    //bind addr
    ret = bind(m_listenfd, (struct sockaddr *)&local_addr, sizeof(struct sockaddr_in));
    if( ret == -1 ) {
        perror("bind error");
        close(m_listenfd);
        return false;
    }

    if (listen(m_listenfd, 128) == -1 ){
        perror("listen error");
        close(m_listenfd);
        return false;
    }

    //create epoll
    m_epoll_fd = epoll_create( MAX_EVENTS );

    m_listenEv->eventset(m_listenfd ,m_epoll_fd );
    //将监听套接字 添加到epoll中 , 模式LT 非阻塞
    m_listenEv->eventadd( EPOLLIN);


    return true;
}

bool Block_Epoll_Net::InitThreadPool()
{

    m_threadpool = new thread_pool;

    //创建拥有10个线程的线程池 最大线程数200 环形队列最大值50000
    if( (m_threadpool->Pool_create(200,10,50000)) == false )
    {
        perror("Create Thread_Pool Failed:");
        exit(-1);
    }

    return true;
}

void Block_Epoll_Net::EventLoop()
{
    printf("EventLoop:server running\n");
    int  i = 0;
    while (1) {

        /* 等待事件发生 */
        int nfd = epoll_wait( m_epoll_fd, events, MAX_EVENTS+1, 1000);
        if (nfd < 0) {
            printf("epoll_wait error, exit\n");
//            break;
            continue;
        }
        for (i = 0; i < nfd; i++) {
            struct myevent_s *ev = (struct myevent_s *)events[i].data.ptr;
            int fd = ev->fd;
            if ( (events[i].events & EPOLLIN) ) {
                if( fd == m_listenfd )
                    accept_event();
                else
                    recv_event( ev );
            }
            if ((events[i].events & EPOLLOUT) ) {
                epollout_event( ev );
            }
        }
    }
}

void Block_Epoll_Net::accept_event()
{
    struct sockaddr_in caddr;
    socklen_t len = sizeof(caddr);
    int clientfd ;
    if ((clientfd = accept(m_listenfd, (struct sockaddr *)&caddr, &len)) == -1) {
        if (errno != EAGAIN && errno != EINTR) {
            /* 暂时不做出错处理 */
        }
        printf("%s: accept, %s\n", __func__, strerror(errno));
        return;
    }

    //设置接收缓冲区大小
    setRecvBufSize( clientfd );
    //设置发送缓冲区大小
    setRecvBufSize( clientfd );
    //设置 无延迟
    setNoDelay( clientfd );
    char keybuf[1024]="m_epoll_fd:1";
    //sprintf(keybuf,,m_epoll_fd);

    m_redis->appendOneToList(keybuf,to_string(clientfd));
    sprintf(keybuf,"clientfd:%d",clientfd);
    m_redis->setex(keybuf,"1",_CHECK_ALIVE_TIME);

    myevent_s * clientEv = new myevent_s(this);
    clientEv->eventset( clientfd , m_epoll_fd );
    // 使用EPOLLONESHOT epoll监听不会重复检测 避免多线程并发 使得同一个套接字接收是排队的
    clientEv->eventadd(  EPOLLIN/*|EPOLLET*/|EPOLLONESHOT );

    //m_mapSockfdToEvent[clientfd] = clientEv;
    m_mapSockfdToEvent.insert(clientfd , clientEv);

    printf("new connect [%s:%d][time:%ld] \n",
           inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port), time(NULL) );
    return;
}




void Block_Epoll_Net::recv_event( myevent_s *ev)
{
    //将接收函数任务使用线程池处理
     m_threadpool->Producer_add(  recv_task , (void*) ev );
}

void* Block_Epoll_Net::recv_task(void* arg)
{
    myevent_s * ev = (myevent_s*)arg;

    Block_Epoll_Net * pthis = ev->pNet;

    //接收和处理分离
    int nRelReadNum = 0;
    int nPackSize = 0;
    char *pSzBuf = NULL;
    do
    {
        nRelReadNum = read(ev->fd,&nPackSize,sizeof(nPackSize) );
        if(nRelReadNum <= 0)
            break;

        pSzBuf = new char[nPackSize];
        int nOffSet = 0;
        nRelReadNum = 0;
        //接收包的数据
        while(nPackSize)
        {
            nRelReadNum = recv(ev->fd,pSzBuf+nOffSet,nPackSize,0);
            if(nRelReadNum <= 0)
                break;

            nOffSet += nRelReadNum;
            nPackSize -= nRelReadNum;
        }
        char *temp=pSzBuf;
        char buf2[1024]="";
        sprintf(buf2,"fd_key:%d",ev->fd);
        PackType type = *(PackType*)pSzBuf;
        if(type==10006){
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,pSzBuf , nOffSet);
            Buffer_Deal( (void*) buffer );
        }else{
        //接收和处理分离 跑线程池里其他线程处理 , 避免处理影响接收


        string content = CMyAes::AES_CBC_Decryption( "0123456789ABCDEF" , "0123456789ABCDEF" , temp );
        CJson m_json(content.c_str());

        //cout << "json:" <<json.json_to_string() << endl;
        int m_type=m_json.json_get_int("type");

       if(m_type==100){
           char buf[1024]="";
           sprintf(buf,m_json.json_get_string("content"));

          string decryptedtext = CMyRsa::RSA_OAEP_Decrypt_Private(buf, privateKey);
          cout<<decryptedtext<<endl;
          CJson op(decryptedtext.c_str());
          if(m_redis->isExist(buf2)) m_redis->removeKey(buf2);
          m_redis->setString(buf2,op.json_get_string("KEY"));
       }else{
           char buf[1024]="";
           sprintf(buf,m_json.json_get_string("content"));
           //cout<<buf<<endl;
           string m_Aes_key;
           m_redis->getString(buf2,m_Aes_key);
           cout<<"my_key:"<<m_Aes_key<<endl;

           string m_content = CMyAes::AES_CBC_Decryption( m_Aes_key , "0123456789ABCDEF" , buf );
           //cout<<m_content<<endl;
           CJson json( m_content.c_str() );
           cout << "json:" <<json.json_to_string() << endl;
           int m_type=json.json_get_int("type");
        if(m_type==10000){
            STRU_REGISTER_RQ rq;
            rq.type=m_type;

            sprintf(rq.name,json.json_get_string("name"));
            sprintf(rq.tel,json.json_get_string("tel"));
            sprintf(rq.password,json.json_get_string("password"));
            sprintf(rq.sms,json.json_get_string("sms"));
            char *m_buf=(char*)&rq;
           // cout<<rq.name<<rq.password<<rq.tel<<endl;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );
        }
        if(m_type==10002){
            STRU_LOGIN_RQ rq;
            rq.type=m_type;
            sprintf(rq.tel,json.json_get_string("tel"));
            sprintf(rq.password,json.json_get_string("password"));
            cout<<rq.tel<<' '<<rq.password<<endl;


            //cout<<strlen(szbuf)<<' '<<sizeof(rq)<<' '<<sizeof(szbuf)<<endl;
            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );
        }
        else if(m_type==10004){
            STRU_UPLOAD_FILE_RQ rq;
            rq.type=m_type;
            sprintf(rq.dir,json.json_get_string("dir"));
            sprintf(rq.fileName,json.json_get_string("fileName"));
            sprintf(rq.fileType,json.json_get_string("fileType"));
            sprintf(rq.md5,json.json_get_string("md5"));
            sprintf(rq.time,json.json_get_string("time"));
            rq.size=json.json_get_int("size");
            rq.timestamp=json.json_get_int("timestamp");
            rq.userid=json.json_get_int("userid");

            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );

        }/*else if(m_type==10006){
            STRU_FILE_CONTENT_RQ rq;
            rq.type=m_type;
            sprintf(rq.content,json.json_get_string("content"));

            rq.fileid=json.json_get_int("fileid");
            rq.len=json.json_get_int("len");
            rq.timestamp=json.json_get_int("timestamp");
            rq.userid=json.json_get_int("userid");
            char *m_buf=(char*)&rq;

            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );
        }*/
        else if(m_type==10008){
            STRU_GET_INFO_RQ rq;
            rq.type=m_type;
            sprintf(rq.dir,json.json_get_string("dir"));
            rq.user_id=json.json_get_int("user_id");
            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );

        }else if(m_type==10010){
            STRU_DOWNLOAD_FILE_RQ rq;

            rq.type=m_type;
            sprintf(rq.dir,json.json_get_string("dir"));
            rq.fileid=json.json_get_int("fileid");
            rq.userid=json.json_get_int("userid");
            rq.timestamp=json.json_get_int("timestamp");

            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );
            }
        else if(m_type==10011){
             STRU_DOWNLOAD_FOLDER_RQ rq;
             rq.type=m_type;
             sprintf(rq.dir,json.json_get_string("dir"));
             rq.fileid=json.json_get_int("fileid");
             rq.timestamp=json.json_get_int("timestamp");
             rq.userid=json.json_get_int("userid");

             char *m_buf=(char*)&rq;
             DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
             Buffer_Deal( (void*) buffer );
            }

        else if(m_type==10014){
            STRU_FILE_HEADER_RS rq;
            rq.type=m_type;
            rq.result=json.json_get_int("result");
            rq.userid=json.json_get_int("userid");
            rq.fileid=json.json_get_int("fileid");
            rq.timestamp=json.json_get_int("timestamp");

            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );

        }else if(m_type==10007){
        STRU_FILE_CONTENT_RS rq;
        rq.type=m_type;
        rq.result=json.json_get_int("result");
        rq.userid=json.json_get_int("userid");
        rq.fileid=json.json_get_int("fileid");
        rq.timestamp=json.json_get_int("timestamp");
        rq.len=json.json_get_int("len");
        char *m_buf=(char*)&rq;
        DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
        Buffer_Deal( (void*) buffer );
        }
        else if(m_type==10015){
            STRU_ADD_FOLDER_RQ rq;

            rq.type=m_type;
            sprintf(rq.dir,json.json_get_string("dir"));
            sprintf(rq.fileName,json.json_get_string("fileName"));
            sprintf(rq.time,json.json_get_string("time"));
            rq.timestamp=json.json_get_int("timestamp");
            rq.userid=json.json_get_int("userid");

            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );

   }else if(m_type==10018){
   int size=json.json_get_int("itemCount");
   int packsize=sizeof(STRU_SHARE_FILE_RQ)+sizeof(int)*size;
   STRU_SHARE_FILE_RQ *rq=(STRU_SHARE_FILE_RQ *)malloc(packsize) ;
   rq->init();
   rq->type=m_type;

    sprintf(rq->dir,json.json_get_string("dir"));
    rq->itemCount=json.json_get_int("itemCount");
    sprintf(rq->shareTime,json.json_get_string("shareTime"));
   rq->userid=json.json_get_int("userid");
   cout<<"Count:"<<rq->itemCount<<endl;
   for(int i=0;i<rq->itemCount;i++){
       char buf[1024]="";
       sprintf(buf,"fileidArray:%d",i);
       rq->fileidArray[i]=json.json_get_int(buf);
       cout<<"shareFile"<<rq->fileidArray[i]<<endl;
   }
   char *m_buf=(char*)rq;
   DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , packsize);
   Buffer_Deal( (void*) buffer );
   }

        else if(m_type==10020){
            STRU_MY_SHARE_RQ rq;
            rq.type=m_type;
            rq.userid=json.json_get_int("userid");

            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );

        }
        else if(m_type==10022){
            STRU_GET_SHARE_RQ rq;

            rq.type=m_type;
            sprintf(rq.dir,json.json_get_string("dir"));
            rq.shareLink=json.json_get_int("shareLink");
            sprintf(rq.time,json.json_get_string("time"));
            rq.userid=json.json_get_int("userid");
            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );

            }

        else if(m_type==10025){
            int size=json.json_get_int("fileCount");
            int packsize=sizeof(STRU_DELETE_FILE_RQ)+sizeof(int)*size;
            STRU_DELETE_FILE_RQ *rq=(STRU_DELETE_FILE_RQ *)malloc(packsize);
            rq->init();
            rq->type=m_type;
            sprintf(rq->dir,json.json_get_string("dir"));
            rq->fileCount=json.json_get_int("fileCount");
            rq->userid=json.json_get_int("userid");
            for(int i=0;i<rq->fileCount;i++){
                char buf[1024]="";
                sprintf(buf,"fileidArray:%d",i);
                rq->fileidArray[i]=json.json_get_int(buf);
            }
            char *m_buf=(char*)rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , packsize);
            Buffer_Deal( (void*) buffer );

         }else if(m_type==10027){
            STRU_CONTINUE_DOWNLOAD_RQ rq;

            rq.type=m_type;
            rq.fileid=json.json_get_int("fileid");
            rq.pos=json.json_get_int("pos");
            rq.timestamp=json.json_get_int("timestamp");

            sprintf(rq.dir,json.json_get_string("dir"));
            rq.userid=json.json_get_int("userid");

            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );

        }else if(m_type==10028){
             STRU_CONTINUE_UPLOAD_RQ rq;

             rq.type=m_type;
             rq.fileid=json.json_get_int("fileid");
             rq.timestamp=json.json_get_int("timestamp");
             sprintf(rq.dir,json.json_get_string("dir"));
             rq.userid=json.json_get_int("userid");

            char *m_buf=(char*)&rq;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );

        }
        else if(m_type==10033){
        STRU_SMS_RQ rq;
        rq.type=m_type;
        sprintf(rq.tel,json.json_get_string("tel"));

        char *m_buf=(char*)&rq;
        //cout<<rq.tel<<' '<<rq.type<<endl;
        DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
        Buffer_Deal( (void*) buffer );
        }
        else if(m_type==10031){
            _addfriend_RQ rq;
           rq.type=m_type;
           sprintf(rq.friend_name,json.json_get_string("friend_name"));
           rq.my_id=json.json_get_int("my_id");
           sprintf(rq.my_name,json.json_get_string("my_name"));
           char *m_buf=(char*)&rq;
           //cout<<rq.tel<<' '<<rq.type<<endl;
           DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
           Buffer_Deal( (void*) buffer );
        }else if(m_type==10032){
            _addfriend_RS rq;
            rq.type=m_type;
            rq.friendid=json.json_get_int("friendid");
            rq.my_id=json.json_get_int("my_id");
            rq.status=json.json_get_int("status");
            char *m_buf=(char*)&rq;
            cout<<rq.friendid<<' '<<rq.status<<endl;
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );
        }
        else if(m_type==10035){

            STRU_CHAR_RQ rq;
            rq.type=m_type;
            char *m_buf=(char*)&rq;
            sprintf(rq.content,json.json_get_string("content"));
            rq.friendid=json.json_get_int("friendid");
            rq.my_id=json.json_get_int("my_id");
            DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd ,m_buf , sizeof(m_buf));
            Buffer_Deal( (void*) buffer );
        }
}
        //DataBuffer * buffer = new DataBuffer(ev->pNet , ev->fd , pSzBuf , nOffSet );
        //Buffer_Deal( (void*) buffer );
        //pthis->m_threadpool->Producer_add(  Buffer_Deal , (void*) buffer );
}
        //要重新注册事件

        char keybuf[1024]="";

        sprintf(keybuf,"clientfd:%d",ev->fd);
        m_redis->removeKey(keybuf);
        sprintf(keybuf,"m_epoll_fd:1");
        m_redis->Remvals(keybuf,to_string(ev->fd));
        ev->eventadd(  ev->events );

        return 0;

    }while(0);


    ev->eventdel();
    close(ev->fd);
    //回收event结构
    //pthis->m_mapSockfdToEvent.erase( ev->fd );
    pthis->m_mapSockfdToEvent.erase( ev->fd );
    delete ev;
    return NULL;

}

void * Block_Epoll_Net::Buffer_Deal( void * arg )
{
    DataBuffer * buffer = (DataBuffer *)arg;
    if( !buffer ) return NULL;

    buffer->pNet->m_recv_callback(buffer->sockfd,buffer->buf,buffer->nlen);

    //printf("pszbuf = %p \n",buffer->buf);
    if(buffer->buf != NULL)
    {
//    delete buffer->buf;
//    buffer->buf = NULL;
    }
    delete buffer;
    return 0;
}

void Block_Epoll_Net::epollout_event( myevent_s *ev )
{

}



int Block_Epoll_Net::SendData(int fd, char *szbuf, int nlen)
{

    int nPackSize = nlen + 4;
    vector<char> vecbuf( nPackSize , 0);
    //vecbuf.resize( nPackSize );

    char* buf = &* vecbuf.begin();
    char* tmp = buf;
    *(int*)tmp = nlen;//按四个字节int写入
    tmp += sizeof(int );
    memcpy( tmp , szbuf , nlen );

    int res = send( fd,(const char *)buf, nPackSize ,0);

    return res;
}

void Block_Epoll_Net::setNonBlockFd(int fd)
{
    int flags = 0;
    flags = fcntl(fd, F_GETFL, 0);
    int ret = fcntl(fd, F_SETFL, flags|O_NONBLOCK);
    if( ret == -1)
        perror("setNonBlockFd fail:");
}

void Block_Epoll_Net::setRecvBufSize( int fd)
{
    //接收缓冲区
    int nRecvBuf = 256*1024;//设置为 256 K
    setsockopt(fd,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));
}

void Block_Epoll_Net::setSendBufSize( int fd)
{
    //发送缓冲区
    int nSendBuf=128*1024;//设置为 128 K
    setsockopt(fd,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
}

#include<netinet/tcp.h>
void Block_Epoll_Net::setNoDelay( int fd)
{
    //nodelay
    int value = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY ,(char *)&value, sizeof(int));
}
