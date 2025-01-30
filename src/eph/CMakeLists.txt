file(GLOB SRCS "*.cpp")

add_library(eph ${SRCS})
target_include_directories(eph PUBLIC
        .
)