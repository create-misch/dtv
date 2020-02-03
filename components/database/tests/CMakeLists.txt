project(gtest_database)

add_executable(${PROJECT_NAME}
    database_query_test.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    gtest
    gtest_main
    database)
