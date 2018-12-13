#include <QString>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <iostream>

#include <QVariant>

#include <model/database.h>

namespace  {
constexpr auto nameTable= "smp";
constexpr auto version_storage = "0.1";
}

namespace libsmp {

Database::Database() {}

bool Database::connectToDatabase(const QString &name) {    
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        std::cout << "Not found SQLITE Driver!" << std::endl;
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(name);

     if (!db.open()) {
         std::cout <<  db.lastError().text().toStdString() << std::endl;
         return false;
     }

     return createTable();
}

bool Database::saveData(const Key &key, const Key &parentKey, const QByteArray &data) {
    auto saveQuery = prepare("INSERT OR REPLACE INTO smp (key, parent_key, data, version)"
                             " VALUES ((:key), (:parent_key), (:data), (:version))");
    saveQuery.bindValue(":key", key);
    saveQuery.bindValue(":parent_key", parentKey);
    saveQuery.bindValue(":data", data);
    saveQuery.bindValue(":version", version_storage);
    auto res = saveQuery.exec();

    if (!res)
        std::cout << "Error save table " << saveQuery.lastError().text().toStdString() << std::endl;
    return res;
}

QList<QVariantList> Database::loadData() {
    auto result = QList<QVariantList>();
    auto loadQuery = prepare("SELECT * FROM smp");
    if (!loadQuery.exec())
        return result;

    while(loadQuery.next()) {
        auto list =  QVariantList();
        list.append(loadQuery.value(0));
        list.append(loadQuery.value(1));
        list.append(loadQuery.value(2));
        result.push_back(list);
    }

    return result;
}

bool Database::saveDataFile(const Key &key, QByteArray &&data) {
    auto saveQuery = prepare("INSERT OR REPLACE INTO smp (key, file_data)"
                             " VALUES ((:key), (:data))");
    saveQuery.bindValue(":key", key);
    saveQuery.bindValue(":data", data);
    auto res = saveQuery.exec();

    if (!res)
        std::cout << "Error save file " << saveQuery.lastError().text().toStdString() << std::endl;
    return res;
}

QSqlQuery Database::executeQueryString(const QString &queryString) {
    auto qry = query();

    qry.exec(queryString);
    return qry;
}

QSqlQuery Database::executeQuery(QSqlQuery &query) {
    query.exec();
    return query;
}

QSqlQuery Database::query() {
    return QSqlQuery(QString(), QSqlDatabase::database());
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
    auto createString = QString("CREATE TABLE IF NOT EXISTS %1 ("
                                  "key INTEGER PRIMARY KEY NOT NULL ,"
                                  "parent_key INTEGER NOT NULL,"
                                  "data BLOB,"
                                  "file_data BLOB,"
                                  "version TEXT)").arg(nameTable);
    auto createTable = prepare(createString);

    auto res = createTable.exec();
    if (!res)
        std::cout << "Error create table " << createTable.lastError().text().toStdString() << std::endl;
    return res;
}

}
