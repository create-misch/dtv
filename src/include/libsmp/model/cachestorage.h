#pragma once

#include <QString>

namespace libsmp {

class CacheStorage {
public:
    CacheStorage();
    ~CacheStorage();

    QString createNameCacheFile(const QString &nameFile, const QString &typeFile);
    bool searchAndOpen(const QString &nameCacheFile);
    bool createAndOpen(const QString &nameCacheFile, const QByteArray &dataFile);

    void clearCacheFiles();

private:
    QString fullName(const QString &nameFile);
    bool openDocument(const QString nameFile);

    QString pathStorage_ = "./";
};

}
