# You have to set PROJECTNAME variable!
isEmpty(PROJECTNAME){
    error("You have to set PROJECTNAME variable!")
}
isEmpty(top_srcdir): top_srcdir=$$PWD

CONFIG += qt
#CONFIG += debug_and_release

macx {
    CONFIG -= app_bundle
    CONFIG -= lib_bundle
}


CONFIG(release, debug|release):POST        =
CONFIG(release, debug|release):build_postfix=release

CONFIG(debug, debug|release):POST          =d
CONFIG(debug, debug|release):build_postfix=debug


win32 {
garbage_subdir=win
}
unix {
    garbage_subdir=unix

    android {
        garbage_subdir=android/$$ANDROID_TARGET_ARCH
    }
}


win32|android* {
#    TEMP_DIR=$$(TEMP)
#    isEmpty(TEMP_DIR) {
#        error("Not set enviroment variable TEMP")
#    }
#    pwd_=$$PWD
#    subdir=$$replace(pwd_, :, '')
#    top_garbagedir=$$TEMP_DIR/garbage/$$subdir
    top_garbagedir=$$top_srcdir/../garbage/$$garbage_subdir
}
!android-g++ {
    !win32 {
        TEMP_DIR=/tmp/
        top_garbagedir=$$TEMP_DIR/garbage/$$garbage_subdir/$$PWD
    }
}

top_builddir=$$top_garbagedir/$$build_postfix
isEmpty(debug_dest_dir) {

    exists($$top_srcdir/../../../submodules) {
        top_destdir=$$top_srcdir/../../../bin
    } else {
        top_destdir=$$top_srcdir/../bin
    }

} else {
    top_destdir=$$debug_dest_dir
}
top_includedir=$$top_srcdir/include
INCLUDEPATH += $$top_includedir
INCLUDEPATH += $$top_includedir/libsmp

!win32 {
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib
}

projectroot_dir=$$top_srcdir/..
projectroot_includedir=$$projectroot_dir/include
projectroot_libdir=$$projectroot_dir/lib

android {
    equals(ANDROID_TARGET_ARCH, x86) {
        top_installdir = /libs/x86
    } else: equals(ANDROID_TARGET_ARCH, armeabi-v7a) {
        top_installdir = /libs/armeabi-v7a
    } else {
        top_installdir = /libs/armeabi
    }
} else:unix {
    top_installdir=$$(DESTDIR)
}

win32 {
    top_installdir=$$top_garbagedir/install
}
unix {
    top_installdir=$$(DESTDIR)
}

top_submodulesdir=$$top_srcdir/../submodules
!isEmpty(SUBMODULES) {
    for(module, SUBMODULES) {
        INCLUDEPATH += $$top_submodulesdir/$$module/src/include/
        INCLUDEPATH += $$top_submodulesdir/$$module/include/
    }
}

builddir=$$top_builddir/$${PROJECTNAME}/

RCC_DIR=$$builddir
OBJECTS_DIR=$$builddir
MOC_DIR=$$builddir
DESTDIR=$$top_destdir
UI_DIR = $$builddir/ui

LIBS += -L$$top_destdir
linux{
    # Третьяк: Следующая строчка ломает запуск приложений на MacOS X
    QMAKE_RPATHDIR += $$top_destdir
}

#Третьяк: форсируем Unicode. Вопрос - это только для Win32???
#DEFINES += UNICODE
CONFIG(debug, debug|release):DEFINES += _DEBUG

exists(global.local.pri) {
   include(global.local.pri)
}

