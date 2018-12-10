#include <model/node.h>
#include <model/nodetree.h>

#include <model/observer.h>

#include <model/datastoragemain.h>

namespace libsmp {


DataStorageMain::DataStorageMain() :
    tree_(new NodeTree) {}

DataStorageMain::~DataStorageMain() {}

void DataStorageMain::addChildObject(const Key &key) {
    auto keyNode = tree_->addChildForKey(key);

    data_map_[keyNode] = Data{};

    auto node = tree_->getNodeWithKey(key);
    if (node != nullptr)
        updateObject(node);
}

void DataStorageMain::setNameForObject(const Key &key, const QString &name) {
    if (data_map_.count(key) > 0)
        data_map_[key].name = name;

    updateObject(tree_->getNodeWithKey(key));
}

void DataStorageMain::setDescriptionForObject(const Key &key, const QString &description) {
    if (data_map_.count(key) > 0)
        data_map_[key].description = description;
    updateDescription(description);
}

void DataStorageMain::requestDescriptionForObject(const Key &key) {
    auto it = data_map_.find(key);
    if (it == std::end(data_map_)) return;

    updateDescription((*it).second.description);
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
        observer->updateRequestedObject(node);
    }
}

void DataStorageMain::updateDescription(const QString &description) {
    for (auto &observer : observers_) {
        observer->updateDescription(description);
    }
}

}

