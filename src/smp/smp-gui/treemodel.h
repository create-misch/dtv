#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <global.h>

namespace libsmp {
class ControllerInterface;
}

class TreeItem;

class TreeModel : public QAbstractItemModel {
    Q_OBJECT
public:
    explicit TreeModel(libsmp::sp<libsmp::ControllerInterface> controller, QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void setRootItem(TreeItem *item);

private:
    TreeItem* rootItem;
    libsmp::sp<libsmp::ControllerInterface> controller_;
};

