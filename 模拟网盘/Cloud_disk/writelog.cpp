#include<writelog.h>


WriteLog *WriteLog::GetInstance()
{
      static WriteLog w_log;
      return &w_log;
}

void WriteLog::Write_log(int type, string content)
{
    n_time=Mytime::Get_Time();
    //投入生产者消费者队列
    string res;
    char buf[1024]="";
  sprintf(buf,"%04d_%02d_%02d_%02d_%02d_%02d_%03d",n_time.year,n_time.month,n_time.day,n_time.hour,n_time.min,n_time.seconds,n_time.ms);
  res+=buf;
  switch (type) {
  case 0:
      res+="[INFO]";
      break;
  case 1:
      res+="[ERROR]";
      break;
  case 2:
      res+="[WARING]";
      break;
  default:
      res+="[INFO]";
      break;
  }

  res=res+content+"\n";//换行符结尾

   unique_lock<mutex>ulock(m_tex);
   //投递到任务队列
   que.emplace_back(res);
   ulock.unlock();
   //投递任务一次，唤醒一次
   con_tex.notify_one();
}

WriteLog::WriteLog()
{
    init();

    //创建线程
     thread th1(&WriteLog::WriteThread,this);
    //线程回收
     th1.detach();
}

void WriteLog::init()
{
    n_time=Mytime::Get_Time();
  //获取当前时间
   char buf[1024]="";
 sprintf(buf,"./Log/%04d_%02d_%02d_%02d_%02d_%02d_%03d",n_time.year,n_time.month,n_time.day,n_time.hour,n_time.min,n_time.seconds,n_time.ms);

  //文件创建
 p_file=fopen(buf,"w");
 n_count=0;
}

void WriteLog::WriteThread()
{
    //消费者队列
    while(!is_quit){
       unique_lock<mutex>u_lck(m_tex);
       while(que.empty()&&!is_quit){
           con_tex.wait(u_lck);
       }


       n_count++;

       if(n_count>=50){//大于50行时 可以通过时间来进行文件切换
           fclose(p_file);
           init();//重开文件
       }
       //从头部取出任务
       cout<<que.front()<<endl;
       string ans=que.front();

       que.pop_front();
       fwrite(ans.c_str(),1,strlen(ans.c_str()),p_file);
       fflush(p_file);//主动写入缓冲区内容

    }
    fclose(p_file);
}

WriteLog::~WriteLog()
{
    is_quit=true;
    //唤醒挂起的消费者进行退出
    con_tex.notify_one();
    this_thread::sleep_for(chrono::milliseconds(20));
}


