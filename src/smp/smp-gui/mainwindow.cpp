#include <controller/controllerinterface.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(libsmp::sp<libsmp::ControllerInterface> controller, QWidget *parent) :
    QMainWindow(parent),
    controller_(controller),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    controller_->addChildObject(std::string());
    controller_->setDescriptionForObject(std::string(),"fdsfsd asdf asdf asdfasdf asdf ");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateDescription(const QString &description) {
    ui->textBrowser->setText(description);
}

void MainWindow::updateRequestedObject(const libsmp::Object &object) {
    Q_UNUSED(object)
}
