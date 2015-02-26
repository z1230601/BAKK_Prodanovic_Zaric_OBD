cmake_minimum_required(VERSION 2.6)
project(OBDCU)

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory build)

set(CMAKE_CXX_FLAGS "-g -Wall")
add_subdirectory(src)

add_executable(OBDCU src/Main.cpp)

target_link_libraries(OBDCU View) #Model Controller)
