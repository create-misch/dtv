# Определение проекта
PROJECTNAME=libsmp

# Глобальные настройки
include(../../global.pri)

# Тип проекта
TEMPLATE = lib

# Имя собираемого модуля
TARGET = smp$${POST}

# Опции сборки
include(../../options.pri)

# Настройки QT
QT += core sql

# Подключаемые библиотеки

include(../../log4app.pri)

LIBS += -lconfigmanager$${POST}

libsmp_includedir = $$top_includedir/libsmp
INCLUDEPATH += $$top_includedir
# Экспортируемые заголовочные файлы
libheaders.path = $$top_installdir/$$root_prefix_dev/include/$${PROJECTNAME}/
libheaders.files =                                                  \
    $$libsmp_includedir/global.h\
    $$libsmp_includedir/model/nodeinterface.h \
    $$libsmp_includedir/model/prefixtree.h \
    $$libsmp_includedir/model/prefixnode.h \
    $$libsmp_includedir/model/datastorageinterface.h \
    $$libsmp_includedir/model/datastoragemain.h \
    $$libsmp_includedir/model/observer.h \
    $$libsmp_includedir/model/node.h \
    $$libsmp_includedir/model/nodetree.h \
    $$libsmp_includedir/model/data.h \
    $$libsmp_includedir/controller/controllerinterface.h \
    $$libsmp_includedir/controller/controllermain.h \    
    $$libsmp_includedir/controller/factorycontroller.h \



# Заголовочные файлы
HEADERS  += $${libheaders.files} \
    ../../include/libsmp/model/hardstorageinterface.h \
    ../../include/libsmp/model/hardstoragedb.h \
    ../../include/libsmp/model/database.h

# Исходники
SOURCES += \
    controller/controllermain.cpp \
    model/node.cpp \
    model/nodetree.cpp \
    model/datastoragemain.cpp \
    model/hardstoragedb.cpp \
    ../../include/libsmp/model/database.cpp

DISTFILES +=
