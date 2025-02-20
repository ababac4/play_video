QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Play_music.cpp \
    addfridio.cpp \
    chatdiolog.cpp \
    ckenel.cpp \
    friendlist.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    mytablewidegt.cpp \
    play_dialog.cpp \
    show_pdf.cpp \
    useritem.cpp \
    vedio_play.cpp \
    writelog.cpp

HEADERS += \
    Play_music.h \
    addfridio.h \
    chatdiolog.h \
    cjson.h \
    ckenel.h \
    friendlist.h \
    logindialog.h \
    mainwindow.h \
    mytablewidegt.h \
    play_dialog.h \
    show_pdf.h \
    useritem.h \
    vedio_play.h \
    writelog.h

FORMS += \
    addfridio.ui \
    chatdiolog.ui \
    friendlist.ui \
    logindialog.ui \
    mainwindow.ui \
    play_dialog.ui \
    show_pdf.ui \
    useritem.ui
include(./netapi/netapi.pri)
    INCLUDEPATH +=./netapi/
include(./md5/md5.pri)
    INCLUDEPATH +=./md5
include(./sqlapi/sqlapi.pri)
INCLUDEPATH +=./sqlapi

INCLUDEPATH += $$PWD/cryptopp565-release/include
LIBS +=-L$$PWD/cryptopp565-release/bin/-lcryptopp565
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
include(./cryptopp/cryptopp.pri)
INCLUDEPATH+=./cryptopp/
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QT+=core
RESOURCES += \
    resource.qrc

win32: LIBS += -L$$PWD/proper/ -llibpoppler.dll

INCLUDEPATH += $$PWD/proper
DEPENDPATH += $$PWD/proper

win32: LIBS += -L$$PWD/proper/ -llibpoppler-qt5.dll

INCLUDEPATH += $$PWD/proper
DEPENDPATH += $$PWD/proper

DISTFILES += \
    images/Cancel_32x32.png \
    images/CheckBox_32x32.png \
    images/PDF.png \
    images/addFile.png \
    images/check.png \
    images/delete.png \
    images/file.png \
    images/folder.png \
    images/logo.ico \
    images/pause.png \
    images/play.png \
    images/search.png \
    images/share.png \
    images/transmit.ico
