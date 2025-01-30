file(GLOB SRCS "*.cpp")

add_library(mylib ${SRCS})
target_include_directories(mylib PUBLIC
        .
)