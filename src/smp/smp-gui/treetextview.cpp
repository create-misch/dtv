#include <QFileDialog>

#include <controller/controllermain.h>

#include <model/data.h>

#include "treeitem.h"
#include "treemodel.h"
#include "fileinfomodel.h"

#include "treetextview.h"
#include "ui_treetextview.h"

TreeItem *indexToItem(QModelIndex &&index) {
    return static_cast<TreeItem*>(index.internalPointer());
}

TreeTextView::TreeTextView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeTextView),
    fileInfoModel_(new FileInfoModel()){
    ui->setupUi(this);
    ui->treeView_files->setModel(fileInfoModel_.get());

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
    fileInfoModel_->setItems(data.filesInfo);
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

void TreeTextView::on_pushButton_addFile_clicked() {
    if (!toTreeItem(ui->treeView->currentIndex()))
        return;
    QString nameDocument = QFileDialog::getOpenFileName(this,
                                            tr("Open project file"), "./", tr("Files (*.doc *.pdf)"));
    QFile file(nameDocument);
    file.open(QIODevice::ReadOnly);
    auto dataFile = file.readAll();
    controller_->saveFile(currentTreeItem()->key(), nameDocument.section("/", -1), std::move(dataFile));
}

void TreeTextView::on_pushButton_deleteFile_clicked() {
    auto treeItem = toTreeItem(ui->treeView->currentIndex());
    if (!treeItem)
        return;

    auto index = ui->treeView_files->currentIndex();
    auto nameFile = index.data().toString();
    controller_->deleteFile(treeItem->key(), nameFile);
}

void TreeTextView::on_pushButton_openFiel_clicked() {
    auto treeItem = toTreeItem(ui->treeView->currentIndex());
    if (!treeItem)
        return;

    auto index = ui->treeView_files->currentIndex();
    if (index == QModelIndex()) {
        return;
    }
    auto indexFileName = index.sibling(index.row(), 0);
    auto nameFile = indexFileName.data().toString();
    controller_->openFile(treeItem->key(), nameFile);
}
