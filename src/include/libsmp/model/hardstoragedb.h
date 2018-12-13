#pragma once

#include <memory>

#include <model/hardstorageinterface.h>

namespace libsmp {

class Database;

class HardStorageDB final : public HardStorageInterface {
public:
    HardStorageDB();
    ~HardStorageDB();
    void saveStorageToFile(const QString &fileName, const DataMap &dataMap,
                            const NodeTree *nodeTree) override final;

    void loadStorageFromFile(const QString &fileName, DataMap &dataMap,
                                     NodeTree *nodeTree) override final;

private:
    std::unique_ptr<Database> db_;

};
}
