#include <model/prefixtree.h>
#include <model/prefixnode.h>

#include <model/modelmain.h>

namespace libsmp {

ModelMain::ModelMain() :
    tree_(new PrefixTree) {}

ModelMain::~ModelMain() {}

void ModelMain::addChildObject(const std::string &key) {
    tree_->addEmptyChildForNode(key);
}

void ModelMain::setNameForObject(const std::string &key, const QString &name) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;
    dynamic_cast<PrefixNode *>(node.get())->setName(name);
}

void ModelMain::setDescriptionForObject(const std::string &key, const QString &description) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;
    dynamic_cast<PrefixNode *>(node.get())->setDescription(description);
}

void ModelMain::requestObject(const std::string &key) {
    auto node = tree_->getNodeWithKey(key);

    if (node == nullptr) return;
}

}

