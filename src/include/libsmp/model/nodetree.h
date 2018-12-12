#pragma once

#include <global.h>
#include <functional>

namespace libsmp {

class Node;
class NodeInterface;

class NodeTree {
public:
    NodeTree();
    ~NodeTree();

    Key addChildForKey(const Key &key);
    Node* getNodeWithKey(const Key &key);

    using Visitor = std::function<void (const NodeInterface &node)>;

    void recursiveVisitor(Visitor visitor) const;

private:
    void recursiveVisitor(NodeInterface *root, Visitor visitor) const;
    Key nextKey() const;
    NodeInterface *root_node_ = nullptr;
};

}
