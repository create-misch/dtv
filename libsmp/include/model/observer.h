#pragma once

#include <global.h>

namespace libsmp {

class Node;
struct Data;

using Node = Node;

class Observer {
public:
    virtual ~Observer() {}

    virtual void updateRequestedObject(const Node &node) = 0;
    virtual void updateData(const Data &date) = 0;

};

}
