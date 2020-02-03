project (database)

cmake_minimum_required(VERSION 3.10)

find_package(Qt5 COMPONENTS Core Sql)

file(GLOB_RECURSE HEADERS include/*.h)

add_library(${PROJECT_NAME} ${TYPE_BUILD}
    ${HEADERS}
    src/database_connector.cpp
    src/database_connector.h
    src/database_query.cpp
    src/database_query.h
    src/database.cpp
    src/database.h
    )

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core
    Qt5::Sql
    log4app
    )
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)

add_subdirectory(tests)
