CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(CommunicationInterface)
SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0")

IF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64") 
  ADD_DEFINITIONS(-fPIC) 
ENDIF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
INCLUDE_DIRECTORIES(includes)
# Find requried external libraries
FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(Boost COMPONENTS thread system REQUIRED)

#reSET CMAKE MOdule path for special find scripts
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
MESSAGE( STATUS "CMAKE_MODULE_PATH:         " ${CMAKE_MODULE_PATH} )
FIND_PACKAGE(libusb-1.0 REQUIRED)
FIND_PACKAGE(CppUnit REQUIRED)
FIND_PACKAGE(libusb_vhci REQUIRED)


# find all cpp files in src dir and SET internal Cmake variable EXECS
FILE(GLOB_RECURSE EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)
#message(STATUS "without main: " ${EXECS})


#Make also shared library out of found cpps and SET internal CMAKE VAR
ADD_LIBRARY(serial-communication-dev STATIC ${EXECS})

SET(LIBRARY_NAME "libserial-communication-dev.a")
FILE(GLOB_RECURSE dev_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# link the libraries to the executable (most of them found by cmake modules)
target_link_libraries (serial-communication-dev 
         ${CMAKE_THREAD_LIBS_INIT}
         ${Boost_LIBRARIES}
         ${LIBUSB_1_LIBRARIES}
         ${LIBUSB_VHCI_LIBRARIES})

GET_PROPERTY(serial_communication_location TARGET serial-communication-dev PROPERTY LOCATION)
MESSAGE (STATUS "seiarl_lib_location == ${serial_communication_location} linking to ${OBDMiddleware_SOURCE_DIR}/")

ADD_CUSTOM_COMMAND(TARGET serial-communication-dev 
   POST_BUILD
   COMMAND ln -s -f ${serial_communication_location} ${LIBRARY_NAME}
   COMMAND mkdir -p middleware_includes
   COMMAND ln -s -f ${dev_INCLUDES} middleware_includes/.
   WORKING_DIRECTORY "${OBDMiddleware_SOURCE_DIR}/"
)


###### Install & Packaging #####
SET(INSTALL_DIR "/usr/lib/")
INSTALL(TARGETS
   serial-communication-dev
   DESTINATION ${INSTALL_DIR}
)

SET(include_INSTALL_DIR /usr/includes/OBDMiddleware/)


#Install includes into dir
INSTALL(FILES
  ${dev_INCLUDES}
  DESTINATION ${include_INSTALL_DIR}
)

##Testing        ##############################################################
INCLUDE(CTest)

FILE(GLOB UnitTests_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

MESSAGE( STATUS "looking in:         " ${CMAKE_CURRENT_SOURCE_DIR}/test/ )

ADD_EXECUTABLE(CommunicationTester 
     ${UnitTests_SRCS})

TARGET_LINK_LIBRARIES(CommunicationTester
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${CPPUNIT_LIBRARIES}
                      ${CMAKE_DL_LIBS}
                      ${LIBUSB_1_LIBRARIES}
                      ${LIBUSB_VHCI_LIBRARIES}
                      serial-communication-dev
                      )

FOREACH(test ${UnitTests_SRCS})
        GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
        ADD_TEST(${TestName} CommunicationTester ${TestName})
ENDFOREACH(test)
