
INCLUDEPATH += $$PWD/cryptopp565-release/

#LIBS += -L$$PWD/cryptopp565-release/lib/   -lcryptopp565
LIBS += -L$$PWD/cryptopp565-release/bin/debug   -lcryptopp565


HEADERS += \
    $$PWD/cmyaes.h \
    $$PWD/cmydes.h \
    $$PWD/cmyrsa.h

SOURCES += \
    $$PWD/cmyaes.cpp \
    $$PWD/cmydes.cpp \
    $$PWD/cmyrsa.cpp
