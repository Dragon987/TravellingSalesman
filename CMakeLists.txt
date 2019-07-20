cmake_minimum_required(VERSION 3.14)
project(TravellingSalesman VERSION 1.0)

add_executable(
    app
    ./src/main.cpp
)

target_link_libraries(
    app
    -lengine
    -lMath
)