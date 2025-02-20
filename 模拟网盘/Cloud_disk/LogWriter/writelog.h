#ifndef WRITELOG_H
#define WRITELOG_H
#include<iostream>
#include<mutex>
#include<condition_variable>
#include<deque>
#include<string.h>

#include<thread>
using namespace std;
struct Mytime{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int seconds;
    int ms;
    static Mytime Get_Time(){
        chrono::system_clock::time_point pt=chrono::system_clock::now();//根据系统时间获取当前时钟
        time_t tp=chrono::system_clock::to_time_t(pt);//转换为时间time_t类型
        struct tm* t=localtime(&tp);//转换为c时间结构体

        //输出毫秒
        auto du=pt.time_since_epoch();//转换为格林威治时间戳
        auto ms=chrono::duration_cast<chrono::milliseconds>(du).count();//chrono转换
        //求余
        ms=ms%1000;
        Mytime mt;
         mt.year=t->tm_year+1900;
         mt.month=t->tm_mon+1;
         mt.day=t->tm_mday;
         mt.hour=t->tm_hour;
         mt.min=t->tm_min;
         mt.seconds=t->tm_sec;
         mt.ms=ms;

//        cout<<"ms:"<<ms<<endl;
//        cout<<"year:"<<t->tm_year+1900<<endl;
//        cout<<"month"<<t->tm_mon+1<<endl;
//        cout<<"day:"<<t->tm_mday<<endl;
//        cout<<"hour:"<<t->tm_hour<<endl;
//        cout<<"min"<<t->tm_min<<endl;
//        cout<<"second:"<<t->tm_sec<<endl;
//        cout<<"ms:"<<ms<<endl;
        return mt;
    }
};

class WriteLog
{
public:
    static WriteLog* GetInstance(){
        static WriteLog w_log;
        return &w_log;
    }
    void Write_log(int type,string content){
        n_time=Mytime::Get_Time();
        //投入生产者消费者队列
        string res;
        char buf[1024]="";
      sprintf(buf,"./%04d_%02d_%02d_%02d_%02d_%02d_%03d",n_time.year,n_time.month,n_time.day,n_time.hour,n_time.min,n_time.seconds,n_time.ms);
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

private:
    WriteLog(){
       init();

       //创建线程
        thread th1(&WriteLog::WriteThread,this);
       //线程回收
        th1.detach();
    }
    void init(){

       n_time=Mytime::Get_Time();
     //获取当前时间
      char buf[1024]="";
    sprintf(buf,"./%04d_%02d_%02d_%02d_%02d_%02d_%03d",n_time.year,n_time.month,n_time.day,n_time.hour,n_time.min,n_time.seconds,n_time.ms);

     //文件创建
    p_file=fopen(buf,"w");
    n_count=0;
    }
    void WriteThread(){
        //消费者队列
        while(!is_quit){
           unique_lock<mutex>u_lck(m_tex);
           while(que.empty()&&!is_quit){
               con_tex.wait(u_lck);
           }


           n_count++;

           if(n_count>=20){//大于20行时
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
    ~WriteLog(){
    is_quit=true;
    //唤醒挂起的消费者进行退出
    con_tex.notify_one();
    this_thread::sleep_for(chrono::milliseconds(20));
    }

    WriteLog(const WriteLog&)=delete;
    WriteLog &operator=(const WriteLog&)=delete;

private:
    bool is_quit=false; //退出标志位
    FILE* p_file;//文件指针
    mutex m_tex;//互斥锁
    condition_variable con_tex;//条件变量
    deque<string>que;
    int n_count;
    Mytime n_time;

};

#endif // WRITELOG_H
