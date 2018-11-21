#pragma once

#include <string>
#include <list>

#include <QByteArray>
#include <QDataStream>

#include <libsmp/global.h>

namespace libsmp {

class NodeInterface;
using ChildNodes  = std::list<sp<NodeInterface>>;

class NodeInterface {
public:
    virtual ~NodeInterface() {}
    virtual char key() const = 0;
    virtual std::string fullKey() const = 0;

    virtual void setParent(sp<NodeInterface> node) = 0;
    virtual sp<NodeInterface> parent() const = 0;

    virtual void addChild(sp<NodeInterface> node) = 0;
    virtual ChildNodes childs() const = 0;

    virtual bool serialize(QByteArray &data) const = 0;
    virtual bool desirialize(const QByteArray &data) = 0;
};

}
