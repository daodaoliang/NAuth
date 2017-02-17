#-------------------------------------------------
#
# Project created by QtCreator 2016-07-29T17:36:52
#
#-------------------------------------------------

QT       -= gui
QT       += network sql
TARGET = NAuth
TEMPLATE = lib

DEFINES += NAUTH_LIBRARY
CONFIG += c++11

# 引入源码
include($$PWD/NAuth_src.pri)

# 引入 第三方组件
include($$PWD/../NComputerInfo/NComputerInfo/NComputerInfo_inc.pri)
include($$PWD/../NEncryptionKit/NEncryptionKit/NEncryptionKit_inc.pri)
include($$PWD/../NConfig/NConfig/NConfig_inc.pri)

RC_FILE += ./NAuth_resource.rc

# 定义输出
win32{
    CONFIG += debug_and_release
    CONFIG(release, debug|release) {
            target_path = ./build_/dist
        } else {
            target_path = ./build_/debug
        }
        DESTDIR = ../bin
        MOC_DIR = $$target_path/moc
        RCC_DIR = $$target_path/rcc
        OBJECTS_DIR = $$target_path/obj
}

# 调试器信息
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message(the NAuth will create in folder: $$target_path)
