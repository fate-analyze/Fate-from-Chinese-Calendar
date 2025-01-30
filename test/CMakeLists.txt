add_executable(test1 test1.cpp)
target_link_libraries(test1 PRIVATE eph lunar mylib)
target_include_directories(test1 PRIVATE
        ${CMAKE_SOURCE_DIR}/eph
        ${CMAKE_SOURCE_DIR}/lunar
        ${CMAKE_SOURCE_DIR}/mylib
)