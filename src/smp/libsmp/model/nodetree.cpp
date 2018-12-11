#include <model/node.h>

#include <model/nodetree.h>

namespace libsmp {

NodeTree::NodeTree() {}

NodeTree::~NodeTree() {
    delete root_node_;
}

Key NodeTree::addChildForKey(const Key &key) {
    auto keyNode = nextKey();
    if (root_node_ == nullptr) {
        root_node_ = new Node(keyNode);
        return keyNode;
    }
    auto node = getNodeWithKey(key);
    node->addChild(new Node(keyNode));

    return keyNode;
}

Node *NodeTree::getNodeWithKey(const Key &key) {
    if (key == 0) return dynamic_cast<Node *>(root_node_);
    return dynamic_cast<Node *>(nodeWithKey(root_node_, key));
}

Key NodeTree::nextKey() const {
    if (root_node_ == nullptr)
        return 0;
    return dynamic_cast<Node *>(root_node_)->size() + 1;
}

}
