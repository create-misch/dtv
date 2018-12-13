#include <QStringList>

#include <controller/controllermain.h>

#include "treeitem.h"
#include "treemodel.h"

class TreeItem;

using namespace libsmp;

TreeModel::TreeModel(libsmp::sp<ControllerInterface> controller, QObject *parent)
    : QAbstractItemModel(parent),
      controller_(controller) {}

TreeModel::~TreeModel() {
    delete rootItem;
}

int TreeModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        auto item = toTreeItem(parent.internalPointer());
        return item->columnCount();
    }
    else
        return rootItem->columnCount();
}

void TreeModel::setItem(const Node &item, const QModelIndex &currentIndex, const QString name) {
    if (item.parent() == nullptr) {
        beginResetModel();
        delete rootItem;
        rootItem = new TreeItem(item, name);
        endResetModel();
        return;
    }

    auto treeItem = toTreeItem(currentIndex);
    /// если элемент есть и нужно просто заменить данные
    if (treeItem != nullptr && treeItem->key() == item.key()) {
            treeItem->setName(name);
            return;
    }

    if (treeItem == nullptr) {
        treeItem = toTreeItem(nodeWithKey(rootItem, item.parent()->key()));
    }

    auto node = treeItem->childWithKey(item.key());
    if (node != nullptr) {
        node->setName(name);
        return;
    }

    QModelIndex index;
    index = currentIndex.isValid() == false ?
                treeItem->parent() == nullptr ? QModelIndex()
                                              : createIndex(treeItem->row(), 0, treeItem)
                                              : currentIndex;

    if (treeItem == nullptr) return;

    if (treeItem->key() == item.parent()->key()) {
        beginInsertRows(index, treeItem->childCount(), treeItem->childCount());
        treeItem->addChild(new TreeItem(item, name));
        endInsertRows();
    };
}

TreeItem *TreeModel::getRootItem() {
    return rootItem;
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

bool TreeModel::setData(const QModelIndex &index,
                        const QVariant &value, int role) {
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
    controller_->setNameForObject(item->key(), value.toString());

    return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {
    if (!rootItem)
        return QVariant();

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent)
const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem = nullptr;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = toTreeItem(parent.internalPointer());

    auto childItem = toTreeItem(parentItem->child(row));
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    auto childItem = toTreeItem(index.internalPointer());
    auto parentItem = toTreeItem(childItem->parent());

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = toTreeItem(parent.internalPointer());

    return parentItem->childCount();
}
