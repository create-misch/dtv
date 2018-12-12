#include <QSqlQuery>

#include <model/nodeinterface.h>
#include <model/database.h>
#include <model/nodetree.h>
#include <model/packer.h>

#include <model/hardstoragedb.h>

namespace libsmp {

HardStorageDB::HardStorageDB() :
    db_(new Database) {}

HardStorageDB::~HardStorageDB() {}

void HardStorageDB::saveStorageToFile(const QString &fileName, const DataMap &dataMap,
                                      const NodeTree *nodeTree) {
    if (!db_->connectToDatabase(fileName))
        return;

    auto visitorSave = [dataMap, this] (const NodeInterface &node) {
        auto parent_key = node.parent() == nullptr ? -1 : node.parent()->key();
        auto complete = db_->saveData(node.key(), parent_key, pack(dataMap.at(node.key())));
        Q_UNUSED(complete)
    };
    nodeTree->recursiveVisitor(visitorSave);
}

void HardStorageDB::loadStorageFromFile(const QString &fileName, DataMap &dataMap, NodeTree *nodeTree) {
    Q_UNUSED(fileName)
    Q_UNUSED(dataMap)
    Q_UNUSED(nodeTree)
}

}
