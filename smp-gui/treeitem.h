#pragma once

#include <QList>
#include <QVariant>

#include <model/node.h>

class TreeItem : public libsmp::Node {
public:
    explicit TreeItem(const Node &node, libsmp::NodeInterface * parentItem = nullptr);
    virtual ~TreeItem();

    libsmp::NodeInterface * child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;

    void setName(const QString &name);

private:
    QString name_ = QObject::tr("New object");
};
