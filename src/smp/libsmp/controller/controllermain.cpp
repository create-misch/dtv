#include <model/datastorageinterface.h>

#include <controller/controllermain.h>

namespace libsmp {

ControllerMain::ControllerMain(sp<DataStorageInterface> model) :
    model_(model) {}

void ControllerMain::addChildObject(const Key &key) {
    model_->addChildObject(key);
}

void ControllerMain::setNameForObject(const Key &key, const QString &name) {
    model_->setNameForObject(key, name);
}

void ControllerMain::setDescriptionForObject(const Key &key, const QString &description){
    model_->setDescriptionForObject(key, description);
}

void ControllerMain::requestDescriptionForObject(const Key &key) {
    model_->requestDescriptionForObject(key);
}

void ControllerMain::requestObject(const Key &key) {
    model_->requestObject(key);
}

}

