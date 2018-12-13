#include <model/node.h>
#include <model/nodetree.h>

#include <model/observer.h>
#include <model/hardstoragedb.h>

#include <model/datastoragemain.h>

namespace libsmp {

DataStorageMain::DataStorageMain(const QString &fileHardStorage) :
    tree_(new NodeTree),
    hardStorage_(new HardStorageDB) {
    if (!fileHardStorage.isEmpty()) {
        hardStorage_->loadStorageFromFile(fileHardStorage, data_map_, tree_.get());
    }
}

DataStorageMain::~DataStorageMain() {
    hardStorage_->saveStorageToFile(QString("./%1").arg(data_map_.at(defaultKey).name),
                                    data_map_, tree_.get());
}

void DataStorageMain::addChildObject(const Key &key) {
    auto keyNode = tree_->addChildForKey(key);

    data_map_[keyNode] = Data{};

    auto node = tree_->getNodeWithKey(keyNode);
    if (node != nullptr)
        updateObject(node);
}

void DataStorageMain::setNameForObject(const Key &key, const QString &name) {
    if (data_map_.count(key) == 0)
        return;
    auto &data = data_map_[key];
    data.name = name;
    updateObject(tree_->getNodeWithKey(key));
}

void DataStorageMain::setDescriptionForObject(const Key &key, const QString &description) {
    if (data_map_.count(key) == 0)
        return;
    auto &data = data_map_[key].extraData;
    data.description = description;
    updateData(data);
}

void DataStorageMain::requestDataForObject(const Key &key) {
    auto it = data_map_.find(key);
    if (it == std::end(data_map_)) return;

    updateData((*it).second.extraData);
}

void DataStorageMain::requestObject(const Key &key) {
    if (key == defaultKey) {
        auto visitor = [this](const NodeInterface *node) {
            updateObject(dynamic_cast<const Node *>(node));
        };
        tree_->recursiveVisitor(visitor);
        return;
    }
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;
    updateObject(node);
}

void DataStorageMain::addObserver(Observer *observer) {
    observers_.push_back(observer);
}

void DataStorageMain::updateObject(const Node *node) {
    for (auto & observer : observers_) {
        observer->updateRequestedObject(*node, data_map_.at(node->key()).name);
    }
}

void DataStorageMain::updateData(const ExtraData &data) {
    for (auto &observer : observers_) {
        observer->updateData(data);
    }
}

}

