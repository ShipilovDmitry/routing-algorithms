set  (SRCS
    astar.cpp
)

add_library(rbg-astar ${SRCS})
target_include_directories(rbg-astar PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} rbg-astar)
