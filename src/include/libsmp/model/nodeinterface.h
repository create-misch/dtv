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
    virtual  void setKey(char key) = 0;
    virtual char key() const = 0;
    virtual std::string fullKey() const = 0;

    virtual void setParent(NodeInterface *node) = 0;
    virtual NodeInterface *parent() const = 0;

    virtual void addChild(NodeInterface *node) = 0;
    virtual ChildNodes childs() const = 0;

    virtual bool serialize(QByteArray &data) const = 0;
    virtual bool desirialize(const QByteArray &data) = 0;
};

inline NodeInterface* nodeWithKey(NodeInterface *root, const std::string key) {
    if (!root) return nullptr;
    NodeInterface* currentNode = root;
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
            return nullptr;
    }
    return currentNode;
}

}
