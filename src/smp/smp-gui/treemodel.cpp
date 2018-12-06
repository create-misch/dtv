#include <QStringList>

#include <controller/controllermain.h>

#include "treeitem.h"
#include "treemodel.h"

class TreeItem;

using namespace libsmp;

TreeItem* toTreeItem(void *data) {
    return static_cast<TreeItem *>(data);
}

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

void TreeModel::setItem(const PrefixNode *item) {
    auto node = toTreeItem(nodeWithKey(rootItem, item->fullKey()));
    if (node != nullptr && node->parent() != nullptr) {
        auto treeItem = new TreeItem(*item);
        auto row = node->row();
        auto nodeIndex = createIndex(row, 1, node);
        beginInsertRows(nodeIndex.parent(), row , row);
        replaceNode(rootItem, treeItem, item->fullKey());
        endInsertRows();
    } else {
        beginResetModel();
        delete rootItem;
        rootItem = new TreeItem(*dynamic_cast<const PrefixNode *>(item));
        endResetModel();
    }
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
    controller_->setNameForObject(item->fullKey(), value.toString());

    return true;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const {
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
