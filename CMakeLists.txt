cmake_minimum_required(VERSION 3.6.0)
project(sxwnl-cpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options(-DWIN32)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -s -fexceptions")
    message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src)
add_subdirectory(test)