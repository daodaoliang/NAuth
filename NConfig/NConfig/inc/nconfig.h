#ifndef NCONFIG_H
#define NCONFIG_H
/**
 * 作者: daodaoliang
 * 时间: 2016年7月28日
 * 版本: 1.0.5.0
 * 邮箱: daodaoliang@yeah.net
 */
#include "nconfig_global.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QSettings>
#include "zsqlitecipherdriver.h"

/**
 * @brief The NConfigOperator class 配置项存取操作接口
 */
class NConfig_p : public QObject
{
    Q_OBJECT
public:
    NConfig_p(QObject * parent =0);
    ~NConfig_p();
public:
    /**
     * @brief initConfigDB 初始化配置数据库
     * @param paramPWD 密码
     * @param paramDBName 数据库名字
     * @return 是否初始化成功
     */
    bool initConfigDB(const QString &paramDBName, const QString &paramPWD);

    /**
     * @brief release 释放资源
     */
    void release();

    /**
     * @brief getInnerDB 获取加密后的数据库实例
     * @return
     */
    QSqlDatabase* getInnerDB();

private:

    /**
     * @brief openDB 打开指定数据库,若是不存在则创建
     * @param db
     * @param dbName
     * @param password
     * @return
     * 0   表示密码错误，或该文件不是数据库文件
     * 1   表示新建成功
     * 2   表示打开成功
     * -1  表示新建失败
     * -2  表示打开失败
     */
    int openDB(QSqlDatabase &db, const QString &dbName,const QString &password);

    /**
     * @brief isDbDecrypted 数据库是否被揭秘
     * @param db 数据库
     * @return
     */
    bool isDbDecrypted(QSqlDatabase &db);

    /**
     * @brief changePassword 修改数据库密码
     * 对已经成功打开了的数据库修改密码。注意：
     * 1. 如果数据库还未用正确密码打开，是无法使用本函数修改密码的。
     * 2. 如果数据库文件比较大，修改密码可能需要消耗比较长的时间（需要将所有的数据重新加密）.
     * 3. 密码支持的字符，这里未测试，但是单引号肯定是不能用在密码中的.
     * @param db 数据库
     * @param newPassword 新密码
     * @return 是否设置成功
     */
    bool changePassword(QSqlDatabase &db, const QString &newPassword);

private:
    /**
     * @brief innerDriver 加密的数据库驱动
     */
    ZSQLiteCipherDriver *innerDriver;

    /**
     * @brief innerDB 加密的数据库实例
     */
    QSqlDatabase innerDB;
};

/**
 * @brief The NConfig class 配置库接口
 */
class NCONFIGSHARED_EXPORT NConfig
{

public:
    NConfig();
    ~NConfig();
public:

    /**
     * @brief installAndInit 初始化配置实例
     * @param paramDB 配置数据文件的名字
     * @param paramPWD 数据文件密码
     * @param paramCheckExist 是否检查文件是否存在
     * @return
     */
    bool installAndInit(const QString &paramDB, const QString &paramPWD ,bool paramCheckExist = true);

    /**
     * @brief releaseConf 释放资源
     */
    void releaseConf();

    /**
     * @brief addConfigItem 增加配置项目(存更否创)
     * @param paramTableItem 配置项的表名
     * @param paramTableKey 配置项的名字
     * @param paramTableValue 配置项内容
     * @return 是否添加成功
     */
    bool addConfigItem(const QString &paramTableItem, const QString &paramTableKey, const QString &paramTableValue);

    /**
     * @brief getConfigItem 获取配置项
     * @param paramTableItem 配置项名字
     * @param paramTableKey 配置项key
     * @param paramTableValue 查询到的配置项值
     * @return 是否获取成功
     */
    bool getConfigItem(const QString &paramTableItem, const QString &paramTableKey, QString &paramTableValue);

    /**
     * @brief clearConfig 清空整个配置内容
     * @return 是否清空成功
     */
    bool clearConfig();

    /**
     * @brief exportConfigToFile 导出初始化后的配置库到文件里面(初始化后使用)
     * @return 是否导出成功
     */
    bool exportConfigToFile();

    /**
     * @brief importConfigFromFile 从ini文件导入到配置库(初始化后使用)
     * @param paramIniFile ini文件路径
     * @return
     */
    bool importConfigFromFile(const QString paramIniFile);

    /**
     * @brief getIsDebug 获取运行模式
     * @return
     */
    bool getIsDebug() const;

    /**
     * @brief setIsDebug 设置调试模式
     * @param value
     */
    void setIsDebug(bool value);

    /**
     * @brief getConfigFilePath 获取配置库路径
     * @return 路径
     */
    QString getConfigFilePath() const;

    /**
     * @brief setConfigFilePath 设置配置库路径
     * @param value
     */
    void setConfigFilePath(const QString &value);

private:
    /**
     * @brief innerOperator 内部加密库操作实例
     */
    NConfig_p innerOperator;

    /**
     * @brief isDebug 是否是调试模式
     */
    bool isDebug;

    /**
     * @brief configFilePath 配置库的文件路径
     */
    QString configFilePath;

    /**
     * @brief configFileName 配置文件的名字
     */
    QString configFileName;
};

#endif // NCONFIG_H
