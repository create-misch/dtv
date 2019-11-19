#pragma once

#include <string>
#include <list>

#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <common/global.h>

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
    virtual bool deleteChild(NodeInterface *node) = 0;
    virtual ChildNodes childs() const = 0;
    virtual ChildNodes &childs() = 0;

    virtual bool serialize(QByteArray &data) const = 0;
    virtual bool desirialize(const QByteArray &data) = 0;
};

inline NodeInterface* nodeWithKey(NodeInterface *root, const Key &key) {
    NodeInterface *findNode = nullptr;

    if (!root) return findNode;
    if (root->key() == key) return root;
    if (root->childs().size() == 0) return findNode;

    for (const auto &node : root->childs()) {
        if (node->key() == key) {
            return node;
        }

        findNode = nodeWithKey(node, key);
        if (findNode != nullptr)
            return findNode;
    }
    return findNode;
}

}
