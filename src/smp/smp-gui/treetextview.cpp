#include <controller/controllermain.h>

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
        controller_->requestDescriptionForObject(item->fullKey());
    });
}

void TreeTextView::setController(libsmp::sp<libsmp::ControllerInterface> controller) {
    controller_ = controller;
    model_ = std::make_shared<TreeModel>(controller_);
    ui->treeView->setModel(model_.get());
}

void TreeTextView::updateRequestedObject(const libsmp::Node *node) {
    model_->setItem(node);
}

void TreeTextView::updateDescription(const QString &description) {
    ui->textBrowser->setText(description);
}

TreeTextView::~TreeTextView() {
    delete ui;
}

void TreeTextView::on_pushButton_save_clicked() {
    auto text = ui->textBrowser->toPlainText();
    TreeItem* treeItem = indexToItem(ui->treeView->currentIndex());
    if (!treeItem) return;
    controller_->setDescriptionForObject(treeItem->fullKey(), text);
}

void TreeTextView::on_pushButton_addElement_clicked() {
    TreeItem* treeItem = indexToItem(ui->treeView->currentIndex());
    std::string key = treeItem == nullptr ? std::string("a") :  treeItem->fullKey();
    controller_->addChildObject(key);
}
