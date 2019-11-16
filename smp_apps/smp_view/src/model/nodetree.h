#pragma once

#include <functional>

#include <common/global.h>

namespace libsmp {

class Node;
class NodeInterface;

constexpr Key defaultKey = 0;

class NodeTree {
public:
    NodeTree();
    ~NodeTree();

    Key addChildForKey(const Key &key);
    Node* getNodeWithKey(const Key &key);

    void insertNode(const Key &key, const Key &keyParent);
    Node *deleteNode(const Key &key);

    using Visitor = std::function<void (const NodeInterface *node)>;

    void recursiveVisitor(Visitor visitor) const;

private:
    void recursiveVisitor(NodeInterface *root, Visitor visitor) const;
    Key nextKey() const;
    NodeInterface *root_node_ = nullptr;
};

}
