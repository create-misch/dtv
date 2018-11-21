#pragma once

#include <model/modeldata.h>

namespace libsmp {

class Observer {
public:
    virtual ~Observer() {}

    virtual void updateRequestedObject(const Object &object) = 0;
    virtual void updateDescription(const QString &description) = 0;

};

}
