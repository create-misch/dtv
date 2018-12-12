#pragma once

#include <QString>
#include <QDataStream>

namespace libsmp {

struct Data {
    QString name = "New Object";
    QString description = "Description";
};

inline QDataStream &operator <<(QDataStream &in, const Data &data) {
    in << data.name;
    in << data.description;

    return in;
}

inline QDataStream &operator >>(QDataStream &out, Data &data) {
    out >> data.name;
    out >> data.description;

    return out;
}

}
