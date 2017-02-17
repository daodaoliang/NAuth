#ifndef NAUTH_H
#define NAUTH_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月18日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QCoreApplication>
#include "nauth_global.h"
#include "nauthprotocol.h"

/**
 * @brief The NAuth class 认证鉴权组件
 */
class NAUTHSHARED_EXPORT NAuth : public QObject
{
    Q_OBJECT
public:
    explicit NAuth(QObject* parent=NULL);

public:
    /**
     * @brief exportKeyFile 导出 key 文件到指定目录
     * @param paramPath 文件路径
     * @return
     */
    bool exportKeyFile(const QString &paramPath = QCoreApplication::applicationDirPath() + "/");

    /**
     * @brief importKeyFile 导入 key 文件并进行解析
     * @param paramPath 文件路径
     * @return
     */
    bool importKeyFile(const QString &paramPath = QCoreApplication::applicationDirPath() + "/");

    /**
     * @brief authWorkFlow 认证工作流程
     * @return
     */
    bool authWorkFlow();

    /**
     * @brief getLastError 获取最后一次错误信息
     * @return
     */
    QString getLastError() const;

    /**
     * @brief setLastError 设置最后一次错误信息
     * @param value
     */
    void setLastError(const QString &value);

private:
    /**
     * @brief protocolInstance 协议操作实例
     */
    NAuthProtocol protocolInstance;

    /**
     * @brief lastError 最后一次错误信息
     */
    QString lastError;
};

#endif // NAUTH_H
