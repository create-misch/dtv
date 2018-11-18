isEmpty(top_srcdir){
    error('File global.pri must be include before default.pri')
}

# ===== Windows =====

# ---- Microsoft Visual Studio -----
# Опции, общие для всех Visual Studio
win32-msvc* {

    # Отключаем макросы min и max из windows.h
    DEFINES += NOMINMAX
    CONFIG += c++11

    # оптимизации
    QMAKE_CXXFLAGS_RELEASE += /MP /Os /GL
    QMAKE_CXXFLAGS_RELEASE += /Ox /Ot /GL
    QMAKE_CXXFLAGS += /Oi
    QMAKE_CXXFLAGS_RELEASE += /Qpar
    !contains(QMAKE_HOST.arch, x86_64): QMAKE_CXXFLAGS += /arch:SSE2
    QMAKE_CXXFLAGS += /Qfast_transcendentals /fp:precise

    # параметры сборки
    CONFIG(debug, debug|release):QMAKE_CXXFLAGS += /Gm		#Enable minimal rebuild
    QMAKE_LFLAGS += /LARGEADDRESSAWARE
    QMAKE_LFLAGS_RELEASE += /LTCG
    #QMAKE_CXXFLAGS += /Zc:wchar_t

    # отладочная информация
    CONFIG(debug, debug|release) {
        winpdb=$$top_destdir/$${TARGET}.pdb
        QMAKE_LFLAGS += "/PDB:$$winpdb"
    }

    winimplib=$$top_destdir/$${TARGET}.lib
    LFLAGS = "/IMPLIB:$$winimplib"
}
# Опции только Visual Studio 2012 (кривые компилятор и stl)
win32-msvc2012 {
    #std::tr1::tuple fix for VS2012
    QMAKE_CXXFLAGS += /D_VARIADIC_MAX=10
}
# Опции только для Intel C++ Compiler (не протестировано)
win32-icc {
    DEFINES += _USE_CXX0X_ NOMINMAX
    CONFIG += c++11
    #QMAKE_CXXFLAGS += -Qstd=c++0x
    QMAKE_LFLAGS +=/MACHINE:X64
}

# ---- MinGW -----

# Опции  для MinGW
win32-g++ {
    CONFIG += c++11
    QMAKE_CXXFLAGS += -mfpmath=sse
# -march=native Удалил
}

win32 {
    contains(TEMPLATE, lib) {
        QMAKE_LFLAGS += $$LFLAGS
    } else {
    contains(TEMPLATE, vclib) {
            QMAKE_LFLAGS += $$LFLAGS
        }
    }
    d_suffix=$${POST}
}

# ---- MinGW -----

# Опции  для MinGW
win32-g++ {
    CONFIG += c++11
    QMAKE_CXXFLAGS += -msse -msse2 -msse3 -msse4.1 -msse4.2 -mavx -mfpmath=sse
}

# ===== Unix =====
# ----- Общее для всех -----
unix {
    d_suffix=
    # для сборки dbg пакета отключаем strip на этапе install
    # он будет сделан при сборке пакета
    CONFIG += nostrip
    CONFIG += c++11
}
# ----- GCC для Linux -----
linux-g++* {
    QMAKE_CXXFLAGS += -Werror
    QMAKE_CXXFLAGS += -Woverloaded-virtual -Wnon-virtual-dtor -Wextra
#    QMAKE_CXXFLAGS += -Wold-style-cast
    QMAKE_CXXFLAGS += -std=c++0x -Werror=format-security    
    QMAKE_CXXFLAGS += -fno-strict-aliasing
    QMAKE_CXXFLAGS += -fabi-version=7

    GCC_VERSION = $$system("g++ -dumpversion")
    contains(GCC_VERSION, 7) {
        # В 7 версии gcc выдаёт варнинг на устаревший макрос Qt 5.5.1
        # Выключаем этот варнинг
        lessThan(QT_MAJOR_VERSION, 6) {
            QMAKE_CXXFLAGS += -Wno-expansion-to-defined
        }
        QMAKE_CXXFLAGS += -std=c++1z
    }
}
# ----- Clang для Linux -----
linux-clang* {
    CONFIG += c++11
    QMAKE_CXXFLAGS += -Woverloaded-virtual -Wnon-virtual-dtor -Wextra -Wno-deprecated
    QMAKE_CXXFLAGS += -mfpmath=sse
}
# ----- Intel C++ Compiler для Linux -----
linux-icc* {
    CONFIG += c++11
    QMAKE_CXXFLAGS += -Woverloaded-virtual -Wnon-virtual-dtor
}
# ----- Clang/GCC для Mac OS X -----
macx {
    QMAKE_CXXFLAGS += -Woverloaded-virtual -Wnon-virtual-dtor -Wextra -Wno-deprecated
    QMAKE_CXXFLAGS += -msse -msse2 -msse3 -msse4.1 -msse4.2 -mavx -mfpmath=sse
    #QMAKE_CXXFLAGS += -fopenmp
    #QMAKE_LFLAGS += -fopenmp
}

use-native-arch {
    win32-g++ {
        QMAKE_CXXFLAGS += -march=native
    }
    macx {
        QMAKE_CXXFLAGS += -march=native
    }
    linux-clang* {
        QMAKE_CXXFLAGS += -march=native
    }
    linux-g++* {
        QMAKE_CXXFLAGS += -march=native
    }
}


# ===== Doxygen =====

# пустые цели dox и doxclean
# чтобы можно было делать make dox
dox.target=
doxclean.target=
doxinstall.target=
doxuninstall.target=
QMAKE_EXTRA_TARGETS += dox doxclean doxinstall doxuninstall

exists(version.pri) {
    include(version.pri)
}
