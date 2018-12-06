#include <QInputDialog>

#include <controller/controllerinterface.h>

#include <model/nodeinterface.h>
#include "treeitem.h"
#include "treemodel.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace libsmp;

TreeItem *indexToItem(QModelIndex &&index) {
    return static_cast<TreeItem*>(index.internalPointer());
}

MainWindow::MainWindow(sp<ControllerInterface> controller, QWidget *parent) :
    QMainWindow(parent),
    controller_(controller),
    model_(std::make_shared<TreeModel>(controller)),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->treeView->setModel(model_.get());

    connect(ui->treeView, &QTreeView::clicked, this,
            [this] (const QModelIndex &index) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        controller_->requestDescriptionForObject(item->fullKey());
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateDescription(const QString &description) {
    ui->textBrowser->setText(description);
}

void MainWindow::updateRequestedObject(const Node *node) {
    model_->setItem(node);
}

void MainWindow::on_pushButton_addChildren_clicked(){
    TreeItem* treeItem = indexToItem(ui->treeView->currentIndex());
    if (treeItem == nullptr) return;
    controller_->addChildObject(treeItem->fullKey());
}

void MainWindow::on_pushButton_SaveDescription_clicked() {
    auto text = ui->textBrowser->toPlainText();
    TreeItem* treeItem = indexToItem(ui->treeView->currentIndex());
    if (!treeItem) return;
    controller_->setDescriptionForObject(treeItem->fullKey(), text);    
}
