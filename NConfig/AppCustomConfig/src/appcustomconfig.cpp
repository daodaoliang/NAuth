#include "appcustomconfig.h"

AppCustomConfig::AppCustomConfig(QObject *parent)
    :QObject(parent)
{

}

AppCustomConfig::~AppCustomConfig()
{

}

bool AppCustomConfig::initAndReadConf(QString confFilePath, QString confFilePwd)
{
    // 获取配置文件
    bool ret = nConfig_p.installAndInit(confFilePath, confFilePwd);
    if(!ret) return ret;
    // 读取配置项
    if(!nConfig_p.getConfigItem("localmysql","host",configItem_localMysql_host)){
        qDebug() << "读取配置项失败";
        return false;
    }else {
        qDebug() << "读取配置成功:" <<configItem_localMysql_host;
    }
    // 读取user
    if(!nConfig_p.getConfigItem("localmysql","user",configItem_localMysql_user)){
        qDebug() << "读取配置项失败";
        return false;
    }else {
        qDebug() << "读取配置成功:" << configItem_localMysql_user;
    }
    // 读取db
    if(!nConfig_p.getConfigItem("localmysql","db",configItem_localMysql_db)){
        qDebug() << "读取配置项失败";
        return false;
    }else {
        qDebug() << "读取配置成功:" << configItem_localMysql_db;
    }
    // 读取pwd
    QString tempConfigPWD;
    if(!nConfig_p.getConfigItem("localmysql","password",configItem_localMysql_password)){
        qDebug() << "读取配置项失败";
        return false;
    }else {
        qDebug() << "读取配置成功:" << configItem_localMysql_password;
    }
    // 读取port
    QString tempConfigPort;
    if(!nConfig_p.getConfigItem("localmysql","port",tempConfigPort)){
        qDebug() << "读取配置项失败";
        return false;
    }else {
        qDebug() << "读取配置成功:" << tempConfigPort;
        configItem_localMysql_port = tempConfigPort.toInt();
    }
    nConfig_p.releaseConf();
    return true;
}
