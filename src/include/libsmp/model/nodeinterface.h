#pragma once

#include <string>
#include <list>

#include <QByteArray>
#include <QDataStream>
#include <QList>

#include <libsmp/global.h>

namespace libsmp {

class NodeInterface;
using ChildNodes  = QList<NodeInterface *>;

class NodeInterface {
public:
    virtual ~NodeInterface() {}
    virtual  void setKey(const Key &key) = 0;
    virtual Key key() const = 0;

    virtual void setParent(NodeInterface *node) = 0;
    virtual NodeInterface *parent() const = 0;

    virtual void addChild(NodeInterface *node) = 0;
    virtual ChildNodes childs() const = 0;
    virtual ChildNodes &childs() = 0;

    virtual bool serialize(QByteArray &data) const = 0;
    virtual bool desirialize(const QByteArray &data) = 0;
};

inline NodeInterface* nodeWithKey(const NodeInterface *root, const Key &key) {
    NodeInterface *findNode = nullptr;

    if (!root) return findNode;
    if (root->childs().size() == 0) return findNode;

    for (const auto &node : root->childs()) {
        if (node->key() == key)
            return node;
    }
    return findNode;
}

//inline bool replaceNode(NodeInterface *root, NodeInterface *nodeReplace, const std::string &key) {
//    auto searchNode = nodeWithKey(root, key);
//    nodeReplace->setParent(searchNode->parent());
//    auto &childs = searchNode->parent()->childs();
//    auto idNodeForReplace = childs.indexOf(searchNode);

//    delete childs[idNodeForReplace];
//    childs[idNodeForReplace] = nodeReplace;

//    return true;
//}

}
