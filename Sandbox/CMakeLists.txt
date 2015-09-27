cmake_minimum_required(VERSION 2.6)
project(SandBox)

#execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory build)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0")

add_subdirectory(src)
add_subdirectory(test)

add_executable(SandBox 
      src/Main.cpp
      src/UartDevice.cpp
      src/SerialCommunication.cpp)

add_library(libusb_vhci src/Main.cpp)

MESSAGE( STATUS "CMAKE_MODULE_PATH:         " ${CMAKE_MODULE_PATH} )

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS thread system REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
MESSAGE( STATUS "CMAKE_MODULE_PATH:         " ${CMAKE_MODULE_PATH} )
find_package(libusb-1.0 REQUIRED)
find_package(CppUnit REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(/usr/local/include/)
link_directories(/usr/local/lib)

#target_link_libraries(lsd_obj_rec_ransac ${PCL_LIBRARIES} ${Boost_LIBRARIES}) 
# link the libraries to the executable
target_link_libraries (SandBox 
         libusb_vhci.so 
         ${CMAKE_THREAD_LIBS_INIT}
         ${Boost_LIBRARIES}
         ${LIBUSB_1_LIBRARIES})

enable_testing()
