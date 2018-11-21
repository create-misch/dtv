#pragma once

#include <string>
#include <libsmp/global.h>

namespace libsmp {

class NodeInterface;

class PrefixTree {
public:
    PrefixTree();
    ~PrefixTree();

    bool addEmptyChildForNode(const std::string &key);

    sp<NodeInterface> getNodeWIthKey(const std::string &key);

private:
    char keyForNode();
    sp<NodeInterface> node_root_;
    char key_value = 0x61;// 'a'

};
}
