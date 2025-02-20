#ifndef VEDIO_PLAY_H
#define VEDIO_PLAY_H

#include <QThread>
#include<QImage>
#include<QDebug>
#include "Play_music.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
#include "libavdevice/avdevice.h"
#include"libswresample/swresample.h"
#include"libavutil/time.h"
#include "SDL.h"
}

#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000  //1 second of 48khz 32bit audio 解码后能存储的最大大小 4（32位）*48
#define SDL_AUDIO_BUFFER_SIZE   1024//一个采样空间 1024位
// 回调函数的参数，时间和有无流的判断
typedef struct {
    time_t lasttime;
    bool connected;
} Runner;
enum PlayerState
{
    Playing = 0,
    Pause,
    Stop
};
class Vedio_play;
typedef struct VideoState {
    AVFormatContext *pFormatCtx;//相当于视频”文件指针”
    ///////////////音频///////////////////////////////////
    AVStream *audio_st; //音频流
    PacketQueue *audioq;//音频缓冲队列
    AVCodecContext *pAudioCodecCtx ;//音频解码器信息指针
    int audioStream;//视频音频流索引
    double audio_clock; ///<pts of last decoded frame 音频时钟
    SDL_AudioDeviceID audioID; //音频 ID
    AVFrame out_frame; //设置参数，供音频解码后的swr_alloc_set_opts使用。
    /// 音频回调函数使用的量
    uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
    unsigned int audio_buf_size = 0;
    unsigned int audio_buf_index = 0;
    AVFrame *audioFrame;
    //////////////////////////////////////////////////////
    ///////////////视频///////////////////////////////////
    AVStream
    *video_st; //视频流
    PacketQueue *videoq;//视频队列
    AVCodecContext *pCodecCtx ;//音频解码器信息指针
    int videoStream;//视频音频流索引
    double video_clock; ///<pts of last decoded frame 视频时钟
    SDL_Thread *video_tid;  //视频线程id
    /////////////////////////////////////////////////////
    //////////////////////////////////////////////////////
    /// 播放控制的变量
    bool isPause=false;//暂停标志
    bool quit=false; //停止
    bool readFinished=true; //读线程文件读取完毕
    bool readThreadFinished=true; //读取线程是否结束
    bool videoThreadFinished=true; // 视频线程是否结束
    SDL_TimerID timer_id;
    /////////////////////////////////////////////////////
    //// 跳转相关的变量
    int seek_req; //跳转标志 -- 读线程
    int64_t seek_pos; //跳转的位置 -- 微秒
    int seek_flag_audio;//跳转标志 -- 用于音频线程中
    int  seek_flag_video;//跳转标志 -- 用于视频线程中
    double seek_time; //跳转的时间(秒)  值和seek_pos是一样的
    //////////////////////////////////////////////////////
    int64_t start_time; //单位 微秒
    //////////////////////////////////////////////////////

    VideoState()
    {
        audio_clock = video_clock  = start_time = 0;
    }

    Vedio_play* m_player;//用于调用函数
} VideoState;


class Vedio_play : public QThread
{
    Q_OBJECT
public:
    //为了完成播放的控制, 需要在VideoPlayer中添加成员PlayerState m_playerState;播放状态是一个枚举,
    //代表着播放状态.

signals:
    void sig_sendimg(QImage img);
    void SIG_PlayerStateChanged(int flag);
    void SIG_TotalTime(qint64 uSec);
public:
    Vedio_play();
    ~Vedio_play(){
        stop(true);
    }
    void run();
    void setFileName(const QString &newFileName);
    ///播放控制
    void play();
    void pause();
    void stop( bool isWait);

    PlayerState playerState() const;

    void packet_queue_flush(PacketQueue *q);
    void seek(int64_t pos);
    double getCurrentTime();
    int64_t getTotalTime();
public slots:
    void SendGetOneImage(QImage &img);

private:
    QString m_fileName;
    VideoState m_videoState;
    PlayerState m_playerState;
};

#endif // VEDIO_PLAY_H
