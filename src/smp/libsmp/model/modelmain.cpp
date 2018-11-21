#include <model/prefixtree.h>
#include <model/prefixnode.h>

#include <model/observer.h>

#include <model/modelmain.h>

namespace libsmp {

sp<PrefixNode> toPrefixNode(sp<NodeInterface> &node) {
    return std::dynamic_pointer_cast<PrefixNode>(node);
}

ModelMain::ModelMain() :
    tree_(new PrefixTree) {}

ModelMain::~ModelMain() {}

void ModelMain::addChildObject(const std::string &key) {
    tree_->addEmptyChildForNode(key);

    auto node = tree_->getNodeWithKey(key);
    updateObject(toPrefixNode(node)->toObject());
}

void ModelMain::setNameForObject(const std::string &key, const QString &name) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;
    auto prefixNode = toPrefixNode(node);
    prefixNode->setName(name);
    updateObject(prefixNode->toObject());
}

void ModelMain::setDescriptionForObject(const std::string &key, const QString &description) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;

    auto prefixNode = toPrefixNode(node);
    prefixNode->setDescription(description);
    updateDescription(prefixNode->getDescription());
}

void ModelMain::requestObject(const std::string &key) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;
    auto prefixNode = toPrefixNode(node);
    updateObject(prefixNode->toObject());
}

void ModelMain::addObserver(sp<Observer> observer) {
    observers_.push_back(observer);
}

void ModelMain::updateObject(const Object &object) {
    for (auto & observer : observers_) {
        observer->updateRequestedObject(object);
    }
}

void ModelMain::updateDescription(const QString &description) {
    for (auto & observer : observers_) {
        observer->updateDescription(description);
    }
}

}

