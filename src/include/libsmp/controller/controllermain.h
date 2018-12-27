#pragma once

#include <global.h>

#include <controller/controllerinterface.h>

namespace libsmp {

class DataStorageInterface;

class ControllerMain : public ControllerInterface {
public:
    explicit ControllerMain(sp<DataStorageInterface> storage);

    void addChildObject(const Key &key) override final;
    void deleteObject(const Key &key) override final;
    void setNameForObject(const Key &key, const QString &name) override final;
    void setDescriptionForObject(const Key &key, const QString &description) override final;
    void requestDataForObject(const Key &key) override final;
    void requestObject(const Key &key) override final;
    void saveFile(const Key &key, const QString &nameFile, QByteArray &&dataFile) override final;
    void deleteFile(const Key &key, const QString &nameFile) override final;
    void openFile(const Key &key, const QString &nameFile) override final;

private:
    sp<DataStorageInterface> storage_;
};

}
