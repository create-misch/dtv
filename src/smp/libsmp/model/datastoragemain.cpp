#include <model/node.h>
#include <model/nodetree.h>

#include <model/observer.h>
#include <model/hardstoragedb.h>
#include <model/cachestorage.h>

#include <model/datastoragemain.h>

namespace libsmp {

DataStorageMain::DataStorageMain(const QString &fileHardStorage) :
    tree_(new NodeTree),
    hardStorage_(new HardStorageDB(fileHardStorage)),
    cache_(new CacheStorage) {    
    hardStorage_->loadStorageFromFile(data_map_, tree_.get());
}

DataStorageMain::~DataStorageMain() {
    hardStorage_->saveStorageToFile(data_map_, tree_.get());
    cache_->clearCacheFiles();
}

void DataStorageMain::addChildObject(const Key &key) {
    auto keyNode = tree_->addChildForKey(key);

    data_map_[keyNode] = Data{};

    auto node = tree_->getNodeWithKey(keyNode);
    if (node != nullptr) {
        updateObject(node);
    }
}

void DataStorageMain::deleteObject(const Key &key) {
    auto node = tree_->deleteNode(key);
    if (node == nullptr) {
        return;
    }

    auto filesInfo = data_map_.at(key).extraData.filesInfo;
    for (auto fileInfo : filesInfo) {
        hardStorage_->deleteDocumentFromStorage(key, fileInfo.fileName);
    }
    data_map_.erase(key);
    requestObject(node->key());
    updateData(data_map_.at(defaultKey).extraData);
}

void DataStorageMain::setNameForObject(const Key &key, const QString &name) {
    if (data_map_.count(key) == 0) {
        return;
    }
    auto &data = data_map_[key];
    data.name = name;
    updateObject(tree_->getNodeWithKey(key));
}

void DataStorageMain::setDescriptionForObject(const Key &key, const QString &description) {
    if (data_map_.count(key) == 0) {
        return;
    }
    auto &data = data_map_[key].extraData;
    data.description = description;
    updateData(data);
}

void DataStorageMain::requestDataForObject(const Key &key) {
    auto it = data_map_.find(key);
    if (it == std::end(data_map_)) {
        return;
    }

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

void DataStorageMain::saveFile(const Key &key, const QString &nameFile, QByteArray &&dataFile) {
    FileInfo fileInfo = {nameFile.section(".", 0, 0), dataFile.size(), nameFile.section(".", -1)};

    if (!hardStorage_->saveDocumentInStorage(key, fileInfo.fileName, std::move(dataFile))) {
        return;
    }
    auto &extraData = data_map_[key].extraData;
    extraData.filesInfo.push_back(std::move(fileInfo));
    updateData(extraData);
}

void DataStorageMain::deleteFile(const Key &key, const QString &nameFile) {
    if (!hardStorage_->deleteDocumentFromStorage(key, nameFile)) {
        return;
    }
    auto &filesInfo = data_map_[key].extraData.filesInfo;
    filesInfo.erase(std::remove_if(std::begin(filesInfo), std::end(filesInfo),
                 [&nameFile](const FileInfo &fileInfo) {
        return fileInfo.fileName == nameFile;
    }), std::end(filesInfo));

    updateData(data_map_.at(key).extraData);
}

void DataStorageMain::openFile(const Key &key, const QString &nameFile) {
    const auto &filesInfo = data_map_.at(key).extraData.filesInfo;
    auto it = std::find_if(std::begin(filesInfo), std::end(filesInfo), [nameFile] (const FileInfo &fileInfo) {
        return fileInfo.fileName == nameFile;
    });

    if (it == std::end(filesInfo)) {
        return;
    }
    const auto &fileInfo = (*it);

    auto nameCacheFile = cache_->createNameCacheFile(fileInfo.fileName, fileInfo.type);
    if (cache_->searchAndOpen(nameCacheFile)) {
        return;
    }

    QByteArray data;
    if (!hardStorage_->unloadDocumentFromStorage(key, nameFile, data)) {
        return;
    }

    if (data.size() != fileInfo.size) {
        return;
    }

    cache_->createAndOpen(nameCacheFile, data);
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

