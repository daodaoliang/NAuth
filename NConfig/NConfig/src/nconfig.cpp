#include "nconfig.h"
NConfig_p::NConfig_p(QObject *parent):QObject(parent)
{
    innerDriver = NULL;
}

NConfig_p::~NConfig_p()
{
    if(innerDB.isOpen() && innerDB.isValid()){
        innerDB.close();
    }
    if(innerDriver != NULL) {
        innerDriver->deleteLater();
    }
    innerDriver = NULL;
    QString name;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
}

bool NConfig_p::isDbDecrypted(QSqlDatabase &db)
{
    QSqlQuery query(db);
    return query.exec("select name,sql from sqlite_master"
                      " where type = 'table'");
}

bool NConfig_p::changePassword(QSqlDatabase &db, const QString &newPassword)
{
    QSqlQuery query(db);
    return query.exec(QString("PRAGMA rekey='%1';").arg(newPassword));
}

QSqlDatabase *NConfig_p::getInnerDB()
{
    return &innerDB;
}

bool NConfig_p::initConfigDB(const QString &paramDBName, const QString &paramPWD)
{
    bool flag = false;
    if(!innerDriver){
        innerDriver = new ZSQLiteCipherDriver();
    }
    innerDB = QSqlDatabase::addDatabase(innerDriver);
    switch (openDB(innerDB, paramDBName, paramPWD)) {
    case -2:
    case -1:
    case 0:
        flag = false;
        break;
    case 1:
    case 2:
        flag = true;
        break;
    }
    return flag;
}

void NConfig_p::release()
{
    if(innerDB.isOpen() && innerDB.isValid()){
        innerDB.close();
    }
    if(innerDriver != NULL) {
        innerDriver->deleteLater();
    }
    innerDriver = NULL;
    QString name;
    {
        name = QSqlDatabase::database().connectionName();
    }
    QSqlDatabase::removeDatabase(name);
}

int NConfig_p::openDB(QSqlDatabase &db, const QString &dbName, const QString &password)
{
    QFile file(dbName);
    bool isDbFileExists = file.exists() && (file.size() > 0);
    db.setDatabaseName(dbName);
    db.setPassword(password);
    if (!db.open()) return isDbFileExists ? -2 : -1;
    if (isDbFileExists && !isDbDecrypted(db))
    {
        db.close();
        return 0;
    }
    return isDbFileExists ? 2 : 1;
}

NConfig::NConfig()
{
    setIsDebug(true);
}

NConfig::~NConfig()
{

}

bool NConfig::installAndInit(const QString &paramDB, const QString &paramPWD, bool paramCheckExist)
{
    if(paramCheckExist){
        QDir tempPath(paramDB);
        if(!QFile::exists(tempPath.absolutePath())){
            if(isDebug) qDebug() << "文件不存在:" << tempPath.absolutePath();
            return false;
        }
    }
    setConfigFilePath(paramDB);
    return innerOperator.initConfigDB(paramDB, paramPWD);
}

void NConfig::releaseConf()
{
    innerOperator.release();
}

