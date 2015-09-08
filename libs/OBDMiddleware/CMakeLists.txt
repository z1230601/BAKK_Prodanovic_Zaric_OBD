cmake_minimum_required(VERSION 2.6)
project(OBDMiddleware)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-g -Wall")

# add sub-parts
add_subdirectory(communication)
