cmake_minimum_required(VERSION 2.6)
project(OBDCU)


set(CMAKE_CXX_FLAGS "-g -Wall")
add_subdirectory(src)

add_library(OBDCU src/Main.cpp)

target_link_libraries(OBDCU src)
