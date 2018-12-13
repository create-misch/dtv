#pragma once

#include <QSqlQuery>
#include <QVariantList>

#include <global.h>

class QString;

namespace libsmp {

class Database {
public:
    Database();

    bool connectToDatabase(const QString &name);

    bool saveData(const Key &key, const Key &parentKey, const QByteArray &data);
    QList<QVariantList> loadData();

    bool saveDataFile(const Key &key, QByteArray &&data);

private:
    QSqlQuery executeQueryString(const QString &queryString);
    QSqlQuery executeQuery(QSqlQuery &query);

    QSqlQuery query();
    bool prepare(QSqlQuery &query, const QString &str);
    QSqlQuery prepare(const QString &str);

    bool createTable();
};

}
