#ifndef LISCENSEOBJECT_H
#define LISCENSEOBJECT_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月25日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include "nauth_global.h"

/**
 * @brief The LiscenseObject class 权限对象实体
 */
class NAUTHSHARED_EXPORT LiscenseObject : public QObject
{
    Q_OBJECT
public:
    explicit LiscenseObject(QObject *parent = 0);

    bool unPackLiscense(const QString &param_key);

public:
    /**
     * @brief getLiscenseRaw 获取许可原始数据
     * @return
     */
    QString getLiscenseRaw() const;

    /**
     * @brief setLiscenseRaw 设置许可原始数据
     * @param value
     */
    void setLiscenseRaw(const QString &value);

    /**
     * @brief getLastError 获取错误描述信息
     * @return
     */
    QString getLastError() const;

    /**
     * @brief setLastError 设置错误描述
     * @param value
     */
    void setLastError(const QString &value);

private:
    /**
     * @brief LiscenseRaw 许可原始数据
     */
    QString liscenseRaw;

    /**
     * @brief lastError 最近的错误描述
     */
    QString lastError;
};

#endif // LISCENSEOBJECT_H
