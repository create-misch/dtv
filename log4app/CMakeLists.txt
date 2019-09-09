project (log4app)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core)

if (NOT 3RDPARTY_DIR)
    set(3RDPARTY_DIR "../3rdparty")
endif()
set(LOG4QT_DIR "${3RDPARTY_DIR}/log4qt")

aux_source_directory(./ SRC_LIST)
aux_source_directory(${LOG4QT_DIR} SRC_LOG4QT_LIST)

add_library(${PROJECT_NAME} ${SRC_LIST} ${SRC_LOG4QT_LIST})

target_include_directories(${PROJECT_NAME} PRIVATE ${3RDPARTY_DIR})
target_link_libraries(${PROJECT_NAME} Qt5::Core)
