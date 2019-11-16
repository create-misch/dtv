#pragma once

#include <QMainWindow>
#include <QTranslator>

#include <common/global.h>
#include <model/observer.h>

namespace Ui {
class MainWindow;
}

using TranslatorList = QVector<QTranslator*>;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TranslatorList translatorList_;
};

