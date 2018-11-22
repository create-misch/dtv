#pragma once

#include <global.h>

#include <controller/controllerinterface.h>

namespace libsmp {

class ModelInterface;

class ControllerMain : public ControllerInterface {
public:
    explicit ControllerMain(sp<ModelInterface> model);

    void addChildObject(const std::string &key) override final;
    void setNameForObject(const std::string &key, const QString &name) override final;
    void setDescriptionForObject(const std::string &key, const QString &description) override final;
    void requestDescriptionForObject(const std::string &key) override final;
    void requestObject(const std::string &key) override final;

private:
    sp<ModelInterface> model_;
};

}
