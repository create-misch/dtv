#pragma once

#include <string>

class QString;

namespace libsmp {

class ControllerInterface {
public:
    virtual ~ControllerInterface () {}

    virtual void addChildObject(const std::string &key) = 0;
    virtual void setNameForObject(const std::string &key, const QString &name) = 0;
    virtual void setDescriptionForObject(const std::string &key, const QString &description) = 0;
    virtual void requestDescriptionForObject(const std::string &key) = 0;
    virtual void requestObject(const std::string &key) = 0;
};
}
