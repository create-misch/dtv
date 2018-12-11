#pragma once

#include <QSqlQuery>

class QString;

namespace libsmp {

class Database {
public:
    Database();

    void connectToDatabase(const QString &name);

    QSqlQuery executeQuery(const QString &query);
};

}
