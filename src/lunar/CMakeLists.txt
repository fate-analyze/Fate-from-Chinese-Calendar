file(GLOB SRCS "*.cpp")

add_library(lunar ${SRCS})
target_include_directories(lunar PUBLIC
        .
)