#include <QString>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <iostream>

#include <QVariant>

#include <model/database.h>



namespace  {
constexpr auto nameTable= "smp";
}

namespace libsmp {

Database::Database() {}

bool Database::connectToDatabase(const QString &name) {
    std::cout <<  "Drivers DB " <<  std::endl;
    for (const auto &str : QSqlDatabase::drivers())
        std::cout <<  str.toStdString() <<  std::endl;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(name);

     if (!db.open()) {
         std::cout <<  db.lastError().text().toStdString() << std::endl;
         return false;
     }

     return createTable();
}

bool Database::saveData(const Key &key, const Key &parentKey, const QByteArray &data) {
    auto saveQuery = prepare("INSERT INTO (:table) (key, parent_key, data)"
                             " VALUES ((:key), (:parent_key), (:data))");
    saveQuery.bindValue(":table", nameTable);
    saveQuery.bindValue(":key", key);
    saveQuery.bindValue(":parent_key", parentKey);
    saveQuery.bindValue(":data", data);
    saveQuery.exec();

    std::cout << "Error save table " << saveQuery.lastError().text().toStdString() << std::endl;
    return false;
}

QSqlQuery executeQueryString(const QString &query) {
    QSqlQuery qry(QSqlDatabase::database());

    qry.exec(query);
    return qry;
}

QSqlQuery Database::executeQuery(QSqlQuery &query) {
    query.exec();
    return query;
}

QSqlQuery Database::query() {
    return QSqlQuery(QSqlDatabase::database());
}

bool Database::prepare(QSqlQuery &query, const QString &str) {
    return query.prepare(str);
}

QSqlQuery Database::prepare(const QString &str) {
    auto q = query();
    prepare(q, str);
    return q;
}

bool Database::createTable() {
    auto checkTable = prepare("SELECT 1 FROM :table");
    checkTable.bindValue(":table", nameTable);
    auto result = checkTable.exec();

    if (result) return result;

    auto createTable = prepare("CREATE TABLE IF NOT EXISTS ? ("
                              "key INTEGER PRIMARY KEY NOT NULL ,"
                              "parent_key INTEGER NOT NULL,"
                              "data BLOB)");
    createTable.bindValue(0, nameTable);

    auto res = createTable.exec();
    if (!res)
        std::cout << "Error create table " << createTable.lastError().text().toStdString() << std::endl;
    return res;
}

}
