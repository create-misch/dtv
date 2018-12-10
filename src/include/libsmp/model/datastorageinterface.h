#pragma once

#include <global.h>
#include <string>

class QString;

namespace libsmp {


class DataStorageInterface {
public:
    virtual ~DataStorageInterface() {}
    virtual void addChildObject(const Key &key) = 0;
    virtual void setNameForObject(const Key &key, const QString &name) = 0;
    virtual void setDescriptionForObject(const Key &key, const QString &description) = 0;
    virtual void requestDescriptionForObject(const Key &key) = 0;
    virtual void requestObject(const Key &key) = 0;

};

}
