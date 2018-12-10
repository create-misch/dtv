#pragma once

#include <QString>

#include <global.h>

#include <model/observer.h>
#include <model/datastoragemain.h>

#include <controller/controllermain.h>

namespace libsmp {

class FactoryController {
public:
    static sp<ControllerInterface> createController(Observer* observer, const QString nameProject) {
        auto model = std::make_shared<ModelMain>();
        auto controller = std::make_shared<ControllerMain>(model);

        controller->addChildObject(std::string());
        controller->setNameForObject(std::string("a"), nameProject);

        model->addObserver(observer);

        return controller;
    }
};

}
