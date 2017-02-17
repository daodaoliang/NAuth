SOURCES += \
    $$PWD/src/appcustomconfig.cpp

HEADERS += \
    $$PWD/inc/appcustomconfig.h

INCLUDEPATH += $$PWD/inc/

# 引入配置库
include($$PWD/../NConfig/NConfig_inc.pri)
win32: LIBS += -L$$PWD/../bin/ -lNConfig

# 引入第三方
include($$PWD/3rdparty/singleton/singleton.pri)