bool NConfig::addConfigItem(const QString &paramTableItem, const QString &paramTableKey, const QString &paramTableValue)
{
    // 语句准备
    QString tableIsExistSql = QString("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%1';").arg(paramTableItem);
    QString tableCreateSql = QString("create table `%1` (`key` varchar primary key,`value` varchar)").arg(paramTableItem);
    QString configInsertSql = QString("replace into `%1` (`key`,`value`) values ('%2','%3');").arg(paramTableItem, paramTableKey, paramTableValue);
    // 存在性保证
    QSqlQuery existQuery = innerOperator.getInnerDB()->exec(tableIsExistSql);
    if(existQuery.lastError().type() != QSqlError::NoError){
        if(isDebug) qDebug()<< "addConfigItem error:" << existQuery.lastError().text();
        existQuery.clear();
        return false;
    }
    existQuery.next();
    bool isExist = existQuery.value(0).toString() == "0" ? false : true;
    if(!isExist){
        if(isDebug) qDebug()<<QString("配置表并不存在,现在进行创建中……");
        QSqlQuery createQuery = innerOperator.getInnerDB()->exec(tableCreateSql);
        if(createQuery.lastError().type() != QSqlError::NoError){
            if(isDebug) qDebug()<< createQuery.lastError().text();
            createQuery.clear();
            return false;
        }
        createQuery.clear();
        if(isDebug) qDebug()<<QString("配置表并不存在,创建完毕!");
    }
    existQuery.clear();
    // 配置项入库
    QSqlQuery insertQuery = innerOperator.getInnerDB()->exec(configInsertSql);
    if(insertQuery.lastError().type() != QSqlError::NoError){
        if(isDebug) qDebug()<< insertQuery.lastError().text();
        insertQuery.clear();
        return false;
    }
    insertQuery.clear();
    if(isDebug) qDebug()<<QString("配置项-%1已经入库 key-%2 value-%3").arg(paramTableItem, paramTableKey, paramTableValue);
    return true;
}

bool NConfig::getConfigItem(const QString &paramTableItem, const QString &paramTableKey, QString &paramTableValue)
{
    // 语句准备
    QString tableIsExistSql = QString("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='%1';").arg(paramTableItem);
    QString configSelectSql = QString("SELECT `value` from %1 where `key` = '%2'").arg(paramTableItem, paramTableKey);
    // 存在性判断
    QSqlQuery existQuery = innerOperator.getInnerDB()->exec(tableIsExistSql);
    if(existQuery.lastError().type() != QSqlError::NoError){
        if(isDebug) qDebug()<< "getConfigItem error:" << existQuery.lastError().text();
        existQuery.clear();
        return false;
    }
    existQuery.clear();
    // 获取配置项
    QSqlQuery selectQuery = innerOperator.getInnerDB()->exec(configSelectSql);
    if(selectQuery.lastError().type() != QSqlError::NoError){
        if(isDebug) qDebug()<< "getConfigItem error:" << selectQuery.lastError().text();
        selectQuery.clear();
        return false;
    }
    if(!selectQuery.next()){
        if(isDebug) qDebug()<< "getConfigItem error:" << "no data!";
        selectQuery.clear();
        return false;
    }
    paramTableValue = QString("%1").arg(selectQuery.value("value").toString());
    selectQuery.clear();
    return true;
}

bool NConfig::clearConfig()
{
    // 语句准备
    QString tableListSql = QString("select * from sqlite_master where type = 'table';");
    // 清空操作
    QSqlQuery tableQuery = innerOperator.getInnerDB()->exec(tableListSql);
    if(tableQuery.lastError().type() != QSqlError::NoError){
        if(isDebug) qDebug() << "clearConfig error:" << tableQuery.lastError().text();
        tableQuery.clear();
        return false;
    }
    QStringList tableNameList;
    while (tableQuery.next()){
        tableNameList.append(tableQuery.value(1).toString());
    }
    tableQuery.clear();
    foreach (QString tableName, tableNameList) {
        if(isDebug) qDebug()<<QString("马上清理配置:%1").arg(tableName);
        QString dropTable = QString("drop table if exists %1").arg(tableName);
        QSqlQuery dropQuery = innerOperator.getInnerDB()->exec(dropTable);
        if(dropQuery.lastError().type() != QSqlError::NoError){
            if(isDebug) qDebug() << QString("清理配置:%1 失败").arg(tableName) << dropQuery.lastError().text();
        }
    }
    return true;
}

