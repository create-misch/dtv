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
    model->addObserver(window);

#ifdef _DEBUG
    controller->addChildObject(std::string());
    controller->setDescriptionForObject(std::string("a"),"lol1 ");
    controller->setNameForObject(std::string("a"),"lol");

    controller->addChildObject(std::string("a"));
    controller->setDescriptionForObject(std::string("ab"),"lol1 ");
    controller->setNameForObject(std::string("ab"),"lol1");

    controller->addChildObject(std::string("a"));
    controller->setDescriptionForObject(std::string("ac"),"lol2");
    controller->setNameForObject(std::string("ac"),"lol2");

    controller->addChildObject(std::string("ab"));
    controller->setDescriptionForObject(std::string("abd"),"lol3");
    controller->setNameForObject(std::string("abd"),"lol3");
#endif
    window->show();

    return a.exec();
}
