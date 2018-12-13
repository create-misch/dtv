#pragma once

#include <QString>
#include <QDataStream>

namespace libsmp {

struct ExtraData {
    QString description = "Description";
};

struct Data {
    QString name = "New Object";
    ExtraData extraData;
};

inline QDataStream &operator <<(QDataStream &in, const ExtraData &data) {
    in << data.description;
    return in;
}

inline QDataStream &operator >>(QDataStream &out, ExtraData &data) {
    out >> data.description;
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
