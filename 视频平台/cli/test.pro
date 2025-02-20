QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(./netapi/netapi.pri)
INCLUDEPATH +=./netapi/

include(./md5/md5.pri)
INCLUDEPATH +=./md5

SOURCES += \
    Play_music.cpp \
    addfridio.cpp \
    audio_read.cpp \
    chatdiolog.cpp \
    ckenel.cpp \
    comment.cpp \
    comment_dialog.cpp \
    comment_user.cpp \
    friendlist.cpp \
    history_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    picinpic_read.cpp \
    picture_widget.cpp \
    play_dialog.cpp \
    recorder_dialog.cpp \
    savevideothread.cpp \
    upload_file.cpp \
    uploadplike.cpp \
    useritem.cpp \
    vedio_play.cpp

HEADERS += \
    Play_music.h \
    addfridio.h \
    audio_read.h \
    chatdiolog.h \
    ckenel.h \
    comment.h \
    comment_dialog.h \
    comment_user.h \
    common.h \
    friendlist.h \
    history_dialog.h \
    mainwindow.h \
    picinpic_read.h \
    picture_widget.h \
    play_dialog.h \
    recorder_dialog.h \
    savevideothread.h \
    upload_file.h \
    uploadplike.h \
    useritem.h \
    vedio_play.h

FORMS += \
    addfridio.ui \
    chatdiolog.ui \
    comment.ui \
    comment_dialog.ui \
    comment_user.ui \
    friendlist.ui \
    history_dialog.ui \
    mainwindow.ui \
    picture_widget.ui \
    play_dialog.ui \
    recorder_dialog.ui \
    upload_file.ui \
    useritem.ui
INCLUDEPATH += $$PWD/ffmpeg-4.2.2/include\
        C:/Qt/opencv-release/include/opencv2\
        C:/Qt/opencv-release/include\
INCLUDEPATH += $$PWD/ffmpeg-4.2.2/include

INCLUDEPATH += $$PWD/ffmpeg-4.2.2/include\
    $$PWD/SDL2-2.0.10/include
    LIBS += $$PWD/ffmpeg-4.2.2/lib/avcodec.lib\
    $$PWD/ffmpeg-4.2.2/lib/avdevice.lib\
    $$PWD/ffmpeg-4.2.2/lib/avfilter.lib\
    $$PWD/ffmpeg-4.2.2/lib/avformat.lib\
    $$PWD/ffmpeg-4.2.2/lib/avutil.lib\
    $$PWD/ffmpeg-4.2.2/lib/postproc.lib\
    $$PWD/ffmpeg-4.2.2/lib/swresample.lib\
    $$PWD/ffmpeg-4.2.2/lib/swscale.lib\
    $$PWD/SDL2-2.0.10/lib/x86/SDL2.lib
LIBS+= C:\Qt\opencv-release\lib\libopencv_*.dll.a
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    face/btn_avatar_a20.png \
    face/btn_avatar_a21.png \
    face/btn_avatar_a22.png \
    face/btn_avatar_a23.png \
    face/btn_avatar_a24.png \
    face/btn_avatar_a25.png \
    face/btn_avatar_a26.png \
    face/btn_avatar_a27.png \
    face/btn_avatar_a28.png \
    face/btn_avatar_a29.png \
    face/btn_avatar_a30.png \
    face/btn_avatar_a31.png \
    face/btn_avatar_a32.png \
    face/btn_avatar_a33.png \
    face/btn_avatar_a34.png \
    face/btn_avatar_a35.png \
    face/btn_avatar_a36.png \
    face/btn_avatar_a37.png \
    face/btn_avatar_a38.png \
    face/btn_avatar_a39.png
