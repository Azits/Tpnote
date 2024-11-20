cmake_minimum_required(VERSION 3.22.1)

project(graphe)
set(SRCS  

    ./main.cpp 
    ./graphe.cpp
    ./element.cpp
    )

set(INCLUDES ./)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
add_executable(graphe ${SRCS})
target_include_directories(graphe PUBLIC ${INCLUDES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb")