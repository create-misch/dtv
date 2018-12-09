#include <model/prefixtree.h>
#include <model/prefixnode.h>

#include <model/observer.h>

#include <model/modelmain.h>

namespace libsmp {

PrefixNode* toPrefixNode(NodeInterface *node) {
    return dynamic_cast<PrefixNode *>(node);
}

ModelMain::ModelMain() :
    tree_(new PrefixTree) {}

ModelMain::~ModelMain() {}

void ModelMain::addChildObject(const std::string &key) {
    tree_->addEmptyChildForNode(key);

    auto node = tree_->getNodeWithKey(key);
    if (node != nullptr)
        updateObject(node);
}

void ModelMain::setNameForObject(const std::string &key, const QString &name) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;    
    node->setName(name);
    updateObject(node);
}

void ModelMain::setDescriptionForObject(const std::string &key, const QString &description) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;

    node->setDescription(description);
    updateDescription(description);
}

void ModelMain::requestDescriptionForObject(const std::string &key) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;

    updateDescription(node->getDescription());
}

void ModelMain::requestObject(const std::string &key) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;
    updateObject(node);
}

void ModelMain::addObserver(Observer *observer) {
    observers_.push_back(observer);
}

void ModelMain::updateObject(const PrefixNode *node) {
    for (auto & observer : observers_) {
        observer->updateRequestedObject(node);
    }
}

void ModelMain::updateDescription(const QString &description) {
    for (auto &observer : observers_) {
        observer->updateDescription(description);
    }
}

}

