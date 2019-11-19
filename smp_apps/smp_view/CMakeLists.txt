project (smp-view)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SRC_DIR ./src)
set(COMMON_DIR ${SRC_DIR}/common)
set(CONTROLLER_DIR ${SRC_DIR}/controller)
set(MODEL_DIR ${SRC_DIR}/model)
set(UI_DIR ${SRC_DIR}/ui)
set(TREE_DIR ${UI_DIR}/tree)
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(TRANSLATIONS_DIR ${RESOURCES_DIR}/translations)

list(APPEND SRC_LIST
    ${SRC_DIR}/main.cpp
    ${COMMON_DIR}/global.h
    ${CONTROLLER_DIR}/controllerinterface.h
    ${CONTROLLER_DIR}/controllermain.cpp
    ${CONTROLLER_DIR}/controllermain.h
    ${CONTROLLER_DIR}/factorycontroller.h
    ${MODEL_DIR}/cachestorage.h
    ${MODEL_DIR}/cachestorage.cpp
    ${MODEL_DIR}/data.h
    ${MODEL_DIR}/database.h
    ${MODEL_DIR}/database.cpp
    ${MODEL_DIR}/datastorageinterface.h
    ${MODEL_DIR}/datastoragemain.h
    ${MODEL_DIR}/datastoragemain.cpp
    ${MODEL_DIR}/hardstorageinterface.h
    ${MODEL_DIR}/hardstoragedb.h
    ${MODEL_DIR}/hardstoragedb.cpp
    ${MODEL_DIR}/nodeinterface.h
    ${MODEL_DIR}/node.h
    ${MODEL_DIR}/node.cpp
    ${MODEL_DIR}/nodetree.h
    ${MODEL_DIR}/nodetree.cpp
    ${MODEL_DIR}/observer.h
    ${MODEL_DIR}/packer.h
    ${UI_DIR}/fileinfomodel.h
    ${UI_DIR}/fileinfomodel.cpp
    ${UI_DIR}/mainwindow.h
    ${UI_DIR}/mainwindow.cpp
    ${UI_DIR}/treeitem.h
    ${UI_DIR}/treeitem.cpp
    ${UI_DIR}/treemodel.h
    ${UI_DIR}/treemodel.cpp
    ${UI_DIR}/treetextview.h
    ${UI_DIR}/treetextview.cpp
    ${TREE_DIR}/tree_node.h
    ${TREE_DIR}/tree_node.cpp
    ${TREE_DIR}/itree_display_presenter.h
    ${TREE_DIR}/itree_display_view.h
    ${TREE_DIR}/tree_display_presenter.h
    ${TREE_DIR}/tree_display_presenter.cpp
    ${TREE_DIR}/tree_display_view.cpp
    ${TREE_DIR}/tree_display_view.h
    ${TREE_DIR}/tree_display_item.cpp
    ${TREE_DIR}/tree_display_item.h)

file(GLOB FORMS ${UI_DIR}/*.ui)
file(GLOB QRC_FILES ${RESOURCES_DIR}/*.qrc)
file(GLOB QM_FILES ${TRANSLATIONS_DIR}/*.qm)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${FORMS} ${HEADERS} ${QRC_FILES} ${QM_FILES})

find_package(Qt5 COMPONENTS Widgets Core Sql)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::Core
    Qt5::Sql
    log4app
    configmanager)

target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})
