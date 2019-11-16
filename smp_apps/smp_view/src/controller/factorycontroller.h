#pragma once

#include <QString>

#include <common/global.h>

#include <model/observer.h>
#include <model/datastoragemain.h>

#include <controller/controllermain.h>

namespace libsmp {

class FactoryController {
public:
    static sp<ControllerInterface> createController(Observer* observer, const QString nameProject) {
        auto model = std::make_shared<DataStorageMain>(nameProject);
        auto controller = std::make_shared<ControllerMain>(model);

        controller->addChildObject(0);
        controller->setNameForObject(0, nameProject);

        model->addObserver(observer);

        return controller;
    }

    static sp<ControllerInterface> createControllerFromStorage(Observer* observer,
                                                               const QString fileStorage) {
        auto model = std::make_shared<DataStorageMain>(fileStorage);
        auto controller = std::make_shared<ControllerMain>(model);

        model->addObserver(observer);

        return controller;
    }
};

}
