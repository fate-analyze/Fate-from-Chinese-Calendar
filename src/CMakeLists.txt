add_subdirectory(eph)
add_subdirectory(lunar)
add_subdirectory(mylib)
add_subdirectory(util)

add_library(${PROJECT_NAME}_src OBJECT
    TimeGeo.cpp
)
target_sources(${PROJECT_NAME}_src PUBLIC
    $<TARGET_OBJECTS:${PROJECT_NAME}_eph>
    $<TARGET_OBJECTS:${PROJECT_NAME}_lunar>
    $<TARGET_OBJECTS:${PROJECT_NAME}_mylib>
    $<TARGET_OBJECTS:${PROJECT_NAME}_util>
)