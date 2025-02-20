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
    static WriteLog* GetInstance();
    void Write_log(int type,string content);

private:
    WriteLog();


    void init();
    void WriteThread();
    ~WriteLog();
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
