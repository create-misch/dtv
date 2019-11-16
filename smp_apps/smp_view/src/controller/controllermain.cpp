#include <model/datastorageinterface.h>

#include <controller/controllermain.h>

namespace libsmp {

ControllerMain::ControllerMain(sp<DataStorageInterface> storage) :
    storage_(storage) {}

void ControllerMain::addChildObject(const Key &key) {
    storage_->addChildObject(key);
}

void ControllerMain::deleteObject(const Key &key) {
    storage_->deleteObject(key);
}

void ControllerMain::setNameForObject(const Key &key, const QString &name) {
    storage_->setNameForObject(key, name);
}

void ControllerMain::setDescriptionForObject(const Key &key, const QString &description){
    storage_->setDescriptionForObject(key, description);
}

void ControllerMain::requestDataForObject(const Key &key) {
    storage_->requestDataForObject(key);
}

void ControllerMain::requestObject(const Key &key) {
    storage_->requestObject(key);
}

void ControllerMain::saveFile(const Key &key, const QString &nameFile, QByteArray &&dataFile) {
    storage_->saveFile(key, nameFile, std::move(dataFile));
}

void ControllerMain::deleteFile(const Key &key, const QString &nameFile) {
    storage_->deleteFile(key, nameFile);
}

void ControllerMain::openFile(const Key &key, const QString &nameFile) {
    storage_->openFile(key, nameFile);
}

}

