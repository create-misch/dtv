#pragma once

#include <global.h>
#include <unordered_map>

class QString;
class QByteArray;

namespace libsmp {

class NodeTree;
struct Data;

class HardStorageInterface {
public:
    virtual ~HardStorageInterface() {}
    virtual void saveStorageToFile(const QString &fileName, const std::unordered_map<Key, Data> &dataMap,
                                   const NodeTree *nodeTree) = 0;

    virtual void loadStorageFromFile(const QString &fileName,
                                     std::unordered_map<Key, Data> &dataMap, NodeTree *nodeTree) = 0;

    virtual void saveDocumentInStorage(const Key &key, QByteArray &&data) = 0;
};

}
