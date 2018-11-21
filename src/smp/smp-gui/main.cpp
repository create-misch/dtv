#include "mainwindow.h"
#include <QApplication>

#include <model/modelmain.h>
#include <controller/controllermain.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    using namespace libsmp;
    auto model = std::make_shared<ModelMain>();

    auto controller = std::make_shared<ControllerMain>(model);

    auto window = std::make_shared<MainWindow>(controller);
    window->show();

    return a.exec();
}
