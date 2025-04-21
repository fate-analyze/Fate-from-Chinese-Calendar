enable_testing()
set(GTEST_LIBRARY /usr/local/lib/gtest)
set(GTEST_INCLUDE_DIRS /usr/local/include/gtest)

add_executable(${PROJECT_NAME}_ut
    UTMain.cpp
    util/TimeUtilTest.cpp
    util/DataUtilTest.cpp
)
target_include_directories(${PROJECT_NAME}_ut PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${GTEST_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(${PROJECT_NAME}_ut PRIVATE
    ${PROJECT_NAME}_src
    gtest
    gtest_main
    pthread
)


add_executable(${PROJECT_NAME}_st
    STMain.cpp
)
target_link_libraries(${PROJECT_NAME}_st PRIVATE ${PROJECT_NAME}_src)