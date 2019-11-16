#pragma once

#include <QByteArray>
#include <QDataStream>

namespace libsmp {

template <class T>
QByteArray pack(const T &t) {
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    stream << t;
    return data;
}

template <class T>
void unpack(const QByteArray &data, T &t) {
    QDataStream stream(data);

    stream >> t;
}

}
