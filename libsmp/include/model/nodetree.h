#pragma once

#include <global.h>

namespace libsmp {

class Node;
class NodeInterface;

class NodeTree {
public:
    NodeTree();
    ~NodeTree();

    Key addChildForKey(const Key &key);
    Node* getNodeWithKey(const Key &key);

private:
    Key nextKey() const;
    NodeInterface *root_node_ = nullptr;
};

}
