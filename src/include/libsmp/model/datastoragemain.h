#pragma once

#include <memory>
#include <list>
#include <unordered_map>

#include <global.h>

#include <model/data.h>

#include <libsmp/model/datastorageinterface.h>

namespace libsmp {

class NodeTree;
class Observer;
class Node;
class HardStorageInterface;
class CacheStorage;

using DataMap = std::unordered_map<Key, Data>;

class DataStorageMain final : public DataStorageInterface {
public:
    DataStorageMain(const QString &fileHardStorage = QString());
    ~DataStorageMain();

    void addChildObject(const Key &key) override final;
    void deleteObject(const Key &key) override final;
    void setNameForObject(const Key &key, const QString &name) override final;
    void setDescriptionForObject(const Key &key, const QString &description) override final;
    void requestDataForObject(const Key &key) override final;
    void requestObject(const Key &key) override final;
    void saveFile(const Key &key, const QString &nameFile, QByteArray &&dataFile) override final;
    void deleteFile(const Key &key, const QString &nameFile) override final;
    void openFile(const Key &key, const QString &nameFile) override final;

    void addObserver(Observer* observer);

private:
    void updateObject(const libsmp::Node *node);
    void updateData(const libsmp::ExtraData &data);

    using Observers = std::list<Observer *>;

    std::unique_ptr<NodeTree> tree_;
    std::unique_ptr<HardStorageInterface> hardStorage_;
    std::unique_ptr<CacheStorage> cache_;
    DataMap data_map_;
    Observers observers_;

};

}
