#include <QInputDialog>

#include <controller/factorycontroller.h>

#include "treetextview.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,[this] (int index) {
            delete ui->tabWidget->widget(index);
            ui->tabWidget->removeTab(index);
    });

    connect(ui->actionCreate_Project, &QAction::triggered, this, [this] () {
        QString nameProject = QInputDialog::getText(this, tr("Create Project"),
                                                    tr("Name Project"));

        auto treeTextView = new TreeTextView;
        auto controller = libsmp::FactoryController::createController(treeTextView, nameProject);
        treeTextView->setController(controller);
        controller->requestObject(0);
        controller->requestDataForObject(0);

        ui->tabWidget->addTab(treeTextView, nameProject);
    });

    connect(ui->actionLoad_Project, &QAction::triggered, this, [this] () {
        QString nameProjectFile = QInputDialog::getText(this, tr("Load Project"),
                                                    tr("Name Project file"));

        auto treeTextView = new TreeTextView;
        auto controller = libsmp::FactoryController::createControllerFromStorage(treeTextView,
                                                                                 nameProjectFile);
        treeTextView->setController(controller);
        controller->requestObject(0);
        controller->requestDataForObject(0);

        ui->tabWidget->addTab(treeTextView, nameProjectFile.section("/", -1));
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

