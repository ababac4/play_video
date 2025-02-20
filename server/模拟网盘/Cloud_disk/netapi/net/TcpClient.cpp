#include "TcpClient.h"


#include"INetMediator.h"

#include"packdef.h"

string m_prikey="MIIBIDANBgkqhkiG9w0BAQEFAAOCAQ0AMIIBCAKCAQEAy4EqTMDdQV9zXwy3dRhtrkOd7XAeFKB1MWteqH61D6ulGcAw"
"A52AWVEbvImcwdeG6xk/2ST3UwYIoRge8muLTtiJ7bYa4JDCL/lHwGy0z9aEjAu595IWQJCmfPHd"
"ACqw6oEXVvT67cGPinxICZ1XbkB2shDs1YYWaHnkhAHfB/XFCP2RzRxISqFnZuq8jGndtJC8lgbXlcOXUjXL7R2ARRt+sQfqss1y1DLaQWZl"
"luomi9KjttHdcuqxWMph05PVOngbpdsEVEJ6wVFDQJPshBJoS+4jHBhfGexa6Ihi+Yc3OYl6Yrs0urZoSunwsGZlzj0v2bn1ICRlU1k7ULooqwIBEQ==";

TcpClient::TcpClient( INetMediator * pMediator ):m_sock( INVALID_SOCKET ),m_isStop(false)
{
	m_pMediator = pMediator;
    m_isConnected = false;
	m_hThreadHandle = NULL;

}

TcpClient::~TcpClient()  //使用时, 父类指针指向子类, 使用虚析构
{
    TcpClient::UnInitNet();
}
//初始化网络	//加载库 创建套接字 绑定
bool TcpClient::InitNet(const char *szBufIP, unsigned short port)
{
    if( !m_isLoadlib )
    {

        WORD wVersionRequested;
        WSADATA wsaData;
        int err;

    /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
        wVersionRequested = MAKEWORD(2, 2);

        err = WSAStartup(wVersionRequested, &wsaData);
        if (err != 0) {
            return false;
        }

        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            WSACleanup();
            return false;
        }
        m_isLoadlib = true;
    }

    m_isConnected = false;

	//2.雇人-- 创建套接字 进程与外界网络通信需要的接口 决定了与外界通讯的方式(tcp udp)
	m_sock = socket( AF_INET , SOCK_STREAM , IPPROTO_TCP ); // ipv4 udp
	if ( m_sock == INVALID_SOCKET) {
		WSACleanup();
        return false;
	}

	//3. 连接服务器
	sockaddr_in addr;
	addr.sin_family = AF_INET ;
    addr.sin_addr.S_un.S_addr = inet_addr( szBufIP );  /*inet_addr("192.168.31.115")*/ ;  //绑定任意网卡
    addr.sin_port = htons( port );  //htons 转换为网络字节序 大端存储  43232

	
	if( connect( m_sock ,(const sockaddr* ) &addr , sizeof(addr) ) == SOCKET_ERROR )
	{
		UnInitNet();
        return false;
	}

    //设置客户端发送缓冲区
    //     int nSendBuf=64*1024;//设置为64K
    //     setsockopt(m_sock,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));
    //设置客户端接收缓冲区
    //     int nRecvBuf=64*1024;//设置为64K
    //     setsockopt(m_sock,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));

//    DWORD nNetTimeout= 300;//1秒 - 1000

//    //发送时限 , 超时退出避免长时间阻塞
//    setsockopt(m_sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(DWORD));

    //禁用 TCP-NODELAY
    int value = 1;
    setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (char *)&value, sizeof(int));


    m_isConnected = true;
	// 收数据 -- 创建线程 CreateThread  WinAPI  strcpy  C/C++ RunTime 库函数 创建内存块
	m_hThreadHandle = (HANDLE)_beginthreadex(  NULL, 0 ,&RecvThread ,this , 0 , NULL );     //( CreateThread 创建内存块 )
	//_endthreadex(); -- 回收内存块      //( ExitThread 不回收内存块 ) --内存泄露

	return true;
}

unsigned int __stdcall TcpClient::RecvThread( void * lpvoid)
{
	TcpClient* pthis = (TcpClient*) lpvoid;
	pthis->RecvData();
	
	return 0;
}

