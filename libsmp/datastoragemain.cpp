#include <log4app.h>

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
    log4app::Log()->trace(Q_FUNC_INFO);
    auto keyNode = tree_->addChildForKey(key);

    data_map_[keyNode] = Data{};

    auto node = tree_->getNodeWithKey(keyNode);
    if (node != nullptr) {
        updateObject(node);
    }
}

void DataStorageMain::deleteObject(const Key &key) {
    log4app::Log()->trace(Q_FUNC_INFO);
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
    log4app::Log()->trace(Q_FUNC_INFO);
    if (data_map_.count(key) == 0) {
        log4app::Log()->error("Data storage(set name). Don't found element with key %1", key);
        return;
    }
    auto &data = data_map_[key];
    data.name = name;
    updateObject(tree_->getNodeWithKey(key));
}

void DataStorageMain::setDescriptionForObject(const Key &key, const QString &description) {
    log4app::Log()->trace(Q_FUNC_INFO);
    if (data_map_.count(key) == 0) {
        log4app::Log()->error("Data storage(set description). Don't found element with key %1", key);
        return;
    }
    auto &data = data_map_[key].extraData;
    data.description = description;
    updateData(data);
}

void DataStorageMain::requestDataForObject(const Key &key) {
    log4app::Log()->trace(Q_FUNC_INFO);
    auto it = data_map_.find(key);
    if (it == std::end(data_map_)) {
        log4app::Log()->error("Data storage(request object). Don't found element with key %1", key);
        return;
    }

    updateData((*it).second.extraData);
}

void DataStorageMain::requestObject(const Key &key) {
    log4app::Log()->trace(Q_FUNC_INFO);
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
    log4app::Log()->trace(Q_FUNC_INFO);
    FileInfo fileInfo = {nameFile.section(".", 0, 0), dataFile.size(), nameFile.section(".", -1)};

    if (!hardStorage_->saveDocumentInStorage(key, fileInfo.fileName, std::move(dataFile))) {
        log4app::Log()->error("Data storage(save file). Error save documet in storage!");
        return;
    }
    auto &extraData = data_map_[key].extraData;
    extraData.filesInfo.push_back(std::move(fileInfo));
    updateData(extraData);
}

void DataStorageMain::deleteFile(const Key &key, const QString &nameFile) {
    log4app::Log()->trace(Q_FUNC_INFO);
    if (!hardStorage_->deleteDocumentFromStorage(key, nameFile)) {
        log4app::Log()->error("Data storage(delete file). Error delete documet from storage!");
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
    log4app::Log()->trace(Q_FUNC_INFO);
    const auto &filesInfo = data_map_.at(key).extraData.filesInfo;
    auto it = std::find_if(std::begin(filesInfo), std::end(filesInfo), [nameFile] (const FileInfo &fileInfo) {
        return fileInfo.fileName == nameFile;
    });

    if (it == std::end(filesInfo)) {
        log4app::Log()->error("Data storage(open file). Document don't found in data storage!");
        return;
    }
    const auto &fileInfo = (*it);

    auto nameCacheFile = cache_->createNameCacheFile(fileInfo.fileName, fileInfo.type);
    if (cache_->searchAndOpen(nameCacheFile)) {
        return;
    }

    QByteArray data;
    if (!hardStorage_->unloadDocumentFromStorage(key, nameFile, data)) {
        log4app::Log()->error("Data storage(open file). Document don't unload from had storage!");
        return;
    }

    if (data.size() != fileInfo.size) {
        log4app::Log()->error("Data storage(open file). Document no correct size!");
        return;
    }

    cache_->createAndOpen(nameCacheFile, data);
}

void DataStorageMain::addObserver(Observer *observer) {
    log4app::Log()->trace(Q_FUNC_INFO);
    observers_.push_back(observer);
}

void DataStorageMain::updateObject(const Node *node) {
    log4app::Log()->trace(Q_FUNC_INFO);
    for (auto & observer : observers_) {
        observer->updateRequestedObject(*node, data_map_.at(node->key()).name);
    }
}

void DataStorageMain::updateData(const ExtraData &data) {
    log4app::Log()->trace(Q_FUNC_INFO);
    for (auto &observer : observers_) {
        observer->updateData(data);
    }
}

}

