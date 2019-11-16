#pragma once

#include <unordered_map>

#include <common/global.h>

class QString;
class QByteArray;

namespace libsmp {

class NodeTree;
struct Data;

class HardStorageInterface {
public:
    virtual ~HardStorageInterface() {}
    virtual void saveStorageToFile(const std::unordered_map<Key, Data> &dataMap, const NodeTree *nodeTree) = 0;
    virtual void loadStorageFromFile(std::unordered_map<Key, Data> &dataMap, NodeTree *nodeTree) = 0;

    virtual bool saveDocumentInStorage(const Key &key, const QString &nameFile, QByteArray &&data) = 0;
    virtual bool deleteDocumentFromStorage(const Key &key, const QString &nameFIle) = 0;
    virtual bool unloadDocumentFromStorage(const Key &key, const QString &nameFile, QByteArray &data) = 0;
};

}
