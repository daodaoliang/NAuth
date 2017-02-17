#-------------------------------------------------
#
# Project created by QtCreator 2016-07-26T10:03:02
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = NConfig
TEMPLATE = lib
CONFIG += c++11
DEFINES += NCONFIG_LIBRARY

# 引入源码
include(NConfig_src.pri)
INCLUDEPATH += ./inc/ \

# 引入第三方源码

include($$PWD/3rdparty/wxsqlite3/wxsqlite3.pri)
include($$PWD/3rdparty/zsqlitecipherdriver/zsqlitecipherdriver.pri)

# 引入第三方头文件路径
INCLUDEPATH += $$PWD\3rdparty\wxsqlite3
INCLUDEPATH += $$PWD\3rdparty\zsqlitecipherdriver

# 设置版本信息

RC_FILE += ./NConfig_resource.rc

# 设定编译输出路径
win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = ./build_/dist
        } else {
            target_path = ./build_/debug
        }
        DESTDIR = ./../../bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        OBJECTS_DIR = $$target_path/obj
}

# 输出编译套件信息
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the NConfig will create in folder: $$target_path)
