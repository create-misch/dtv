#pragma once

#include <QMainWindow>

#include <global.h>
#include <model/observer.h>

namespace Ui {
class MainWindow;
}

namespace libsmp {
struct Object;
class ControllerInterface;
}

class MainWindow : public QMainWindow, public libsmp::Observer {
    Q_OBJECT
public:
    explicit MainWindow(libsmp::sp<libsmp::ControllerInterface> controller, QWidget *parent = 0);
    ~MainWindow();

    void updateDescription(const QString &description) override final;
    void updateRequestedObject(const libsmp::Object &object) override final;

private:
    libsmp::sp<libsmp::ControllerInterface> controller_;
    Ui::MainWindow *ui;


};

