#pragma once

#include <QList>
#include <QVariant>

#include <model/node.h>

class TreeItem : public libsmp::Node {
public:
    explicit TreeItem(const Node &node, libsmp::NodeInterface * parentItem = nullptr);
    explicit TreeItem(const Node &node, const QString &name, libsmp::NodeInterface * parentItem = nullptr);
    virtual ~TreeItem();

    libsmp::NodeInterface* child(int row);
    TreeItem *childWithKey(const libsmp::Key &key);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;

    /// возвращает номер удалённого элемента
    /// на основе полученного node
    int rowForDelete(const NodeInterface *node);
    void setName(const QString &name);

private:
    QString name_ = QObject::tr("New object");
};
