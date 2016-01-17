CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(OBDCU)

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

IF(NOT DEFINED Middleware_SOURCE_PATH)
   SET(Middleware_SOURCE_PATH "/usr/lib/")
ENDIF(NOT DEFINED Middleware_SOURCE_PATH)

IF(DEFINED Middleware_BASE_PATH)
   INCLUDE_DIRECTORIES("${Middleware_BASE_PATH}/middleware_includes")
   FILE(GLOB_RECURSE middleware_dynamic_libraries ${Middleware_BASE_PATH}/*.so)
   FILE(GLOB_RECURSE middleware_static_libraries ${Middleware_BASE_PATH}/*.a)
ELSE(DEFINED Middleware_BASE_PATH)
   IF(EXISTS "/usr/includes/OBDMiddleware/")
     INCLUDE_DIRECTORIES("/usr/includes/OBDMiddleware/")
     SET(middleware_dynamic_libraries "/usr/lib/libdatabase-connection-manager-dev.so")
     SET(middleware_static_libraries "/usr/lib/libserial-communication-dev.a")
   ELSE(EXISTS "/usr/includes/OBDMiddleware/")
     MESSAGE(FATAL_ERROR "No middleware libraries found or specified. Please Specify under Middleware_BASE_PATH for compiled linking or else install the libraries and make sure the are under /usr/lib/ and /usr/include/OBDMiddleware")
   ENDIF(EXISTS "/usr/includes/OBDMiddleware/")
ENDIF(DEFINED Middleware_BASE_PATH)

###############################################################################################
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
MESSAGE( STATUS "CMAKE_MODULE_PATH:         " ${CMAKE_MODULE_PATH} )
FIND_PACKAGE(CppUnit REQUIRED)
FIND_PACKAGE(Xml++ REQUIRED)
FIND_PACKAGE(MySQLConnectorCPP REQUIRED)


INCLUDE_DIRECTORIES(includes)
INCLUDE_DIRECTORIES(${LibXML++_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${MYSQLCONNECTORCPP_INCLUDE_DIRS})
###############################################################################################

#libdatabase-connection-manager-dev.so  libserial-communication-dev.a

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

FIND_PACKAGE(Qt4 REQUIRED)

LIST(APPEND OBDCU_EXECUTABLES "src/Main.cpp")
LIST(APPEND OBDCU_INCLUDES "")

ADD_SUBDIRECTORY(src)

MESSAGE("SOURCES ${OBDCU_EXECUTABLES}")
MESSAGE("INCLUDES ${OBDCU_INCLUDES}")

ADD_EXECUTABLE(OBDCU ${OBDCU_EXECUTABLES})

#ADD_CUSTOM_COMMAND(TARGET OBDCU
#  PRE_BUILD
#  COMMAND mkdir -p includes
#  COMMAND ln -s -f ${OBDCU_INCLUDES} includes/.
#  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/"
#)

TARGET_LINK_LIBRARIES(OBDCU
  View
  Controller
  ${middleware_dynamic_libraries}
  ${middleware_static_libraries}

) #Model)

