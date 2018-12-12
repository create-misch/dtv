#include <model/node.h>
#include <model/nodetree.h>

#include <model/observer.h>
#include <model/hardstoragedb.h>

#include <model/datastoragemain.h>

namespace libsmp {

DataStorageMain::DataStorageMain() :
    tree_(new NodeTree),
    hardStorage_(new HardStorageDB) {}

DataStorageMain::~DataStorageMain() {
    hardStorage_->saveStorageToFile("./database", data_map_, tree_.get());
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
    updateData(data);
}

void DataStorageMain::setDescriptionForObject(const Key &key, const QString &description) {
    if (data_map_.count(key) == 0)
        return;
    auto &data = data_map_[key];
    data.description = description;
    updateData(data);
}

void DataStorageMain::requestDataForObject(const Key &key) {
    auto it = data_map_.find(key);
    if (it == std::end(data_map_)) return;

    updateData((*it).second);
}

void DataStorageMain::requestObject(const Key &key) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;
    updateObject(node);
}

void DataStorageMain::addObserver(Observer *observer) {
    observers_.push_back(observer);
}

void DataStorageMain::updateObject(const Node *node) {
    for (auto & observer : observers_) {
        observer->updateRequestedObject(*node);
    }
}

void DataStorageMain::updateData(const Data &data) {
    for (auto &observer : observers_) {
        observer->updateData(data);
    }
}

}

