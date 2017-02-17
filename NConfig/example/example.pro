QT += sql
QT -= gui

CONFIG += c++11

TARGET = NConfig_example
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp


win32{
    DESTDIR = $$PWD/../../bin/
    MOC_DIR = $$PWD/build_/moc
    RCC_DIR = $$PWD/build_/rcc
    OBJECTS_DIR = $$PWD/build_/obj
}

# import dll file
include($$PWD/../NConfig/NConfig_inc.pri)
