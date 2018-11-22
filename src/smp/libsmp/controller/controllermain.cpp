#include <model/modelinterface.h>

#include <controller/controllermain.h>

namespace libsmp {

ControllerMain::ControllerMain(sp<ModelInterface> model) :
    model_(model) {}

void ControllerMain::addChildObject(const std::string &key) {
    model_->addChildObject(key);
}

void ControllerMain::setNameForObject(const std::string &key, const QString &name) {
    model_->setNameForObject(key, name);
}

void ControllerMain::setDescriptionForObject(const std::string &key, const QString &description){
    model_->setDescriptionForObject(key, description);
}

void ControllerMain::requestDescriptionForObject(const std::string &key) {
    model_->requestDescriptionForObject(key);
}

void ControllerMain::requestObject(const std::string &key) {
    model_->requestObject(key);
}

}

