#pragma once

#include <global.h>

class QString;

namespace libsmp {

class Node;
struct ExtraData;

using Node = Node;

class Observer {
public:
    virtual ~Observer() {}

    virtual void updateRequestedObject(const Node &node, const QString &name) = 0;
    virtual void updateData(const ExtraData &date) = 0;

};

}
