/// @file listmodel.h
/// @brief Модель данных для массива
/// @author Алексей Максимов
/// @date 2015-08-20

#pragma once

#include <QtCore/QAbstractItemModel>

template<typename T, typename Container = QList<T>>
class ListModel : public QAbstractItemModel
{
public:
    typedef Container List;
    ListModel(QObject* parent = nullptr) : QAbstractItemModel(parent) {

    }
    virtual ~ListModel() {

    }

    const T& constElement(int i) const {
        return list_[i];
    }

    T& element(int i) {
        return list_[i];
    }

    int count() const {
        return list_.count();
    }

    void setListData(const List &list) {
        beginResetModel();
        list_ = list;
        endResetModel();
    }

    /// добавление элемента. Возвращает индекс добавленного
    int addElement(T e) {
        beginInsertRows(QModelIndex(), count(), count());
        list_.append(e);
        endInsertRows();
        return list_.size() - 1;
    }
    void prependElements(const List &elementList) {
      beginInsertRows(QModelIndex(), 0, elementList.count() - 1);

      for (const T &e : elementList) {
        list_.prepend(e);
      }

      endInsertRows();
    }

    void addElements(const List &elementList) {
      beginInsertRows(QModelIndex(), count(), count() + elementList.count() - 1);
      list_.append(elementList);
      endInsertRows();
    }

    int insertElement(int index, T e) {
        beginInsertRows(QModelIndex(), index, index);
        list_.insert(index, e);
        endInsertRows();
        return index;
    }

    void removeElement(T e) {
        int index = list_.indexOf(e);
        if (index == -1) return;
        removeElementByIndex(index);
    }

    void replaceElement (int index, T e) {
        if (index == -1 || index > count())
            return;
        list_.replace (index, e);
    }

    void removeElementByIndex(int index) {
        beginRemoveRows(QModelIndex(), index, index);
        list_.removeAt(index);
        endRemoveRows();
    }

    void removeAll() {
        beginRemoveRows(QModelIndex(), 0, count());
        list_.clear();
        endRemoveRows();
    }

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE{
        if (parent.isValid()) {
            return QModelIndex();
        }
        return createIndex(row, column);
    }  // index

    QModelIndex parent(const QModelIndex& child) const Q_DECL_OVERRIDE {
        Q_UNUSED(child);
        return QModelIndex();
    }  // parent

    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE{
        Q_UNUSED(parent);
        return count();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE{
        Q_UNUSED(parent)
        return 1;
    }
    bool removeRows(int row, int count, const QModelIndex &parent) override
    {
        Q_UNUSED(parent)

        if(count <= 0 || (row + count > list_.size()) )
            return false;

        beginRemoveRows(QModelIndex(), row, row + count -1);
        list_.erase(list_.begin() + row, list_.begin() + row + count);
        endRemoveRows();
        return true;
    }

    const List& list() const { return list_; }
protected:
    List& list() { return list_; }
private:
    List list_;
private:
    Q_DISABLE_COPY(ListModel)
};
