#pragma once

#include <memory>

#include <model/hardstorageinterface.h>

namespace libsmp {

class Database;

class HardStorageDB final : public HardStorageInterface {
public:
    HardStorageDB();
    ~HardStorageDB();
    void saveStorageToFile(const QString &fileName, const std::unordered_map<Key, Data> &dataMap,
                            const NodeTree *nodeTree) override final;

    void loadStorageFromFile(const QString &fileName, std::unordered_map<Key, Data> &dataMap,
                                     NodeTree *nodeTree) override final;

    bool saveDocumentInStorage(const Key &key, const QString &nameFile, QByteArray &&data) override final;
    bool deleteDocumentFromStorage(const Key &key, const QString &nameFIle) override final;
    bool unloadDocumentFromStorage(const Key &key, const QString &nameFile, QByteArray &data) override final;

private:
    std::unique_ptr<Database> db_;

};
}
