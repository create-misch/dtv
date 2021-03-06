#pragma once

#include <QAbstractItemModel>

#include <model/data.h>

class FileInfoModel : public QAbstractItemModel {
    Q_OBJECT
public:
    FileInfoModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void setItems(const libsmp::FilesInfo &filesInfo);

private:
    libsmp::FilesInfo filesInfo_;
};


