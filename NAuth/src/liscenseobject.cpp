#include "liscenseobject.h"

LiscenseObject::LiscenseObject(QObject *parent) : QObject(parent)
{

}

bool LiscenseObject::unPackLiscense(const QString &param_key)
{
    Q_UNUSED(param_key);
    // TODO 解析
    return true;
}

QString LiscenseObject::getLiscenseRaw() const
{
    return liscenseRaw;
}

void LiscenseObject::setLiscenseRaw(const QString &value)
{
    liscenseRaw = value;
}

QString LiscenseObject::getLastError() const
{
    return lastError;
}

void LiscenseObject::setLastError(const QString &value)
{
    lastError = value;
}
