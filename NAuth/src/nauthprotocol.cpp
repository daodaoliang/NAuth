#include "nauthprotocol.h"
#include "ncomputerinfo.h"
#include "nconfig.h"
#include "nencryptionkit.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>
#include <string>
using namespace std;

NAuthProtocol::NAuthProtocol(QObject *parent) : QObject(parent)
{
    innerPassword = "DaoDaoLiang'PWD_Nami!";
}

bool NAuthProtocol::PackAuthProtocol(QString &param_packet)
{
    // 获取原始信息
    bool ret = getBaseRawInfo();
    if(!ret) return ret;
    // 协议封装
    QJsonObject outerJson;
    QJsonObject productionJson;
    productionJson.insert("version", proVersion);
    productionJson.insert("name", proName);
    QJsonObject pcJson;
    pcJson.insert("mac", pcMAC);
    pcJson.insert("disk_serial", pcSerial);
    pcJson.insert("cpu_version", pcCPUVersion);
    pcJson.insert("cpu_arch", pcCPUArch);
    QJsonObject sysJson;
    sysJson.insert("sys_version", sysVersion);
    sysJson.insert("sys_user", sysUser);
    outerJson.insert("product", productionJson);
    outerJson.insert("computer", pcJson);
    outerJson.insert("system", sysJson);
    QJsonDocument temp_document;
    temp_document.setObject(outerJson);
    QString tempJson = QString(temp_document.toJson(QJsonDocument::Compact));

    // 协议加密
    NEncryptionKit EncryptionInstance;
    EncryptionInstance.setPassword(innerPassword);
    string temp_str;
    ret = EncryptionInstance.getEncryByAES(tempJson, temp_str);
    if(!ret) {
        setLastError("加密失败");
        return ret;
    }
    param_packet = QByteArray::fromStdString(temp_str).toHex();
    param_packet += EncryptionInstance.getMD5Hash(param_packet);
    return true;
}

bool NAuthProtocol::UnPackAuthProtocol(const QString &param_key)
{
    QString decryptQstring;
    NEncryptionKit EncryptionInstance;
    QString tempMD5 = param_key.right(32);
    QString tempRaw = param_key.left(param_key.length() - 32);
    if(EncryptionInstance.getMD5Hash(tempRaw) != tempMD5){
        setLastError("认证文件被非法修改");
        return false;
    }
    // 协议解密
    try{
        EncryptionInstance.setPassword(innerPassword);
        bool ret = EncryptionInstance.decryptByAES(QByteArray::fromHex(tempRaw.toLocal8Bit()).toStdString(), decryptQstring);
        if(!ret){
            setLastError("解密失败");
            return ret;
        }
    } catch (...){
        setLastError("解密失败-发生未知错误");
        return false;
    }

    // 协议解析
    QJsonDocument innerDocument;
    QJsonObject productionJson;
    QJsonParseError tempJsonError;
    innerDocument = QJsonDocument::fromJson(decryptQstring.toLocal8Bit(), &tempJsonError);
    if(tempJsonError.error != QJsonParseError::NoError){
        setLastError(tempJsonError.errorString());
        return false;
    } else {
        if(innerDocument.isObject()){
            productionJson = innerDocument.object();
        } else {
            setLastError("协议解析失败");
            return false;
        }
    }

    QJsonValue product = productionJson.take("product");
    QJsonValue pc = productionJson.take("computer");
    QJsonValue sys = productionJson.take("system");

    if(!product.isObject()){
        setLastError("协议解析失败-product is not object");
        return false;
    }
    if(!pc.isObject()){
        setLastError("协议解析失败-pc is not object");
        return false;
    }
    if(!sys.isObject()){
        setLastError("协议解析失败-sys is not object");
        return false;
    }

    // 获取原始基础信息
    bool ret = getBaseRawInfo();
    if(!ret) return ret;

    // product 匹配
    QString temStr;
    QJsonObject temObj = product.toObject();

    if(temObj.contains("version")){
        temStr = temObj.take("version").toString();
    } else {
        setLastError("auth中product没有version");
        return false;
    }
    if(temStr != proVersion){
        setLastError("本地软件版本和授权版本不一致");
        return false;
    }

    if(temObj.contains("name")){
        temStr = temObj.take("name").toString();
    } else {
        setLastError("auth中product没有name");
        return false;
    }
    if(temStr != proName){
        setLastError("本地软件名字和授权不一致");
        return false;
    }

    // computer 匹配
    temObj = pc.toObject();
    if(temObj.contains("mac")){
        temStr = temObj.take("mac").toString();
    } else {
        setLastError("auth中computer没有mac");
        return false;
    }
    if(temStr != pcMAC){
        setLastError("本地网卡设备和授权不一致");
        return false;
    }
    if(temObj.contains("disk_serial")){
        temStr = temObj.take("disk_serial").toString();
    } else {
        setLastError("auth中computer没有disk_serial");
        return false;
    }
    if(temStr != pcSerial){
        setLastError("本地硬盘序列号和授权不一致");
        return false;
    }
    if(temObj.contains("cpu_version")){
        temStr = temObj.take("cpu_version").toString();
    } else {
        setLastError("auth中computer没有cpu_version");
        return false;
    }
    if(temStr != pcCPUVersion){
        setLastError("本地CPU和授权不一致");
        return false;
    }
    if(temObj.contains("cpu_arch")){
        temStr = temObj.take("cpu_arch").toString();
    } else {
        setLastError("auth中computer没有cpu_arch");
        return false;
    }
    if(temStr != pcCPUArch){
        setLastError("本地CPU和授权不一致");
        return false;
    }

    // sys 匹配
    temObj = sys.toObject();
    if(temObj.contains("sys_version")){
        temStr = temObj.take("sys_version").toString();
    } else {
        setLastError("auth中computer没有sys_version");
        return false;
    }
    if(temStr != sysVersion){
        setLastError("本地系统和授权不一致");
        return false;
    }
    if(temObj.contains("sys_user")){
        temStr = temObj.take("sys_user").toString();
    } else {
        setLastError("auth中computer没有sys_user");
        return false;
    }
    if(temStr != sysUser){
        setLastError("本地系统用户和授权不一致");
        return false;
    }
    return true;
}

