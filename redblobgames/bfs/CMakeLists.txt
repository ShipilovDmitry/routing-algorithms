set  (SRCS
    bfs.cpp
)

add_library(bfs ${SRCS})
target_include_directories(bfs PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} bfs)
