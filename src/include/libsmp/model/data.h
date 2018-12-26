#pragma once

#include <QString>
#include <QDataStream>

namespace libsmp {

inline quint64 toHash(QString fileName) {
    std::hash<std::string> hash_fn;
    return static_cast<quint64>(hash_fn(fileName.toStdString()));
}

struct FileInfo {
    QString fileName;
    int size;
    QString type;
};

using FilesInfo = QList<FileInfo>;
struct ExtraData {
    QString description = "Description";
    FilesInfo filesInfo;
};

struct Data {
    QString name = "New Object";
    ExtraData extraData;
};

inline QDataStream &operator <<(QDataStream &in, const FileInfo &data) {
    in << data.fileName;
    in << data.size;
    in << data.type;
    return in;
}

inline QDataStream &operator >>(QDataStream &out, FileInfo &data) {
    out >> data.fileName;
    out >> data.size;
    out >> data.type;
    return out;
}

inline QDataStream &operator <<(QDataStream &in, const ExtraData &data) {
    in << data.description;
    in << data.filesInfo;
    return in;
}

inline QDataStream &operator >>(QDataStream &out, ExtraData &data) {
    out >> data.description;
    out >> data.filesInfo;
    return out;
}

inline QDataStream &operator <<(QDataStream &in, const Data &data) {
    in << data.name;
    in << data.extraData;
    return in;
}

inline QDataStream &operator >>(QDataStream &out, Data &data) {
    out >> data.name;
    out >> data.extraData;
    return out;
}

}
