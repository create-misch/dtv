#pragma once

#include <string>
#include <global.h>

namespace libsmp {

class NodeInterface;

class PrefixTree {
public:
    PrefixTree();
    ~PrefixTree();

    bool addEmptyChildForNode(const std::string &key);

    NodeInterface* getNodeWithKey(const std::string &key);

private:
    char keyForNode();
    NodeInterface *node_root_ = nullptr;
    char key_value = 0x61;// 'a'

};
}
