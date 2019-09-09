project (smp-gui)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets)

aux_source_directory(./ SRC_LIST)
file(GLOB FORMS "./*.ui")
file(GLOB HEADERS "./*.h")

file(GLOB QRC_FILES "./*.qrc")
file(GLOB QM_FILES "./translations/*.qm")

add_executable(${PROJECT_NAME} ${SRC_LIST} ${FORMS} ${HEADERS} ${QRC_FILES} ${QM_FILES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets libsmp)
