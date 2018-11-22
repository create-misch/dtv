#pragma once

#include <global.h>

namespace libsmp {

class NodeInterface;

class Observer {
public:
    virtual ~Observer() {}

    virtual void updateRequestedObject(const NodeInterface *node) = 0;
    virtual void updateDescription(const QString &description) = 0;

};

}