bool NConfig::exportConfigToFile()
{
    // 语句准备
    QString tableListSql = QString("select * from sqlite_master where type = 'table';");
    // 文件准备
    QString tempFileName = QString("%1%2.ini").arg(configFilePath, configFileName);
    if(QFile::exists(tempFileName)){
        QFile::remove(tempFileName);
    } else {
        QFile temp(tempFileName);
        temp.open(QIODevice::ReadWrite);
        temp.close();
    }
    QSettings tempFile(tempFileName,QSettings::IniFormat);
    // 文件操作
    QSqlQuery tableQuery = innerOperator.getInnerDB()->exec(tableListSql);
    if(tableQuery.lastError().type() != QSqlError::NoError){
        if(isDebug) qDebug() << "exportConfigToFile error:" << tableQuery.lastError().text();
        tableQuery.clear();
        return false;
    }
    QStringList tempNameList;
    while (tableQuery.next()){
        tempNameList.append(tableQuery.value(1).toString());
    }
    tableQuery.clear();
    foreach (QString tempName, tempNameList) {
        QString selectSql = QString("select * from `%1`").arg(tempName);
        QSqlQuery selectQuery = innerOperator.getInnerDB()->exec(selectSql);
        if(selectQuery.lastError().type() != QSqlError::NoError){
            if(isDebug) qDebug() << QString("导出配置:%1 失败").arg(tempName) << selectQuery.lastError().text();
        } else {
            if(isDebug) qDebug() << QString("导出配置:%1 开始").arg(tempName);
        }
        tempFile.beginGroup(tempName);
        while (selectQuery.next()) {
            QString tempKey = selectQuery.value("key").toString();
            QString tempValue = selectQuery.value("value").toString();
            if(isDebug) qDebug() << QString(" %1 : %2 ").arg(tempKey, tempValue);
            tempFile.setValue(tempKey, tempValue);
        }
        tempFile.endGroup();
        if(isDebug) qDebug() << QString("导出配置:%1 完毕").arg(tempName);
    }
    return true;
}

bool NConfig::importConfigFromFile(const QString paramIniFile)
{
    // 存在性判断
    QDir tempInnerFile(paramIniFile);
    QString tempInnerFilePath = tempInnerFile.absolutePath();
    if(!QFile::exists(tempInnerFilePath)){
        if(isDebug) qDebug() << QString("导入失败-文件:%1 不存在").arg(tempInnerFilePath);
        return false;
    }
    // 格式判断
    if(tempInnerFilePath.split(".").last() != "ini"){
        if(isDebug) qDebug() <<QString("文件格式错误");
        return false;
    }
    // 文件准备
    QStringList tempList = tempInnerFilePath.split(".");
    QString tempPath = tempList.first() + ".conf";
    // 调试信息
    if(isDebug) qDebug() << "即将把内容导入到:" << tempPath;
    // 内容导入
    QSettings tempInnerSettings(paramIniFile, QSettings::IniFormat);
    QStringList groupList = tempInnerSettings.childGroups();
    foreach (QString item, groupList) {
        tempInnerSettings.beginGroup(item);
        foreach(QString innerItem ,tempInnerSettings.allKeys()) {
            bool ret = addConfigItem(item, innerItem, tempInnerSettings.value(innerItem).toString());
            if(isDebug && !ret) qDebug() << QString("table:%1 key:%2 value:%3 导入失败").arg(item, innerItem, tempInnerSettings.value(innerItem).toString());
        }
        tempInnerSettings.endGroup();
    }
    // 调试信息
    if(isDebug) qDebug() << "已经完成把内容导入到:" << tempPath;
    return true;
}

bool NConfig::getIsDebug() const
{
    return isDebug;
}

void NConfig::setIsDebug(bool value)
{
    isDebug = value;
}

QString NConfig::getConfigFilePath() const
{
    return configFilePath;
}

void NConfig::setConfigFilePath(const QString &value)
{
    QString tempStr = QString("%1").arg(value);
    QStringList tempList = tempStr.split('/');
    QDir temp(value);
    if(tempList.length() <= 1){
        configFilePath = QDir("./").absolutePath();
        configFileName = QString("%1").arg(value);
    } else {
        QString tempPath = temp.absolutePath();
        configFilePath = tempPath.left(tempPath.length() - tempList.last().length());
        configFileName = tempList.last().split('.').first();
    }
    if(isDebug){
        qDebug() << "configFilePath:" << configFilePath;
        qDebug() << "configFileName:" << configFileName;
    }
}
