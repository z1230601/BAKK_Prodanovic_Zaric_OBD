cmake_minimum_required(VERSION 2.6)
project(SandBox)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0")

add_subdirectory(src)
add_subdirectory(test)

# Find requried external libraries
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS thread system filesystem REQUIRED)

#reset CMAKE MOdule path for special find scripts
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
MESSAGE( STATUS "CMAKE_MODULE_PATH:         " ${CMAKE_MODULE_PATH} )
find_package(libusb-1.0 REQUIRED)
find_package(CppUnit REQUIRED)
find_package(libusb_vhci REQUIRED)

# find all cpp files in src dir and set internal Cmake variable EXECS
FILE(GLOB_RECURSE EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)
message(STATUS "without main: " ${EXECS})
#add found cpp to one executable named SandBox
add_executable(SandBox 
                 src/Main.cpp 
                 ${EXECS})

#Make also shared library out of found cpps and set internal CMAKE VAR
#add_library(SandBoxLib SHARED ${EXECS})
#set(SRC_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/build/libSandBoxLib.so)

# link the libraries to the executable (most of them found by cmake modules)
target_link_libraries (SandBox 
         ${CMAKE_THREAD_LIBS_INIT}
         ${Boost_LIBRARIES}
         ${LIBUSB_1_LIBRARIES}
         ${LIBUSB_VHCI_LIBRARIES})

##Testing        ##############################################################
include(CTest)

FILE(GLOB UnitTests_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

MESSAGE( STATUS "looking in:         " ${CMAKE_CURRENT_SOURCE_DIR}/test/ )

ADD_EXECUTABLE(UnitTester 
     ${UnitTests_SRCS})

target_link_libraries(UnitTester
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${CPPUNIT_LIBRARIES}
                      ${CMAKE_DL_LIBS}
                      ${SRC_LIBRARY}
                      )

message(STATUS " test to be added: " ${UnitTests_SRCS})
FOREACH(test ${UnitTests_SRCS})
        GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
        ADD_TEST(${TestName} UnitTester ${TestName})
ENDFOREACH(test)
