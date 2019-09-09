project (libsmp)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Sql Gui)

aux_source_directory(./ SRC_LIST)
file(GLOB HEADERS "./include/*.h" "./include/*/*.h")
file(GLOB QRC_FILES "./*.qrc")
file(GLOB QM_FILES "./translations/*.qm")

add_library(${PROJECT_NAME} ${SRC_LIST} ${HEADERS} ${QRC_FILES} ${QM_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Sql Qt5::Gui log4app)

target_include_directories(${PROJECT_NAME} PUBLIC ./include)
