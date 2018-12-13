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
        db_->saveData(node.key(), parent_key, pack(dataMap.at(node.key())));
    };
    nodeTree->recursiveVisitor(visitorSave);
}

void HardStorageDB::loadStorageFromFile(const QString &fileName, DataMap &dataMap, NodeTree *nodeTree) {
    if (!db_->connectToDatabase(fileName))
        return;

    auto data = db_->loadData();

    auto loadData = [&dataMap, nodeTree] (QVariantList && list) {
        Data data;
        unpack(list.at(2).toByteArray(), data);
        auto key = qvariant_cast<Key>(list.at(0));
        auto keyParent = qvariant_cast<Key>(list.at(1));
        dataMap[key] = std::move(data);

        nodeTree->insertNode(key, keyParent);
    };

    for (auto &&list : data) {
        loadData(std::move(list));
    }
}

}
