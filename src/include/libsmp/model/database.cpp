#include <QString>
#include <QSqlError>
#include <QSqlDatabase>

#include "database.h"

#include <iostream>

namespace libsmp {

Database::Database() {}

void Database::connectToDatabase(const QString &name) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);

     if (!db.open())
         std::cout <<  db.lastError().text().toStdString();
}

QSqlQuery Database::executeQuery(const QString &query) {
    QSqlQuery qry(QSqlDatabase::database());

    qry.exec(query);
    return qry;
}

}
