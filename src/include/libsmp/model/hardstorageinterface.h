#pragma once

#include <model/datastoragemain.h>

class QString;

namespace libsmp {

//class DataMap;
class NodeTree;

class HardStorageInterface {
public:
    virtual ~HardStorageInterface() {}
//    virtual void saveNameWithKey(const Key &key, const QString &name) = 0;
//    virtual void saveDescriptorWithKey(const Key &key, const QString &descriptor) = 0;
//    virtual void saveDataWithKey(const Key &key, const Data &data) =0;

    virtual void saveStorageToFile(const QString &fileName, const DataMap &dataMap,
                                   const NodeTree *nodeTree) = 0;

    virtual void loadStorageFromFile(const QString &fileName, DataMap &dataMap, NodeTree *nodeTree) = 0;
};

}
