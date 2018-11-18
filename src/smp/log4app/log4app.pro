PROJECTNAME=liblog4app

include(../../global.pri)

TEMPLATE = lib
TARGET = log4app$${POST}

include(../../options.pri)

DEFINES += LIBLOG4APP_LIB
CONFIG(staticlib) {
    DEFINES += LIBLOG4APP_LIB_STATICLIB LOG4QT_LIB_STATICLIB
}

QT       += core
QT      -= widgets

#подключаемые библиотеки
LIBS += -lconfigmanager$${POST}

INCLUDEPATH += $$top_srcdir/3rdparty

project_includedir=$$top_includedir
INCLUDEPATH += $$project_includedir
libheaders.path = $$top_installdir/$$root_prefix_dev/include/$${PROJECTNAME}/
libheaders.files =                                      \
    $$project_includedir/log4app/export.h        \
    $$project_includedir/log4app/log4app.h

HEADERS  +=                                                 \
    $${libheaders.files}                                    \
    listmodel.h                                             \
    $$project_includedir/log4app/widgetappender.h

include($$top_srcdir/3rdparty/log4qt/log4qt.pri)
    
#исходники
SOURCES +=                      \
    log4app.cpp                 \
    widgetappender.cpp


subprojectroot_dir=$$PWD
include(../../cppcheck.pri)
DOXPROJECT=logger
include(../../doxygen.pri)
