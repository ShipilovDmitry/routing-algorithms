set  (SRCS
    dijkstra.cpp
)

add_library(dijkstra ${SRCS})

target_link_libraries(${PROJECT_NAME} dijkstra)
