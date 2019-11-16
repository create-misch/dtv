#pragma once
#include <QWidget>

#include <common/global.h>
#include <model/observer.h>

namespace Ui {
class TreeTextView;
}

namespace libsmp {
class ControllerInterface;
struct ExtraData;
}

class QKeyEvent;
class TreeModel;
class TreeItem;
class FileInfoModel;

class TreeTextView final : public QWidget, public libsmp::Observer {
    Q_OBJECT
public:
    explicit TreeTextView(QWidget *parent = 0);

    void setController(libsmp::sp<libsmp::ControllerInterface> controller);

    void updateRequestedObject(const libsmp::Node &node, const QString &name) override final;
    void updateData(const libsmp::ExtraData &data) override final;

    ~TreeTextView();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_save_clicked();
    void on_pushButton_addElement_clicked();
    void on_pushButton_addFile_clicked();
    void on_pushButton_deleteFile_clicked();
    void on_pushButton_openFiel_clicked();

    void on_pushButton_removeElement_clicked();

private:
    TreeItem *currentTreeItem();
    Ui::TreeTextView *ui;
    libsmp::sp<libsmp::ControllerInterface> controller_;
    libsmp::sp<TreeModel> model_;
    libsmp::sp<FileInfoModel> fileInfoModel_;
};
