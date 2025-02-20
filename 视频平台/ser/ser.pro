TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ./include

LIBS+= -lpthread -lmysqlclient

SOURCES += \
    src/main.cpp \
    src/block_epoll_net.cpp \
    src/clogic.cpp \
    src/err_str.cpp \
    src/Mysql.cpp \
    src/TCPKernel.cpp \
    src/Thread_pool.cpp \
    src/credis.cpp

HEADERS += \
    include/Thread_pool.h \
    include/TCPKernel.h \
    include/packdef.h \
    include/Mysql.h \
    include/err_str.h \
    include/clogic.h \
    include/block_epoll_net.h \
    include/credis.h

QMAKE_CXXFLAGS += -std=c++11

LIBS +=-lhiredis
 INCLUDEPATH += /usr/include/
 LIBS +=-lalibabacloud-sdk-core

