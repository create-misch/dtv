#include <QSqlQuery>

#include <log4app.h>

#include <model/nodeinterface.h>
#include <model/database.h>
#include <model/nodetree.h>
#include <model/packer.h>
#include <model/data.h>

#include <model/hardstoragedb.h>

namespace libsmp {

HardStorageDB::HardStorageDB(const QString &dbName) :
    db_(new Database) {
    QString fileDb;
    fileDb = dbName.endsWith(".smp") ? dbName : QString("%1.smp").arg(dbName);

    if (!db_->connectToDatabase(fileDb)) {
        log4app::Log()->error("Data base %1 don't open!!", fileDb);
    }
}

HardStorageDB::~HardStorageDB() {}

void HardStorageDB::saveStorageToFile(const std::unordered_map<Key, Data> &dataMap,
                                      const NodeTree *nodeTree) {
    db_->clearData();
    auto visitorSave = [dataMap, this] (const NodeInterface *node) {
        auto parent_key = node->parent() == nullptr ? -1 : node->parent()->key();
        db_->saveData(node->key(), parent_key, pack(dataMap.at(node->key())));
    };
    nodeTree->recursiveVisitor(visitorSave);
}

void HardStorageDB::loadStorageFromFile(std::unordered_map<Key, Data> &dataMap, NodeTree *nodeTree) {
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

bool HardStorageDB::saveDocumentInStorage(const Key &key, const QString &nameFile, QByteArray &&data) {
    return db_->saveDataFile(key, nameFile, qCompress(data));
}

bool HardStorageDB::deleteDocumentFromStorage(const Key &key, const QString &nameFIle) {
    return db_->deleteDataFile(key, nameFIle);
}

bool HardStorageDB::unloadDocumentFromStorage(const Key &key, const QString &nameFile, QByteArray &data) {
    QByteArray compressData;
    auto res = db_->unloadDataFile(key, nameFile, compressData);
    data = qUncompress(compressData);

    return res;
}

}
