#include <QString>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <iostream>

#include <QVariant>

#include <log4app/log4app.h>

#include <model/database.h>

namespace  {
constexpr auto nameTableSmp= "smp";
constexpr auto nameTableSmpFiles= "smp_files";
constexpr auto version_storage = "0.1";
}

quint64 toHash(const QString &fileName) {
    std::hash<std::string> hash_fn;
    return static_cast<quint64>(hash_fn(fileName.toStdString()));
}

namespace libsmp {

Database::Database() {}

bool Database::connectToDatabase(const QString &name) {    
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        log4app::Log()->error("Not found SQLITE Driver!");
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", name.toLatin1());

    db.setDatabaseName(name);

     if (!db.open()) {
         log4app::Log()->error("Data base error : %1", db.lastError().text());
         return false;
     }
     db_ = db;

     return createTables();
}

bool Database::saveData(const Key &key, const Key &parentKey, const QByteArray &data) {
    auto saveQuery = prepare("INSERT OR REPLACE INTO smp (key, parent_key, data, version)"
                             " VALUES ((:key), (:parent_key), (:data), (:version))");
    saveQuery.bindValue(":key", key);
    saveQuery.bindValue(":parent_key", parentKey);
    saveQuery.bindValue(":data", data);
    saveQuery.bindValue(":version", version_storage);
    auto res = saveQuery.exec();

    if (!res) {
        log4app::Log()->error("Data base error(save table) : %1",
                              saveQuery.lastError().text());
    }
    return res;
}

QList<QVariantList> Database::loadData() {
    auto result = QList<QVariantList>();
    auto loadQuery = prepare("SELECT * FROM smp");
    if (!loadQuery.exec()) {
        log4app::Log()->error("Data base error(load data) : %1",loadQuery.lastError().text());
        return result;
    }

    while(loadQuery.next()) {
        auto list =  QVariantList();
        list.append(loadQuery.value(0));
        list.append(loadQuery.value(1));
        list.append(loadQuery.value(2));
        result.push_back(list);
    }

    return result;
}

bool Database::clearData() {
    auto deleteQuery = prepare("DELETE FROM smp");
    auto res =  deleteQuery.exec();

    if (!res) {
        log4app::Log()->error("Data base error(clear table) : %1",
                              deleteQuery.lastError().text());
    }

    return res;
}

bool Database::saveDataFile(const Key &key, const QString &nameFile, QByteArray &&data) {
    auto saveQuery = prepare("INSERT OR REPLACE INTO smp_files (key, name, file_data, version)"
                             " VALUES ((:key), (:name), (:file_data), (:version))");
    saveQuery.bindValue(":key", key);    
    saveQuery.bindValue(":name", toHash(nameFile));
    saveQuery.bindValue(":file_data", data);
    saveQuery.bindValue(":version", version_storage);
    auto res = saveQuery.exec();

    if (!res) {
        log4app::Log()->error("Data base error(save file %1) : %2", nameFile,
                              saveQuery.lastError().text());
    }
    return res;
}

bool Database::deleteDataFile(const Key &key, const QString &nameFile) {
    auto deleteQuery = prepare("DELETE FROM smp_files "
                             " WHERE key=:key AND name=:name");
    deleteQuery.bindValue(":key", key);    
    deleteQuery.bindValue(":name", toHash(nameFile));

    auto res = deleteQuery.exec();

    if (!res) {
        log4app::Log()->error("Data base error(delete file %1) : %2 ", nameFile,
                              deleteQuery.lastError().text());
    }
    return res;
}

bool Database::unloadDataFile(const Key &key, const QString &nameFile, QByteArray &data) {
    auto unloadQuery = prepare("SELECT key, name, file_data FROM smp_files"
                             " WHERE key = :key AND name = :name");
    unloadQuery.bindValue(":key", key);
    unloadQuery.bindValue(":name", toHash(nameFile));

    auto res = unloadQuery.exec();

    if (!res) {
        log4app::Log()->error("Data base error (unload file %1) : %2", nameFile,
                  unloadQuery.lastError().text());
    }

    res |= unloadQuery.first();

    data = unloadQuery.value(2).toByteArray();
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
    return QSqlQuery(QString(), db_);
}

bool Database::prepare(QSqlQuery &query, const QString &str) {
    return query.prepare(str);
}

QSqlQuery Database::prepare(const QString &str) {
    auto q = query();
    prepare(q, str);

    return q;
}

bool Database::createTables() {
    auto createString = QString("CREATE TABLE IF NOT EXISTS %1 ("
                                  "key INTEGER PRIMARY KEY NOT NULL ,"
                                  "parent_key INTEGER NOT NULL,"
                                  "data BLOB,"                                  
                                  "version TEXT)").arg(nameTableSmp);
    auto createTable = prepare(createString);

    auto res = createTable.exec();
    if (!res) {
        log4app::Log()->error("Data base error (create table %1) : %2", nameTableSmp,
                  createTable.lastError().text());
    }

    createString = QString("CREATE TABLE IF NOT EXISTS %1 ("
                           "id INTEGER PRIMARY KEY NOT NULL ,"
                           "key INTEGER NOT NULL,"
                           "name INTEGER,"
                           "file_data BLOB,"
                           "version TEXT)").arg(nameTableSmpFiles);

    createTable = prepare(createString);
    auto resFiles = createTable.exec();

    if (!resFiles) {
        log4app::Log()->error("Data base error (create table %1) : %2", nameTableSmp,
                  createTable.lastError().text());
    }

    return res && resFiles;
}

}