//关闭网络
void TcpClient::UnInitNet()
{
	m_isStop = true ; // 尝试退出线程循环 
	if( m_hThreadHandle )
	{
		if( WaitForSingleObject(m_hThreadHandle , 100 ) == WAIT_TIMEOUT )
		{
			TerminateThread( m_hThreadHandle , -1 );
		}
		CloseHandle(m_hThreadHandle);
		m_hThreadHandle = NULL;
	}
	if( m_sock && m_sock != INVALID_SOCKET )
		closesocket(m_sock);

    if( m_isLoadlib )
    {
        WSACleanup();
        m_isLoadlib = false;
    }
} 
//发送 : 同时兼容tcp udp 
bool TcpClient::SendData(unsigned int lSendIP , char* szbuf , int nlen )
{
    if( !szbuf|| nlen <= 0 ) return false;

	//防止粘包  策略: 先发包大小 再发数据包
	// m_sock  <--> lSendIP
/*	send( m_sock , (char*)&nlen , sizeof(int) , 0  );

	if( send( m_sock , buf , nlen , 0  ) <= 0 )
		return false;
	
	return true;
*/

    lSendIP = m_sock;


    CJson m_sjon;
    CJson y_json;
    PackType type = *(PackType*)szbuf;
     m_sjon.json_add_value("type",type);
    cout<<type<<endl;
    y_json.json_add_value("type","null");
    if(type==_PRIVATE_MYKEY){
     y_json.json_add_value("type",_PRIVATE_MYKEY);
        MY_KEY key=*(MY_KEY*)szbuf;

        rekey=key.KEY;
        cout<<"MY_KEY"<<rekey<<endl;
        Rsa_PublicKey publickey =  CMyRsa::RSA_DecodePublicKey(m_prikey);
        m_sjon.json_add_value("KEY",key.KEY);
        cout<<m_sjon.json_to_string().data()<<endl;
         QByteArray jsonbt = m_sjon.json_to_string();
        string ciphertext = CMyRsa::RSA_OAEP_Encrypt_Public(jsonbt.data(),publickey );
        cout << "Ciphertext: " << ciphertext.c_str()<< endl;
        y_json.json_add_value("content",ciphertext.c_str());
    }else{

    if(type==10000){
    STRU_REGISTER_RQ rq=*(STRU_REGISTER_RQ*)szbuf;
    m_sjon.json_add_value("name",rq.name);
    m_sjon.json_add_value("password",rq.password);
    m_sjon.json_add_value("tel",rq.tel);
     m_sjon.json_add_value("sms",rq.sms);
    }
    else if(type==10002){
        STRU_LOGIN_RQ temp=*(STRU_LOGIN_RQ*)szbuf;
        m_sjon.json_add_value("tel",temp.tel);
        m_sjon.json_add_value("password",temp.password);
      }
    else if(type==10004){
  STRU_UPLOAD_FILE_RQ rq=*(STRU_UPLOAD_FILE_RQ*)szbuf;
   m_sjon.json_add_value("dir",rq.dir);
   m_sjon.json_add_value("fileName",rq.fileName);
   m_sjon.json_add_value("fileType",rq.fileType);
   m_sjon.json_add_value("md5",rq.md5);
   m_sjon.json_add_value("size",rq.size);
   m_sjon.json_add_value("time",rq.time);
   m_sjon.json_add_value("timestamp",rq.timestamp);
   m_sjon.json_add_value("userid",rq.userid);


    }else if(type==10006){
//STRU_FILE_CONTENT_RQ rq=*(STRU_FILE_CONTENT_RQ*)szbuf;

//m_sjon.json_add_value("content",rq.content);
//m_sjon.json_add_value("fileid",rq.fileid);
//m_sjon.json_add_value("len",rq.len);
//m_sjon.json_add_value("timestamp",rq.timestamp);
//m_sjon.json_add_value("userid",rq.userid);

lSendIP = m_sock;

int DataLen = nlen + 4;
std::vector<char> vecbuf;
vecbuf.resize( DataLen );

//   char* buf = new char[ DataLen ];
char* buf = &*vecbuf.begin();
char* tmp = buf;
*(int*) tmp = nlen;//绑定长度
tmp+= sizeof(int);

memcpy( tmp , szbuf , nlen);

int res = send( lSendIP ,buf,DataLen , 0);
//    delete[] buf;
return res;

    }
    else if(type==10008){
          STRU_GET_INFO_RQ rq=*(STRU_GET_INFO_RQ*)szbuf;
          m_sjon.json_add_value("user_id",rq.user_id);
          m_sjon.json_add_value("dir",rq.dir);

    }else if(type==10010){
    STRU_DOWNLOAD_FILE_RQ rq=*(STRU_DOWNLOAD_FILE_RQ*)szbuf;
    m_sjon.json_add_value("dir",rq.dir);
    m_sjon.json_add_value("fileid",rq.fileid);
    m_sjon.json_add_value("timestamp",rq.timestamp);
    m_sjon.json_add_value("userid",rq.userid);

    }else if(type==10011){
  STRU_DOWNLOAD_FOLDER_RQ rq=*(STRU_DOWNLOAD_FOLDER_RQ*)szbuf;
 //m_sjon.json_add_value("",rq);
   m_sjon.json_add_value("dir",rq.dir);
   m_sjon.json_add_value("fileid",rq.fileid);
   m_sjon.json_add_value("timestamp",rq.timestamp);
   m_sjon.json_add_value("userid",rq.userid);
    }
    else if(type==10014){
    STRU_FILE_HEADER_RS rq=*(STRU_FILE_HEADER_RS*)szbuf;

    m_sjon.json_add_value("result",rq.result);
    m_sjon.json_add_value("userid",rq.userid);
    m_sjon.json_add_value("fileid",rq.fileid);
    m_sjon.json_add_value("timestamp",rq.timestamp);


    }else if(type==10007){
STRU_FILE_CONTENT_RS rq=*(STRU_FILE_CONTENT_RS*)szbuf;
m_sjon.json_add_value("result",rq.result);
m_sjon.json_add_value("fileid",rq.fileid);
m_sjon.json_add_value("timestamp",rq.timestamp);
m_sjon.json_add_value("userid",rq.userid);
m_sjon.json_add_value("len",rq.len);
    }
    else if(type==10015){
STRU_ADD_FOLDER_RQ rq=*(STRU_ADD_FOLDER_RQ*)szbuf;
m_sjon.json_add_value("dir",rq.dir);
m_sjon.json_add_value("fileName",rq.fileName);
m_sjon.json_add_value("time",rq.time);
m_sjon.json_add_value("timestamp",rq.timestamp);
m_sjon.json_add_value("userid",rq.userid);

}else if(type==10018){
STRU_SHARE_FILE_RQ *rq=(STRU_SHARE_FILE_RQ*)szbuf;
m_sjon.json_add_value("dir",rq->dir);
m_sjon.json_add_value("itemCount",rq->itemCount);
m_sjon.json_add_value("shareTime",rq->shareTime);
m_sjon.json_add_value("userid",rq->userid);

for(int i=0;i<rq->itemCount;i++){
   char buf[1024]="";

   sprintf(buf,"fileidArray:%d",i);
   cout<<buf<<' '<<rq->fileidArray[i]<<endl;
   m_sjon.json_add_value(buf,rq->fileidArray[i]);

}
cout<<m_sjon.json_to_string().data()<<endl;
}
    else if(type==10020){
STRU_MY_SHARE_RQ rq=*(STRU_MY_SHARE_RQ*)szbuf;
m_sjon.json_add_value("userid",rq.userid);

    }
    else if(type==10022){
STRU_GET_SHARE_RQ rq=*(STRU_GET_SHARE_RQ*)szbuf;
m_sjon.json_add_value("dir",rq.dir);
m_sjon.json_add_value("shareLink",rq.shareLink);
m_sjon.json_add_value("time",rq.time);
m_sjon.json_add_value("userid",rq.userid);
    }
    else if(type==10025){
STRU_DELETE_FILE_RQ *rq=(STRU_DELETE_FILE_RQ*)szbuf;
m_sjon.json_add_value("dir",rq->dir);
m_sjon.json_add_value("fileCount",rq->fileCount);
for(int i=0;i<rq->fileCount;i++){
    char buf[1024]="";
    sprintf(buf,"fileidArray:%d",i);
    m_sjon.json_add_value(buf,rq->fileidArray[i]);
}
m_sjon.json_add_value("userid",rq->userid);

   }else if(type==10027){
    STRU_CONTINUE_DOWNLOAD_RQ rq=*(STRU_CONTINUE_DOWNLOAD_RQ*)szbuf;
    m_sjon.json_add_value("dir",rq.dir);
    m_sjon.json_add_value("fileid",rq.fileid);
    m_sjon.json_add_value("pos",rq.pos);
    m_sjon.json_add_value("timestamp",rq.timestamp);
    m_sjon.json_add_value("userid",rq.userid);

   }else if(type==10028){
  STRU_CONTINUE_UPLOAD_RQ rq=*(STRU_CONTINUE_UPLOAD_RQ*)szbuf;
  m_sjon.json_add_value("dir",rq.dir);
  m_sjon.json_add_value("fileid",rq.fileid);
  m_sjon.json_add_value("userid",rq.userid);
  m_sjon.json_add_value("timestamp",rq.timestamp);

   }else if(type==10031){
        _addfriend_RQ rq=*(_addfriend_RQ*)szbuf;
        m_sjon.json_add_value("friend_name",rq.friend_name);
        m_sjon.json_add_value("my_id",rq.my_id);
        m_sjon.json_add_value("my_name",rq.my_name);
    }else if(type==10032){
        _addfriend_RS rs=*(_addfriend_RS*)szbuf;
         m_sjon.json_add_value("my_id",rs.my_id);
         m_sjon.json_add_value("friendid",rs.friendid);
         m_sjon.json_add_value("status",rs.status);

    }
   else if(type==10033){
        STRU_SMS_RQ rq=*(STRU_SMS_RQ*)szbuf;
         m_sjon.json_add_value("tel",rq.tel);
    }
    else if(type==10035){
        STRU_CHAR_RQ rq=*(STRU_CHAR_RQ*)szbuf;
         m_sjon.json_add_value("content",rq.content);
         m_sjon.json_add_value("friendid",rq.friendid);
         m_sjon.json_add_value("my_id",rq.my_id);
    }

 QByteArray m_jsonbt = m_sjon.json_to_string();
 string m_decry =  CMyAes::AES_CBC_Encryption( rekey , "0123456789ABCDEF" , m_jsonbt.data()); //加密
 //string m_decry =  CMyAes::AES_CBC_Encryption( "0123456789ABCDEF" , "0123456789ABCDEF" , m_jsonbt.data()); //加密
  y_json.json_add_value("content",m_decry.c_str());
  //cout<<y_json.json_to_string().data()<<endl;
 //cout<<decry<<endl;
}
    QByteArray jsonbt = y_json.json_to_string();
    string decry =  CMyAes::AES_CBC_Encryption( "0123456789ABCDEF" , "0123456789ABCDEF" , jsonbt.data() ); //加密
    //string decry=jsonbt.data();
    nlen=decry.size()+1;
  //  cout<<decry.size()<<endl;

    int DataLen = nlen + 4;
    std::vector<char> vecbuf;
    vecbuf.resize( DataLen );

 //   char* buf = new char[ DataLen ];
    char* buf = &*vecbuf.begin();
    char* tmp = buf;
    *(int*) tmp = nlen;//绑定长度
    tmp+= sizeof(int);

    memcpy( tmp , decry.data() , nlen);

   // int res = send( lSendIP ,buf,DataLen , 0);
//    delete[] buf;
   // return res;


//    std::vector<char> vecbuf;
//    vecbuf.resize( DataLen );

// //   char* buf = new char[ DataLen ];
//    char* buf = &*vecbuf.begin();
//    char* tmp = buf;
//    *(int*) tmp = nlen;//绑定长度
//    tmp+= sizeof(int);

//    memcpy( tmp , szbuf , nlen);

   int res = send( lSendIP ,buf,DataLen , 0);
//    delete[] buf;
    return res;
}
//接收

void TcpClient::RecvData()
{
	int nPackSize = 0; // 存储包大小
	int nRes = 0;
	while( !m_isStop )
	{
		//接收先接收包大小 在接受数据包
		nRes = recv( m_sock , (char*)&nPackSize , sizeof(int) , 0   ); 
		//从接收缓冲区拷贝包大小
        if( nRes == 0)
        {
            this->m_isConnected = false;
            this->m_pMediator->disConnect();
            closesocket(m_sock);
            m_sock = INVALID_SOCKET;
            break;
        }
        if( nRes < 0 )
        {
            if((errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN))
            {
                continue;
            }

            closesocket(m_sock);
            m_sock = INVALID_SOCKET;
            break;
        }
		int offset = 0;
		char * buf = new char[nPackSize];
		while( nPackSize )
		{
			nRes = recv( m_sock , buf + offset , nPackSize  , 0   );
			if( nRes > 0 )
			{
				nPackSize -= nRes;
				offset += nRes;
			}
		}
		this->m_pMediator->DealData( m_sock , buf , offset  );  //需要在这个函数回收 堆区 空间
	}
}

bool TcpClient::IsConnected()
{
    return  m_isConnected;
}

