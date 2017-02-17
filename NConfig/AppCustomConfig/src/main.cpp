#include <QCoreApplication>
#include "appcustomconfig.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // 读一遍
    if(!APPConfigInstance.initAndReadConf(QCoreApplication::applicationDirPath() + "/app.conf","daodaoliang")){
        qDebug()<<"读取配置文件失败";
    }
    // 再读一遍
    if(!APPConfigInstance.initAndReadConf(QCoreApplication::applicationDirPath() + "/app.conf","daodaoliang")){
        qDebug()<<"读取配置文件失败";
    }
    return a.exec();
}
