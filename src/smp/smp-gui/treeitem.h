#pragma once

#include <QList>
#include <QVariant>

#include <model/prefixnode.h>

class TreeItem : public libsmp::PrefixNode {
public:
    explicit TreeItem(const PrefixNode &node, libsmp::NodeInterface * parentItem = nullptr);
    ~TreeItem();

    libsmp::NodeInterface * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
};
