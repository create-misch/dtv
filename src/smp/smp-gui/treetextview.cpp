#include <controller/controllermain.h>

#include <model/data.h>

#include "treeitem.h"
#include "treemodel.h"

#include "treetextview.h"
#include "ui_treetextview.h"

TreeItem *indexToItem(QModelIndex &&index) {
    return static_cast<TreeItem*>(index.internalPointer());
}

TreeTextView::TreeTextView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeTextView) {
    ui->setupUi(this);

    connect(ui->treeView, &QTreeView::clicked, this,
            [this] (const QModelIndex &index) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        controller_->requestDataForObject(item->key());
    });
}

void TreeTextView::setController(libsmp::sp<libsmp::ControllerInterface> controller) {
    controller_ = controller;
    model_ = std::make_shared<TreeModel>(controller_);
    ui->treeView->setModel(model_.get());
}

void TreeTextView::updateRequestedObject(const libsmp::Node &node, const QString &name) {
    model_->setItem(node, ui->treeView->currentIndex(), name);
}

void TreeTextView::updateData(const libsmp::ExtraData &data) {
    ui->textBrowser->setText(data.description);
}

TreeTextView::~TreeTextView() {
    delete ui;
}

void TreeTextView::on_pushButton_save_clicked() {
    auto text = ui->textBrowser->toPlainText();
    TreeItem* treeItem = indexToItem(ui->treeView->currentIndex());
    if (!treeItem) return;
    controller_->setDescriptionForObject(treeItem->key(), text);
}

void TreeTextView::on_pushButton_addElement_clicked() {
    TreeItem* treeItem = indexToItem(ui->treeView->currentIndex());
    libsmp::Key key = treeItem == nullptr ? 0 :  treeItem->key();
    controller_->addChildObject(key);
}

TreeItem *TreeTextView::currentTreeItem() {
    auto treeItem = toTreeItem(ui->treeView->currentIndex());
    return treeItem == nullptr ? model_->getRootItem() : treeItem;
}
