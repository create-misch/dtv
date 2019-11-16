project (log4app)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core)

if (NOT 3RDPARTY_DIR)
    set(3RDPARTY_DIR "../../3rdparty")
endif()
set(LOG4QT_DIR "${3RDPARTY_DIR}/log4qt/")

aux_source_directory(./ SRC_LIST)
aux_source_directory(${LOG4QT_DIR} SRC_LOG4QT_LIST)
aux_source_directory(${LOG4QT_DIR}/helpers SRC_LOG4QT_LIST)
aux_source_directory(${LOG4QT_DIR}/spi SRC_LOG4QT_LIST)
aux_source_directory(${LOG4QT_DIR}/varia SRC_LOG4QT_LIST)

set(PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/log4app)
file(GLOB HEADERS
    "${LOG4QT_DIR}/*.h"
    "${LOG4QT_DIR}/helpers/*.h"
    "${LOG4QT_DIR}/spi/*.h"
    "${LOG4QT_DIR}/varia/*.h"
    "${INCLUDE_DIR}/*.h")

add_library(${PROJECT_NAME} ${TYPE_BUILD} ${SRC_LIST} ${SRC_LOG4QT_LIST} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${3RDPARTY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} Qt5::Core  configmanager)
