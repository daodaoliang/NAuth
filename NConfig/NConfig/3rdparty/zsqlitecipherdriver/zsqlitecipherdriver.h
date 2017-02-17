/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSql module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef ZSQLITECIPHERDRIVER_H
#define ZSQLITECIPHERDRIVER_H

#include <QtSql/QSqlDriver>
#include <QtSql/QSqlResult>
#include "zsqliteciphercachedresult.h"

struct sqlite3;

class ZSQLiteCipherDriverPrivate;
class ZSQLiteCipherResultPrivate;
class ZSQLiteCipherDriver;

class ZSQLiteCipherResult : public ZSqliteCipherCachedResult
{
    friend class ZSQLiteCipherDriver;
    friend class ZSQLiteCipherResultPrivate;
public:
    explicit ZSQLiteCipherResult(const ZSQLiteCipherDriver* db);
    ~ZSQLiteCipherResult();
    QVariant handle() const;

protected:
    bool gotoNext(ZSqliteCipherCachedResult::ValueCache& row, int idx);
    bool reset(const QString &query);
    bool prepare(const QString &query);
    bool exec();
    int size();
    int numRowsAffected();
    QVariant lastInsertId() const;
    QSqlRecord record() const;
#if (QT_VERSION >= 0x050000)
    void detachFromResultSet();
#endif
    void virtual_hook(int id, void *data);

private:
    ZSQLiteCipherResultPrivate* d;
};

class ZSQLiteCipherDriver : public QSqlDriver
{
    Q_OBJECT
    friend class ZSQLiteCipherResult;
public:
    explicit ZSQLiteCipherDriver(QObject *parent = 0);
    explicit ZSQLiteCipherDriver(sqlite3 *connection, QObject *parent = 0);
    ~ZSQLiteCipherDriver();
    bool hasFeature(DriverFeature f) const;
    bool open(const QString & db,
                   const QString & user,
                   const QString & password,
                   const QString & host,
                   int port,
                   const QString & connOpts);
    void close();
    QSqlResult *createResult() const;
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();
    QStringList tables(QSql::TableType) const;

    QSqlRecord record(const QString& tablename) const;
    QSqlIndex primaryIndex(const QString &table) const;
    QVariant handle() const;
    QString escapeIdentifier(const QString &identifier, IdentifierType) const;

private:
    ZSQLiteCipherDriverPrivate* d;
};

#endif // QSQL_SQLITE_H
