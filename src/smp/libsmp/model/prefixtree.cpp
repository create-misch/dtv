#include <model/prefixnode.h>

#include <model/prefixtree.h>

namespace libsmp {

using namespace std;

PrefixTree::PrefixTree() {}

PrefixTree::~PrefixTree() {}

bool PrefixTree::addEmptyChildForNode(const string &key){
    if (key.empty() || key.at(0) == 0x00) {
        node_root_ = make_shared<PrefixNode>(keyForNode());
        return true;
    }

    auto node = getNodeWithKey(key);

    if (node == nullptr)
        return false;

    node->addChild(make_shared<PrefixNode>(keyForNode()));

    return true;
}

sp<NodeInterface> PrefixTree::getNodeWithKey(const string &key) {
    sp<NodeInterface> currentNode = node_root_;
    for (const auto &k : key) {
        if (currentNode->key() == k)
            continue;

        for (auto &node : currentNode->childs()) {
            if (node->key() == k) {
                currentNode = node;
                break;
            }
        }

        if (currentNode->key() != k)
            return sp<NodeInterface>();
    }
    return currentNode;
}

char PrefixTree::keyForNode() {
    return key_value++;
}

}
