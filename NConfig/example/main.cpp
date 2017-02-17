#include <QCoreApplication>

#include "nconfig.h"
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() <<"**************************************测试用例开始*************************************" << "\r\n";

    qDebug() <<"--------------------------------------初始化测试开始-----------------------------------";
    NConfig NConfigInstance;
    qDebug() << "配置文件是否打开成功:" << NConfigInstance.installAndInit(QCoreApplication::applicationDirPath() + "/app.conf", "daodaoliang", false);
    qDebug() <<"--------------------------------------初始化测试完毕-----------------------------------" << "\r\n";

    qDebug() <<"--------------------------------------添加配置测试开始---------------------------------";
    qDebug() << "增加测试配置项开始";
    NConfigInstance.addConfigItem("localmysql","host","127.0.0.1");
    NConfigInstance.addConfigItem("localmysql","user","root");
    NConfigInstance.addConfigItem("localmysql","password","Fuck1024");
    NConfigInstance.addConfigItem("localmysql","db","caterwisdom");
    NConfigInstance.addConfigItem("localmysql","port","3306");
    NConfigInstance.addConfigItem("app","version","1.0.1.0");
    NConfigInstance.addConfigItem("app","name","cater-center");
    qDebug() << "增加测试配置项结束";
    qDebug() <<"--------------------------------------添加配置测试完毕---------------------------------" << "\r\n";

    qDebug() <<"--------------------------------------读取配置测试开始---------------------------------";
    qDebug() << "读取测试配置项";
    QString tempValue;
    qDebug() << "是否读取成功:" << NConfigInstance.getConfigItem("localmysql","user",tempValue);
    qDebug() << "读取到的值:" << tempValue;
    qDebug() << "是否读取成功:" << NConfigInstance.getConfigItem("localmysql","password",tempValue);
    qDebug() << "是否读取成功:" << NConfigInstance.getConfigItem("localmysql","errorKey",tempValue);
    qDebug() <<"--------------------------------------读取配置测试完毕---------------------------------" << "\r\n";

    qDebug() <<"--------------------------------------导出配置测试开始---------------------------------";
    qDebug() << "是否导出成功:" << NConfigInstance.exportConfigToFile();
    qDebug() <<"--------------------------------------导出配置测试完毕---------------------------------" << "\r\n";

    qDebug() <<"--------------------------------------清空配置测试开始---------------------------------";
    qDebug() << "测试清空配置库";
    qDebug()<< "是否清理成功:" << NConfigInstance.clearConfig();
    qDebug() <<"--------------------------------------清空配置测试完毕---------------------------------" << "\r\n";

    qDebug() <<"--------------------------------------导入配置测试开始---------------------------------";
    qDebug() << "是否导入成功:" << NConfigInstance.importConfigFromFile(QCoreApplication::applicationDirPath() + "/app.ini");
    qDebug() <<"--------------------------------------导入配置测试完毕---------------------------------" << "\r\n";

    NConfigInstance.releaseConf();
    qDebug() <<"**************************************测试用例结束************************************";

    return a.exec();
}