bool NAuthProtocol::UnPackLicenseProtocol(const QString &param_key)
{
    QString decryptQstring;
    NEncryptionKit EncryptionInstance;
    QString tempMD5 = param_key.right(32);
    QString tempRaw = param_key.left(param_key.length() - 32);
    if(EncryptionInstance.getMD5Hash(tempRaw) != tempMD5){
        setLastError("授权文件被非法修改");
        return false;
    }

    // 协议解密
    try{
        EncryptionInstance.setPassword(innerPassword);
        bool ret = EncryptionInstance.decryptByAES(QByteArray::fromHex(tempRaw.toLocal8Bit()).toStdString(), decryptQstring);
        if(!ret) {
            setLastError("解密失败");
            return ret;
        }
    } catch (...) {
        setLastError("解密失败-发生未知错误");
        return false;
    }

    // 协议解析
    QJsonDocument innerDocument;
    QJsonObject productionJson;
    QJsonParseError tempJsonError;
    innerDocument = QJsonDocument::fromJson(decryptQstring.toLocal8Bit(), &tempJsonError);
    if(tempJsonError.error != QJsonParseError::NoError){
        setLastError(tempJsonError.errorString());
        return false;
    } else {
        if(innerDocument.isObject()){
            productionJson = innerDocument.object();
        } else {
            setLastError("协议解析失败");
            return false;
        }
    }

    QJsonValue date;
    if(productionJson.contains("date")){
        productionJson.take("date");
    } else {
        setLastError("协议解析失败-没有date");
        return false;
    }

    QJsonValue authority;
    if(productionJson.contains("authority")){
        productionJson.take("authority");
    } else {
        setLastError("协议解析失败-没有authority");
    }

    if(!date.isObject()){
        setLastError("协议解析失败-date is not object");
        return false;
    }

    if(!authority.isObject()){
        setLastError("协议解析失败-authority is not object");
        return false;
    }

    // date 解析
    QJsonObject temObj = date.toObject();

    if(temObj.contains("apply_date")){
        applyTime = temObj.take("apply_date").toString();
    } else {
        setLastError("liscense中没有apply_date");
        return false;
    }

    if(temObj.contains("begin_date")){
        beginTime = temObj.take("begin_date").toString();
    } else {
        setLastError("liscense中没有begin_date");
        return false;
    }

    if(temObj.contains("end_date")){
        beginTime = temObj.take("end_date").toString();
    } else {
        setLastError("liscense中没有end_date");
        return false;
    }

    // authority 解析
    if(!liscenceInstance.unPackLiscense(authority.toString())){
        setLastError(liscenceInstance.getLastError());
        return false;
    }

    return true;
}

QString NAuthProtocol::getLastError() const
{
    return lastError;
}

void NAuthProtocol::setLastError(const QString &value)
{
    lastError = value;
}

bool NAuthProtocol::getBaseRawInfo()
{
    // 数据归零
    applyTime = "";
    beginTime = "";
    endTime = "";
    proVersion = "";
    proName = "";
    pcMAC = "";
    pcSerial = "";
    pcCPUVersion = "";
    pcCPUArch = "";
    sysVersion = "";
    sysUser = "";
    // 读取产品信息
    NConfig NConfigInstance;
    bool ret = NConfigInstance.installAndInit(QCoreApplication::applicationDirPath() + "/app.conf", "daodaoliang", false);
    if(!ret) {
        setLastError("初始化配置文件失败");
        return ret;
    }
    ret = NConfigInstance.getConfigItem("app","version",proVersion);
    if(!ret) {
        setLastError("获取 产品:版本 信息失败");
        return ret;
    }
    ret = NConfigInstance.getConfigItem("app","name",proName);
    if(!ret) {
        setLastError("获取 产品:名字 信息失败");
        return ret;
    }
    NConfigInstance.releaseConf();

    // 读取电脑硬件信息
    NComputerInfo NComputerInstance;
    ret = NComputerInstance.getMAC(pcMAC, false);
    if(!ret) {
        setLastError("获取 PC:MAC 信息失败");
        return ret;
    }
    ret = NComputerInstance.getVolumeSerialNumber(pcSerial);
    if(!ret) {
        setLastError("获取 PC:Serial 信息失败");
        return ret;
    }
    ret = NComputerInstance.getCPUVersion(pcCPUVersion);
    if(!ret) {
        setLastError("获取 PC:CPUV 信息失败");
        return ret;
    }
    ret = NComputerInstance.getCPUArch(pcCPUArch);
    if(!ret) {
        setLastError("获取 PC:CPUA 信息失败");
        return ret;
    }

    // 读取系统信息
    ret = NComputerInstance.getSysVersion(sysVersion);
    if(!ret) {
        setLastError("获取 SYS:Version 信息失败");
        return ret;
    }
    ret = NComputerInstance.getSysUserName(sysUser);
    if(!ret) {
        setLastError("获取 SYS:User 信息失败");
        return ret;
    }
    return true;
}
