cmake_minimum_required(VERSION 2.6)
project(SandBox)

#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory build)

set(CMAKE_CXX_FLAGS "-g -Wall")
add_subdirectory(src)

add_executable(SandBox 
      src/Main.cpp
      src/uart.cpp)

include_directories(/usr/local/include/)
link_directories(/usr/local/lib)
add_library(libusb_vhci src/Main.cpp)

#target_link_libraries(lsd_obj_rec_ransac ${PCL_LIBRARIES} ${Boost_LIBRARIES}) 
# link the libraries to the executable
target_link_libraries (SandBox libusb_vhci.so)
