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
    if (key == defaultKey) return dynamic_cast<Node *>(root_node_);
    return dynamic_cast<Node *>(nodeWithKey(root_node_, key));
}

void NodeTree::insertNode(const Key &key, const Key &keyParent) {
    if (key == defaultKey) {
        root_node_ = new Node(key);
        return;
    }

    auto node = getNodeWithKey(keyParent);
    node->addChild(new Node(key));
}

void NodeTree::recursiveVisitor(NodeInterface *root, Visitor visitor) const {
    if (!root) return;
    visitor(*root);

    if (root->childs().size() == 0) return;

    for (auto node : root->childs()) {
        recursiveVisitor(node, visitor);
    }
}

void NodeTree::recursiveVisitor(NodeTree::Visitor visitor) const {
    recursiveVisitor(root_node_, visitor);
}

Key NodeTree::nextKey() const {
    if (root_node_ == nullptr)
        return defaultKey;
    return dynamic_cast<Node *>(root_node_)->size() + 1;
}

}
