CONFIG(release, debug|release):DEFINES *= NDEBUG

DEFINES += SQLITE_HAS_CODEC

# 引入查找路径
INCLUDEPATH += $$PWD
DEPENDPATH  += $$PWD

#  引入源码
HEADERS += \
    $$PWD/sqlite3.h \
    $$PWD/codec.h \
    $$PWD/rijndael.h \
    $$PWD/sha2.h

SOURCES += \
    $$PWD/sqlite3.c \
    $$PWD/sqlite3secure.c \
    $$PWD/codec.c \
    $$PWD/rijndael.c \
    $$PWD/codecext.c \
    $$PWD/sha2.c
