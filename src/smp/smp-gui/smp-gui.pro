# Определение проекта
PROJECTNAME=smp-gui

# Глобальные настройки
include(../../global.pri)

# Тип проекта
TEMPLATE = app

# Имя собираемого модуля
TARGET = smp-gui$${POST}

# Опции сборки
include(../../options.pri)

# Настройки QT
QT += core widgets

# Подключаемые библиотеки

include(../../log4app.pri)

LIBS += -lconfigmanager$${POST} -lsmp$${POST}

INCLUDEPATH += $$top_includedir
## Экспортируемые заголовочные файлы
#libheaders.path = $$top_installdir/$$root_prefix_dev/include/$${PROJECTNAME}/
#libheaders.files =                                                  \
#    $$top_includedir/libsmp/global.h\
#    $$top_includedir/libsmp/nodeinterface.h

# Заголовочные файлы
HEADERS  += \
    mainwindow.h \
    treeitem.h \
    treemodel.h \
    treetextview.h \
    fileinfomodel.h

# Исходники
SOURCES += \
    mainwindow.cpp\
    main.cpp \
    treeitem.cpp \
    treemodel.cpp \
    treetextview.cpp \
    fileinfomodel.cpp

FORMS += \
    mainwindow.ui \
    treetextview.ui
