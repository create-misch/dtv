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

class DataStorageMain final : public DataStorageInterface {
public:
    DataStorageMain();
    ~DataStorageMain();

    void addChildObject(const Key &key) override final;
    void setNameForObject(const Key &key, const QString &name) override final;
    void setDescriptionForObject(const Key &key, const QString &description) override final;
    void requestDataForObject(const Key &key) override final;
    void requestObject(const Key &key) override final;

    void addObserver(Observer* observer);

private:
    void updateObject(const libsmp::Node *node);
    void updateData(const Data &data);

    using DataMap = std::unordered_map<Key, Data>;
    using Observers = std::list<Observer *>;

    std::unique_ptr<NodeTree> tree_;
    DataMap data_map_;
    Observers observers_;
};

}
