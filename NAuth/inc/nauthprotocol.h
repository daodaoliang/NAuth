#ifndef NAUTHPROTOCOL_H
#define NAUTHPROTOCOL_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月18日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include "nauth_global.h"
#include "liscenseobject.h"

/**
 * @brief The NAuthProtocol class 鉴权协议封装和解析
 */
class NAUTHSHARED_EXPORT NAuthProtocol : public QObject
{
    Q_OBJECT
public:
    explicit NAuthProtocol(QObject *parent = 0);
    virtual ~NAuthProtocol(){}

public:
    /**
     * @brief PackAuthProtocol 生成本机认证封装包
     * {
     *      "product":{
     *          "version": 产品版本,
     *          "name": 产品名字
     *      },
     *      "computer":{
     *          "mac": MAC地址,
     *          "disk_serial": 系统盘逻辑序列号,
     *          "cpu_version": CPU版本,
     *          "cpu_arch": CPU架构
     *      },
     *      "system":{
     *          "sys_version": 系统版本,
     *          "sys_user": 系统用户
     *      }
     * }
     * @return
     */
    bool PackAuthProtocol(QString &param_packet);

    /**
     * @brief UnPackAuthProtocol 解析协议认证包
     * {
     *      "product":{
     *          "version": 产品版本,
     *          "name": 产品名字
     *      },
     *      "computer":{
     *          "mac": MAC地址,
     *          "disk_serial": 系统盘逻辑序列号,
     *          "cpu_version": CPU版本,
     *          "cpu_arch": CPU架构
     *      },
     *      "system":{
     *          "sys_version": 系统版本,
     *          "sys_user": 系统用户
     *      }
     * }
     * @param param_key
     * @return 是否解析成功
     */
    bool UnPackAuthProtocol(const QString &param_key);

    /**
     * @brief UnPackLicenseProtocol 解析授权认证包
     * {
     *      "date":{
     *          "apply_date": 申请日期,
     *          "begin_date": 开始日期,
     *          "end_date": 失效日期
     *      },
     *      "authority": 权限串
     * }
     * @param param_key
     * @return
     */
    bool UnPackLicenseProtocol(const QString &param_key);

    /**
     * @brief getLastError 获取错误信息
     * @return
     */
    QString getLastError() const;

    /**
     * @brief setLastError 设置错误信息
     * @param value
     */
    void setLastError(const QString &value);

private:
    /**
     * @brief getBaseRawInfo 获取本地环境的原始信息
     * @return
     */
    bool getBaseRawInfo();

private:
    /**
     * @brief applyTime 申请时间
     */
    QString applyTime;

    /**
     * @brief beginTime 有效期的开始时间
     */
    QString beginTime;

    /**
     * @brief endTime 有效期的结束时间
     */
    QString endTime;

    /**
     * @brief proVersion 产品版本
     */
    QString proVersion;

    /**
     * @brief proName 产品名字
     */
    QString proName;

    /**
     * @brief pcMAC 硬件MAC地址
     */
    QString pcMAC;

    /**
     * @brief pcSerial 硬件逻辑序列号
     */
    QString pcSerial;

    /**
     * @brief pcCPUVersion 硬件CPU版本
     */
    QString pcCPUVersion;

    /**
     * @brief pcCPUArch 硬件CPU架构
     */
    QString pcCPUArch;

    /**
     * @brief pcSysVersion 系统版本
     */
    QString sysVersion;

    /**
     * @brief pcSysUser xiton
     */
    QString sysUser;

    /**
     * @brief lastError 最近的错误信息
     */
    QString lastError;

    /**
     * @brief innerPassword 协议包密码
     */
    QString innerPassword;

    /**
     * @brief liscenceInstance 许可对象
     */
    LiscenseObject liscenceInstance;
};

#endif // NAUTHPROTOCOL_H
