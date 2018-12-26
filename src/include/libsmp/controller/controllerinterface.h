#pragma once

#include <global.h>
#include <string>

class QString;
class QByteArray;

namespace libsmp {

class ControllerInterface {
public:
    virtual ~ControllerInterface () {}

    virtual void addChildObject(const Key &key) = 0;
    virtual void setNameForObject(const Key &key, const QString &name) = 0;
    virtual void setDescriptionForObject(const Key &key, const QString &description) = 0;
    virtual void requestDataForObject(const Key &key) = 0;
    virtual void requestObject(const Key &key) = 0;
    virtual void saveFile(const Key &key, const QString &nameFile, QByteArray &&dataFile) = 0;
    virtual void deleteFile(const Key &key, const QString &nameFile) = 0;
    virtual void openFile(const Key &key, const QString &nameFile) = 0;
};
}
