#include "uploadplike.h"
#include"TcpClientMediator.h"
#include"ckenel.h"
UploadPlike::UploadPlike(QObject *parent) : QThread(parent)
{

    m_running=1;
}

void UploadPlike::run()
{
    QTimer timer;
    connect(&timer, &QTimer::timeout, this, &UploadPlike::upload);
    timer.start(10000); // 每30秒触发一次doWorsk()

    // 使用事件循环来保持线程运行
    exec();


}

void UploadPlike::upload()
{

    for(auto a:m_user_Plike){
        STRU_PLIKE_RQ rq;

        int pre_play=0;
        int pre_like=0;
        if(m_pre_Plike.find(a.first)!=m_pre_Plike.end()){
            pre_like=m_pre_Plike[a.first]->like;
            pre_play=m_pre_Plike[a.first]->play;
        }
        rq.file_id=a.first;
        rq.like=a.second->like-pre_like;
        rq.play=a.second->play-pre_play;
        if(rq.like<0) rq.like=0;
        if(rq.play<0) rq.play=0;
        rq.user_id=user_id;
        cout<<a.first<<' '<< rq.like<<' '<<rq.play<<endl;
        Ckenel::create()->Tcpclient->SendData(0,(char*)&rq,sizeof(rq));
    }
    for(auto a:m_user_Plike){
       m_pre_Plike[a.first]=a.second;
    }
}
