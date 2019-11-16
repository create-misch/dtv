project (configmanager)

cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core)

aux_source_directory(./ SRC_LIST)

add_library(${PROJECT_NAME} ${TYPE_BUILD} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_include_directories(${PROJECT_NAME} PUBLIC ./)
