#pragma once

#include <global.h>

namespace libsmp {

class PrefixNode;

using Node = PrefixNode;

class Observer {
public:
    virtual ~Observer() {}

    virtual void updateRequestedObject(const Node *node) = 0;
    virtual void updateDescription(const QString &description) = 0;

};

}
