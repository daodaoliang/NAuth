#include <QCoreApplication>
#include <QDebug>
#include "nauth.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"*****************************************pc.key导出测试开始**********************************************";
    NAuth testINstance001;
    bool ret = testINstance001.exportKeyFile();
    qDebug() << "文件是否导出成功:"<<ret << " lastError:" << testINstance001.getLastError();;
    qDebug()<<"*****************************************pc.key导出测试结束**********************************************";

    qDebug()<<"*****************************************pc.key导入测试开始**********************************************";
    NAuth testINstance002;
    bool ret2 = testINstance002.importKeyFile();
    qDebug() << "文件是否导入成功:"<<ret2 << " lastError:" << testINstance002.getLastError();
    qDebug()<<"*****************************************pc.key导入测试结束**********************************************";

    return a.exec();
}
