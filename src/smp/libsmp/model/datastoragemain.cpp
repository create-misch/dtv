#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>

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
    hardStorage_->saveStorageToFile(QString("./%1.smp").arg(data_map_.at(defaultKey).name),
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

void DataStorageMain::saveFile(const Key &key, const QString &nameFile, QByteArray &&dataFile) {
    if (!hardStorage_->saveDocumentInStorage(key, nameFile, std::move(dataFile))) {
        return;
    }
    FileInfo fileInfo = {nameFile.section(".", 0), dataFile.size(), nameFile.section(".", -1)};

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
    QByteArray data;
    if (!hardStorage_->unloadDocumentFromStorage(key, nameFile, data)) {
        return;
    }

    const auto &filesInfo = data_map_.at(key).extraData.filesInfo;
    auto it = std::find_if(std::begin(filesInfo), std::end(filesInfo), [nameFile] (const FileInfo &fileInfo) {
        return fileInfo.fileName == nameFile;
    });

    if (it == std::end(filesInfo)) {
        return;
    }
    const auto &fileInfo = (*it);

    if (data.size() != fileInfo.size) {
        return;
    }

    QString fullNameFile = "./" + nameFile.section(".", 0, 0) + "_cache." + filesInfo.at(0).type;
    QFile file(fullNameFile);
    if (!file.open((QIODevice::WriteOnly))) {
        return;
    }

    file.write(data.constData(), data.size());
    QFileInfo fileInfoDir(file);

    QDesktopServices::openUrl(QUrl(QString("file://%1").arg(fileInfoDir.absoluteFilePath()),
                                   QUrl::TolerantMode));
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

