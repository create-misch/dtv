#include <model/modeldata.h>

#include <model/prefixnode.h>

namespace libsmp {

PrefixNode::PrefixNode() {}

PrefixNode::~PrefixNode() {
    qDeleteAll(childNodes_);
}

void PrefixNode::setKey(char key) {
    key_ = key;
}

char PrefixNode::key() const {
    return key_;
}

std::string PrefixNode::fullKey() const {
    if (parent() == nullptr) {
        return std::string(&key_, 1);
    }
    auto key = parent()->fullKey();
    key.push_back(key_);
    return key;
}

void PrefixNode::setParent(NodeInterface *node) {
    parent_ = node;
}

NodeInterface* PrefixNode::parent() const {
    return parent_;
}

void PrefixNode::addChild(NodeInterface *node) {
    node->setParent(this);
    childNodes_.push_back(node);
}

ChildNodes PrefixNode::childs() const {
    return childNodes_;
}

bool PrefixNode::serialize(QByteArray &data) const {
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << key_;
    stream << name_;
    //        for( auto node : childNodes_) {
    ////            stream << *node.get();
    //        }

    return true;
}

bool PrefixNode::desirialize(const QByteArray &data) {
    QDataStream stream(data);
    //        stream >> key_;
    stream >> name_;

    return true;
}

void PrefixNode::setName(const QString &name) {
    name_ = name;
}

QString PrefixNode::getName() const {
    return name_;
}

void PrefixNode::setDescription(const QString &description) {
    description_ = description;
}

QString PrefixNode::getDescription() const {
    return description_;
}


}
