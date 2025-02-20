#ifndef SAVEVIDEOTHREAD_H
#define SAVEVIDEOTHREAD_H

#include <QThread>
#include<QApplication>
#include"Audio_Read.h"
#include<QScreen>

//管理线程 来转发采集线程的画面来，防止显示直接访问采集对象

#include"picinpic_read.h"
#include<QMutex>
// a wrapper around a single output AVStream
typedef struct OutputStream {
    AVStream *st;
    AVCodecContext *enc;

    /* pts of the next frame that will be generated */
    int64_t next_pts;
    int samples_count;

    AVFrame *frame;
    AVFrame *tmp_frame;
    uint8_t*frameBuffer;
    int frameBufferSize;
    float t, tincr, tincr2;

    struct SwsContext *sws_ctx;
    struct SwrContext *swr_ctx;
} OutputStream;


#define STREAM_PIX_FMT    AV_PIX_FMT_YUV420P /* default pix_fmt */
struct STRU_AV_FORMAT{

    bool hasCamera;
    bool hasDesk;
    bool hasAudio;
    //////视频信息///////
    int width;
    int height;
    int frame_rate;
    int videoBitRate;
    QString filename;
    //int codec_id; H.264 默认编码格式
    //int pix_fmt;//默认yuv
    /////音频///////

};

struct BufferDataNode
{
uint8_t * buffer;
int bufferSize;
int64_t time;  //视频帧用于稳帧, 比较时间
};

class savevideothread : public QThread
{
    Q_OBJECT

public:
signals:
    void SIG_sendVideoFrame( QImage img ); // 用于预览 桌面图片
    void SIG_sendPicInPic( QImage img ); //用于显示画中画 截图时，小窗口来显示摄像头
public:
    savevideothread();

    bool write_video_frame(AVFormatContext *oc, OutputStream *ost, double time);
public slots:
    void Slot_writeVideoFrameData(  uint8_t* picture_buf, int buffer_size ); //采集的数据格式YUV420P

    void slot_openvideo();
    void slot_closevideo();
    void setinfo(STRU_AV_FORMAT &av_format);//设置视频格式
    void Slot_writeaudioFrameData(uint8_t *picture_buf, int buffer_size);
    void videoDataQuene_Input(uint8_t *buffer, int size, int64_t time);
    BufferDataNode *videoDataQuene_get(int64_t time);
    void audioDataQuene_Input(const uint8_t *buffer, const int &size);
    BufferDataNode *audioDataQuene_get();
    void run();
private:
    //采集 数据 读线程管理
    PicInPic_Read  *pic_Read;
    STRU_AV_FORMAT m_av_format;
    //编码初始化变量
    OutputStream video_st = { 0 }, audio_st = { 0 };
    const char *filename;
    AVOutputFormat *fmt;
    AVFormatContext *oc;
    AVCodec *audio_codec, *video_codec;
    Audio_Read* m_audio;
    int ret;
    int have_video = 0, have_audio = 0;
    int encode_video = 0, encode_audio = 0;
    AVDictionary *opt = NULL;
    int i;
    int mAudioOneFrameSize;

    QList<BufferDataNode*> m_videoDataList;
    QList<BufferDataNode*> m_audioDataList;
    BufferDataNode* lastVideoNode;
    bool m_videoBeginFlag;
    QMutex m_videoMutex;
    QMutex m_audioMutex;
    bool isStop;
    int64_t video_pts;
    int64_t audio_pts;
    qint64 m_videoBeginTime;
    //不能外部直接访问
    void add_audio_stream(OutputStream *ost, AVFormatContext *oc, AVCodec **codec, AVCodecID codec_id);
    void add_video_stream(OutputStream *ost, AVFormatContext *oc, AVCodec **codec, AVCodecID codec_id);
    void open_video(AVFormatContext *oc, AVCodec *codec, OutputStream *ost);
    void close_stream(AVFormatContext *oc, OutputStream *ost);
    int write_frame(AVFormatContext *fmt_ctx, AVCodecContext *c, AVStream *st, AVFrame *frame);
    void open_audio(AVFormatContext *oc, AVCodec *codec, OutputStream *ost);
    int write_frame(AVFormatContext *fmt_ctx, AVCodecContext *c, AVStream *st, AVFrame *frame, int64_t &pts, OutputStream *ost);
    bool write_audio_frame(AVFormatContext *oc, OutputStream *ost);
};

#endif // SAVEVIDEOTHREAD_H
