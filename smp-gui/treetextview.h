#pragma once
#include <QWidget>

#include <global.h>
#include <model/observer.h>

namespace Ui {
class TreeTextView;
}

namespace libsmp {
class ControllerInterface;
struct Data;
}

class TreeModel;
class TreeItem;

class TreeTextView final : public QWidget, public libsmp::Observer {
    Q_OBJECT
public:
    explicit TreeTextView(QWidget *parent = 0);

    void setController(libsmp::sp<libsmp::ControllerInterface> controller);

    void updateRequestedObject(const libsmp::Node &node) override final;
    void updateData(const libsmp::Data &data) override final;

    ~TreeTextView();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_addElement_clicked();

private:    
    TreeItem *currentTreeItem();
    Ui::TreeTextView *ui;
    libsmp::sp<libsmp::ControllerInterface> controller_;
    libsmp::sp<TreeModel> model_;
};
