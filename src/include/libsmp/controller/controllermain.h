#pragma once

#include <global.h>

#include <controller/controllerinterface.h>

namespace libsmp {

class DataStorageInterface;

class ControllerMain : public ControllerInterface {
public:
    explicit ControllerMain(sp<DataStorageInterface> model);

    void addChildObject(const Key &key) override final;
    void setNameForObject(const Key &key, const QString &name) override final;
    void setDescriptionForObject(const Key &key, const QString &description) override final;
    void requestDescriptionForObject(const Key &key) override final;
    void requestObject(const Key &key) override final;

private:
    sp<DataStorageInterface> model_;
};

}
