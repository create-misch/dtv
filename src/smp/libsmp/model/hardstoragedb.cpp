#include <QSqlQuery>

#include <model/database.h>

#include <model/hardstoragedb.h>

namespace libsmp {

HardStorageDB::HardStorageDB() :
    db_(new Database) {}

HardStorageDB::~HardStorageDB() {}

void HardStorageDB::saveStorageToFile(const QString &fileName, const DataMap &dataMap, const NodeTree *nodeTree) {
    db_->connectToDatabase(fileName);

    auto qry = db_->executeQuery("CREATE TABLE smp ("
                 "int , int)");
}

void HardStorageDB::loadStorageFromFile(const QString &fileName, DataMap &dataMap, NodeTree *nodeTree) {
    Q_UNUSED(fileName)
    Q_UNUSED(dataMap)
    Q_UNUSED(nodeTree)
}

}
