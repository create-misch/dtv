#include <model/node.h>

namespace libsmp {

Node::Node(const Key &key, NodeInterface *parent) :
    key_(key),
    parent_(parent) {}

Node::~Node() {
    qDeleteAll(childs_);
    childs_.clear();
}

void Node::setKey(const Key &key) {
    key_ = key;
}

Key Node::key() const {
    return key_;
}

void Node::setParent(NodeInterface *node) {
    parent_ = node;
}

NodeInterface *Node::parent() const {
    return parent_;
}

void Node::addChild(NodeInterface *node) {
    if (node->parent() == nullptr)
        node->setParent(this);
    childs_.push_back(node);
}

bool Node::deleteChild(NodeInterface *node) {
    auto it_remove = std::remove(std::begin(childs_), std::end(childs_), node);
    if (it_remove == std::end(childs_)) {
        return false;
    }
    qDeleteAll(it_remove + 1, std::end(childs_));
    childs_.erase(it_remove, std::end(childs_));
    return  true;
}

ChildNodes Node::childs() const {
    return childs_;
}

ChildNodes &Node::childs() {
    return childs_;
}

bool Node::serialize(QByteArray &data) const {
    Q_UNUSED(data)
    return true;
}

bool Node::desirialize(const QByteArray &data) {
    Q_UNUSED(data)
    return true;
}

int Node::size() const {
    int size = 0;
    for (const auto &node : childs_)
        size += dynamic_cast<Node *>(node)->size();

    size += childs_.size();

    return size;
}

}
