#include <QInputDialog>
#include <QFileDialog>

#include <log4app/log4app.h>
#include <controller/factorycontroller.h>

#include "treetextview.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

void InstallTranslator(TranslatorList* list, const QString& filename) {
    QTranslator* tr(new QTranslator);
    const bool load = tr->load(filename);
    if (!load) {
        log4app::Log()->warn("Can't load translation from file : %1", filename);
        delete tr;
        return;
    }
    qApp->installTranslator(tr);
    list->push_back(tr);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    InstallTranslator(&translatorList_, ":/translations/smp-gui_ru.qm");

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested,[this] (int index) {
            delete ui->tabWidget->widget(index);
            ui->tabWidget->removeTab(index);
    });

    connect(ui->actionCreate_Project, &QAction::triggered, this, [this] () {
        QString nameProject = QInputDialog::getText(this, tr("Create project"),
                                                    tr("Name project"));
        if (nameProject.isEmpty()) {
            return;
        }
        auto treeTextView = new TreeTextView;
        auto controller = libsmp::FactoryController::createController(treeTextView, nameProject);
        treeTextView->setController(controller);
        controller->requestObject(0);
        controller->requestDataForObject(0);

        ui->tabWidget->addTab(treeTextView, nameProject);
    });

    connect(ui->actionLoad_Project, &QAction::triggered, this, [this] () {
        QString nameProjectFile = QFileDialog::getOpenFileName(this,
                                                tr("Open project file"), "./", tr("Image Files (*.smp)"));
        if (nameProjectFile.isEmpty()) {
            return;
        }
        auto treeTextView = new TreeTextView;
        auto controller = libsmp::FactoryController::createControllerFromStorage(treeTextView,
                                                                                 nameProjectFile);
        treeTextView->setController(controller);
        controller->requestObject(0);
        controller->requestDataForObject(0);

        ui->tabWidget->addTab(treeTextView, nameProjectFile.section("/", -1).section(".", 0, 0));
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

