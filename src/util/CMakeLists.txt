file(GLOB ERFA_SRC_FILES
    "erfa/src/*.cpp"
    "erfa/src/*.c"
)
# exclude test parts
list(FILTER ERFA_SRC_FILES EXCLUDE REGEX ".*/t_erfa_c.c")
list(FILTER ERFA_SRC_FILES EXCLUDE REGEX ".*/t_erfa_c_extra.c")
list(FILTER ERFA_SRC_FILES EXCLUDE REGEX ".*/erfaversion.c")

add_library(${PROJECT_NAME}_util OBJECT
    ${ERFA_SRC_FILES}
    TimeUtil.cpp
    DataUtil.cpp
)
target_include_directories(${PROJECT_NAME}_util PRIVATE
    erfa/src
)
