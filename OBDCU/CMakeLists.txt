cmake_minimum_required(VERSION 2.6)
project(OBDCU)

set(build CMAKE_SOURCE_DIRECTORY/build)
file(MAKE_DIRECTORY ${directory})
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${directory})

set(CMAKE_CXX_FLAGS "-g -Wall")
add_subdirectory(src)

add_executable(OBDCU src/Main.cpp)

target_link_libraries(OBDCU View) #Model Controller)
