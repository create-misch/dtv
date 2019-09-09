#include <QDir>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>

#include <log4app.h>

#include <model/cachestorage.h>

namespace  libsmp {

CacheStorage::CacheStorage() {
    pathStorage_ = QCoreApplication::applicationDirPath() + "/";
}

CacheStorage::~CacheStorage() {}

QString CacheStorage::createNameCacheFile(const QString &nameFile, const QString &typeFile) {
    return pathStorage_ + nameFile + "_cache." + typeFile;
}

bool CacheStorage::searchAndOpen(const QString &nameCacheFile) {
    QDir dir(pathStorage_);
    auto files = dir.entryList();

    auto find_it = std::find(std::begin(files), std::end(files),
                             nameCacheFile.section("/", -1));
    if (find_it == std::end(files)) {
        log4app::Log()->info("Cache storage. Cache file with name %1 don't found", nameCacheFile);
        return false;
    }
    return openDocument(nameCacheFile);
}

bool CacheStorage::createAndOpen(const QString &nameCacheFile, const QByteArray &dataFile) {
    QString fullFileName = fullName(nameCacheFile);

    QFile file(fullFileName);
    if (!file.open((QIODevice::WriteOnly))) {
        log4app::Log()->error("Cache storage. File %1 don't created!!", nameCacheFile);
        return false;
    }

    auto size = file.write(dataFile.constData(), dataFile.size());
    if (size != dataFile.size()) {
        log4app::Log()->error("Cache storage. Error write file %1 - %2", nameCacheFile, file.errorString());
        return false;
    }

    return openDocument(nameCacheFile);
}

void CacheStorage::clearCacheFiles() {
    QDir dir(pathStorage_);
    auto namesFiles = dir.entryList({"*_cache.*"});
    for (const auto &nameFile : namesFiles) {
        QFile file(dir.absoluteFilePath(nameFile));
        file.remove();
    }
}

QString CacheStorage::fullName(const QString &nameFile) {
    QFileInfo fileInfo(nameFile);
    return fileInfo.isAbsolute() ? nameFile : pathStorage_ + nameFile;
}

bool CacheStorage::openDocument(const QString nameFile) {
    QString fullFileName = fullName(nameFile);
    if (!QFileInfo::exists(fullFileName)) {
        log4app::Log()->error("Cache storage. File %1 don't found!!", fullFileName);
        return false;
    }

#ifdef __unix
#else
    fullFileName.prepend("/");
#endif

    log4app::Log()->info("Cache storage. Open document %1", fullFileName);
    return QDesktopServices::openUrl(QUrl(QString("file://%1").arg(fullFileName),
                                   QUrl::TolerantMode));
}

}
