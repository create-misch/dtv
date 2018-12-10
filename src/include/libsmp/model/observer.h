#pragma once

#include <global.h>

namespace libsmp {

class Node;

using Node = Node;

class Observer {
public:
    virtual ~Observer() {}

    virtual void updateRequestedObject(const Node *node) = 0;
    virtual void updateDescription(const QString &description) = 0;

};

}
