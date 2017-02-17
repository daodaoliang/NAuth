#include "nauth.h"
#include <QDebug>
#include <QFile>
#include <QDataStream>

NAuth::NAuth(QObject *parent)
    :QObject(parent)
{
}

bool NAuth::exportKeyFile(const QString &paramPath)
{
    QString defaultKeyName = "pc.key";
    QString testPackProtocol;
    bool ret = protocolInstance.PackAuthProtocol(testPackProtocol);
    if(!ret){
        setLastError(protocolInstance.getLastError());
        return false;
    }
    QFile innerFile(paramPath + defaultKeyName);
    try {
        if(innerFile.open(QFile::WriteOnly)){
            QDataStream out(&innerFile);
            out.setVersion(QDataStream::Qt_5_7);
            out << testPackProtocol.toLocal8Bit();
            innerFile.flush();
        }
    } catch (...) {
        setLastError("pc.key打开失败");
        return false;
    }
    innerFile.close();
    return true;
}

bool NAuth::importKeyFile(const QString &paramPath)
{
    QString defaultKeyName = "pc.key";
    QByteArray pcKeyRaw;
    QFile innerFile(paramPath + defaultKeyName);
    try {
        if(innerFile.open(QFile::ReadOnly)){
            QDataStream in(&innerFile);
            in.setVersion(QDataStream::Qt_5_7);
            in >> pcKeyRaw;
        }
    } catch (...) {
        setLastError("pc.key读取失败");
    }
    innerFile.close();
    bool ret = protocolInstance.UnPackAuthProtocol(pcKeyRaw);
    if(!ret){
        setLastError(protocolInstance.getLastError());
        return false;
    }
    return true;
}

bool NAuth::authWorkFlow()
{
    // 查找本地授权文件
    QString localLicense = QCoreApplication::applicationDirPath() + "/licence.lock";
    if(!QFile::exists(localLicense)){
        setLastError("未找到版权文件,请申请正版授权!");
        return false;
    }

    // 解析本地授权文件
}

QString NAuth::getLastError() const
{
    return lastError;
}

void NAuth::setLastError(const QString &value)
{
    lastError = value;
}
