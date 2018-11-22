#pragma once

#include <QMainWindow>

#include <global.h>
#include <model/observer.h>

namespace Ui {
class MainWindow;
}

namespace libsmp {
class NodeInterface;
class ControllerInterface;
}

class TreeModel;

class MainWindow : public QMainWindow, public libsmp::Observer {
    Q_OBJECT
public:
    explicit MainWindow(libsmp::sp<libsmp::ControllerInterface> controller, QWidget *parent = 0);
    ~MainWindow();

    void updateDescription(const QString &description) override final;
    void updateRequestedObject(const libsmp::NodeInterface *node) override final;

private slots:
    void on_pushButton_addChildren_clicked();
    void on_pushButton_SaveDescription_clicked();

private:
    libsmp::sp<libsmp::ControllerInterface> controller_;
    libsmp::sp<TreeModel> model_;
    Ui::MainWindow *ui;


};

