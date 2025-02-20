TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


INCLUDEPATH += ./include

LIBS+= -lpthread -lmysqlclient

SOURCES += \
    src/Thread_pool.cpp \
    src/TCPKernel.cpp \
    src/Mysql.cpp \
    src/main.cpp \
    src/err_str.cpp \
    src/clogic.cpp \
    src/block_epoll_net.cpp \
    src/credis.cpp \
    src/cmyaes.cpp \
    src/cmyrsa.cpp \
    src/writelog.cpp \
    src/md5.cpp

OTHER_FILES +=

HEADERS += \
    include/Thread_pool.h \
    include/TCPKernel.h \
    include/packdef.h \
    include/Mysql.h \
    include/err_str.h \
    include/clogic.h \
    include/block_epoll_net.h \
    include/credis.h \
    include/cmyrsa.h \
    include/cmyaes.h \
    include/cjson.h \
    include/writelog.h \
    include/md5.h

QMAKE_CXXFLAGS += -std=c++11
LIBS += -L/usr/local/lib/ -ljson
INCLUDEPATH += /usr/local/include/json/
 LIBS+=-lcryptopp
LIBS +=-lhiredis
 INCLUDEPATH += /usr/include/
 LIBS +=-lalibabacloud-sdk-core
