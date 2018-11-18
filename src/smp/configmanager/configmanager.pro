# Определение проекта
PROJECTNAME=configmanager

# Глобальные настройки
include(../../global.pri)

# Тип проекта
TEMPLATE = lib

# Имя собираемого модуля
TARGET = configmanager$${POST}

# Опции сборки
include(../../options.pri)

# Настройки QT
QT += core network
QT += gui
android: QT += androidextras

# Определения препроцессора
CONFIG(staticlib) {
    DEFINES += CONFIGMANAGER_LIB_STATICLIB
} else {
    DEFINES += CONFIGMANAGER_LIB
}

# Подключаемые библиотеки

project_includedir=$$top_includedir
INCLUDEPATH += $$project_includedir
# Экспортируемые заголовочные файлы
libheaders.path = $$top_installdir/$$root_prefix_dev/include/$${PROJECTNAME}/
libheaders.files =                                                  \
    $$project_includedir/configmanager/configmanager.h              \
    $$project_includedir/configmanager/configmanager_export.h       \
    $$project_includedir/configmanager/settings.h

# Заголовочные файлы
HEADERS  += $${libheaders.files}


# Исходники
SOURCES +=                                  \
    configmanager.cpp                       \
    settings.cpp

# Документирование
#subprojectroot_dir=$$PWD
#DOXPROJECT=configmanager
#include(../../doxygen.pri)
