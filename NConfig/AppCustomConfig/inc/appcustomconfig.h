#ifndef APPCUSTOMCONFIG_H
#define APPCUSTOMCONFIG_H
#include "nconfig.h"
#include <QObject>
#include "singleton.h"

#define APPConfigInstance Singleton<AppCustomConfig>::instance()

/**
 * @brief The AppCustomConfig class 应用程序配置文件读取并对外提供变量
 */
class AppCustomConfig: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief AppCustomConfig 构造函数
     */
    AppCustomConfig(QObject *parent=NULL);
    virtual ~AppCustomConfig();


    /**
     * @brief initAndReadConf 初始化并读取配置文件
     * @param confFilePath
     * @param confFilePwd
     * @return
     */
    bool initAndReadConf(QString confFilePath, QString confFilePwd);

public:
    /**
     * @brief configItem_localMysql_host 本地数据库的host
     */
    QString configItem_localMysql_host;

    /**
     * @brief configItem_localMysql_user 本地数据库的user
     */
    QString configItem_localMysql_user;

    /**
     * @brief configItem_localMysql_password 本地数据库的pwd
     */
    QString configItem_localMysql_password;

    /**
     * @brief configItem_localMysql_db 本地数据库的db
     */
    QString configItem_localMysql_db;

    /**
     * @brief configItem_localMysql_port 本地数据库的port
     */
    int configItem_localMysql_port;

private:
    NConfig nConfig_p;
};

#endif // APPCUSTOMCONFIG_H
