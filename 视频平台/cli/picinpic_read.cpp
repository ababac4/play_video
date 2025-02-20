#include"picinpic_read.h"


//插入流进行转换
PicInPic_Read::PicInPic_Read(QObject  *parent): QObject(parent)
{
    timer = new QTimer(this);//开启定时器
    connect( timer , SIGNAL(timeout()) , this , SLOT(slot_getVideoFrame()));
}
void PicInPic_Read::slot_openVideo()
{
    cap.open(0);
    if(!cap.isOpened()){
        QMessageBox::information(NULL,tr("提示"),tr("视频没有打开"));
        return;
    }
    // 定时器不准确 ，多的丢弃 按定时器写入帧 用于同步音视频
    timer->start(1000/FRAME_RATE - 10 );

}
void PicInPic_Read::slot_closeVideo()
{
    timer->stop();

    if(cap.isOpened())
        cap.release();
}


void PicInPic_Read::slot_getVideoFrame()
{
    Mat frame;

    if( !cap.read(frame) )
    {
        return;
    }
   //画中画图片获取
    cvtColor(frame,frame,CV_BGR2RGB);

    QImage iconImage((unsigned const
                      char*)frame.data,frame.cols,frame.rows,QImage::Format_RGB888);

    iconImage = iconImage.scaled( QSize(320,240) ,Qt::KeepAspectRatio );
    //投递画中画图片
    Q_EMIT SIG_sendPicInPic( iconImage );

    //获取桌面截图
    QScreen *src = QApplication::primaryScreen();//主窗口
    QPixmap map = src->grabWindow( QApplication::desktop()->winId());//获取桌面图片
    //转化为 RGB24 QImage
    QImage image = map.toImage().convertToFormat(QImage::Format_RGB888);//转码

    //计算视频帧
//    long long time = 0;
    uint8_t * picture_buf = NULL;
    int buffer_size = ImageToYuvBuffer( image , &picture_buf );//放入缓冲区中

    Q_EMIT SIG_sendVideoFrameData( picture_buf, buffer_size );
    Q_EMIT SIG_sendVideoFrame( image );
}

int PicInPic_Read::ImageToYuvBuffer( QImage& image , uint8_t ** buffer )//RGB24 转为 yuv420p 用于显示
{
    int w = image.width();
    int h = image.height();
    int y_size = w * h;
    // image.invertPixels(QImage::InvertRgb);
    //==================== 创建 RGB 对应的空间 =========================
    AVFrame *pFrameRGB = av_frame_alloc();
    // Determine required buffer size and allocate buffer
    int numBytes1 = avpicture_get_size(AV_PIX_FMT_RGB24, w, h);
    uint8_t *buffer1 = (uint8_t *)av_malloc(numBytes1*sizeof(uint8_t));
    avpicture_fill((AVPicture *)pFrameRGB, buffer1, AV_PIX_FMT_RGB24, w, h);
    pFrameRGB->data[0] = image.bits();
    //==================== 创建 YUV 对应的空间 =========================
    AVFrame *pFrameYUV = av_frame_alloc();
    // Determine required buffer size and allocate buffer
    int numBytes2 = avpicture_get_size(AV_PIX_FMT_YUV420P, w, h);
    uint8_t *buffer2 = (uint8_t *)av_malloc(numBytes2*sizeof(uint8_t));
    avpicture_fill((AVPicture *)pFrameYUV, buffer2, AV_PIX_FMT_YUV420P, w, h);
    //  qWarning() << "numBytes2 " << numBytes2;
    //==================== 创建转化器 ================================
    SwsContext *  rgb_to_yuv_ctx = sws_getContext(w,h, AV_PIX_FMT_RGB24,
                                                  w,h, AV_PIX_FMT_YUV420P,
                                                  SWS_BICUBIC, NULL,NULL,NULL);
    sws_scale(rgb_to_yuv_ctx, pFrameRGB->data, pFrameRGB->linesize, 0,
              h, pFrameYUV->data, pFrameYUV->linesize);
    //将转换完的数据提取到缓冲区
    uint8_t * picture_buf = (uint8_t *)av_malloc(numBytes2);
    memcpy(picture_buf,pFrameYUV->data[0],y_size);
    memcpy(picture_buf+y_size,pFrameYUV->data[1],y_size/4);
    memcpy(picture_buf+y_size+y_size/4,pFrameYUV->data[2],y_size/4);
    //写返回空间
    *buffer = picture_buf;
    //qWarning() << rc << endl;
    sws_freeContext(rgb_to_yuv_ctx);
    av_free(buffer1);
    av_free(buffer2);
    av_free(pFrameRGB);
    av_free(pFrameYUV);
    return y_size*3/2;
}
