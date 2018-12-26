#include "fileinfomodel.h"

libsmp::FileInfo *toFileInfo(void *data) {
    return static_cast<libsmp::FileInfo *>(data);
}

FileInfoModel::FileInfoModel(QObject *parent) :
    QAbstractItemModel(parent) {}

QVariant FileInfoModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    if (index.row() >= filesInfo_.size())
        return QVariant();

    auto &fileInfo = filesInfo_[index.row()];

    switch (index.column()) {
    case 0:
        return fileInfo.fileName;

    case 1:
        return fileInfo.type;

    case 2:
        return fileInfo.size;

    default:
        return "Unknown";
    }

    return "Unknown";
}

Qt::ItemFlags FileInfoModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}

QVariant FileInfoModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0:
            return tr("Name file");

        case 1:
            return tr("Type file");

        case 2:
            return tr("Size file");

        default:
            return tr("Unknown");
        }
    }

    return QVariant();
}

QModelIndex FileInfoModel::index(int row, int column, const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return createIndex(row, column);
}

QModelIndex FileInfoModel::parent(const QModelIndex &index) const {
    Q_UNUSED(index)

    return QModelIndex();
}

int FileInfoModel::rowCount(const QModelIndex &parent) const {
    if (parent == QModelIndex()) {
        return filesInfo_.size();
    }

    return 0;
}

int FileInfoModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)

    return 3;
}

void FileInfoModel::setItems(const libsmp::FilesInfo &filesInfo) {
        beginResetModel();
        filesInfo_ = filesInfo;
        endResetModel();
}
