CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(DatabaseManagement)


#IF(NOT DEFINED configuration_library_location)
#  SET(configuration_library_location "${CMAKE_CURRENT_SOURCE_DIR}/../configurations/libconfiguration-dev.so")
#ENDIF(NOT DEFINED configuration_library_location)

MESSAGE(STATUS "Using in database to link to conf: " ${configuration_library_location})

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0")

IF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64") 
  ADD_DEFINITIONS(-fPIC) 
ENDIF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

# Find required external libraries ##############################################
FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(Boost COMPONENTS thread system REQUIRED)

#reset CMAKE Module path for special find scripts
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
MESSAGE( STATUS "CMAKE_MODULE_PATH:         " ${CMAKE_MODULE_PATH} )
FIND_PACKAGE(CppUnit REQUIRED)
FIND_PACKAGE(Xml++ REQUIRED)
FIND_PACKAGE(MySQLConnectorCPP REQUIRED)
##################################################################################

INCLUDE_DIRECTORIES(includes)
INCLUDE_DIRECTORIES(${LibXML++_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${MYSQLCONNECTORCPP_INCLUDE_DIRS})


# find all cpp files in src dir and set internal Cmake variable EXECS
FILE(GLOB_RECURSE EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../configurations/src/)

#Make also shared library out of found cpps and set internal CMAKE VAR
ADD_LIBRARY(${Database_target_name} SHARED ${EXECS})
SET(LIBRARY_NAME "lib${Database_target_name}.so")

# link the libraries to the executable (most of them found by cmake modules)
TARGET_LINK_LIBRARIES(${Database_target_name}
         ${configuration_library_location}
         ${CMAKE_THREAD_LIBS_INIT}
         ${Boost_LIBRARIES}
         ${LibXML++_LIBRARIES}
         ${MYSQLCONNECTORCPP_LIBRARIES})

# setup linking posibility ########################################################

FILE(GLOB_RECURSE dev_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# Link result into home folder for easier finding
GET_PROPERTY(database_library_location TARGET ${Database_target_name} PROPERTY LOCATION)
MESSAGE (STATUS "database_lib_location == ${database_library_location} linking to ${OBDMiddleware_SOURCE_DIR}/")

ADD_CUSTOM_COMMAND(TARGET ${Database_target_name}
   POST_BUILD
   COMMAND ln -s -f ${database_library_location} ${LIBRARY_NAME}
   COMMAND mkdir -p ${middleware_include_dir}
   COMMAND ln -s -f ${dev_INCLUDES} ${middleware_include_dir}/.
   WORKING_DIRECTORY "${OBDMiddleware_SOURCE_DIR}/"
)

########################################################################################

## Install & Packaging #################################################################
SET(INSTALL_DIR "/usr/lib/")
INSTALL(TARGETS
   ${Database_target_name}
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

ADD_EXECUTABLE(DatabaseTester 
     ${UnitTests_SRCS})

TARGET_LINK_LIBRARIES(DatabaseTester

         ${configuration_library_location}
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${CPPUNIT_LIBRARIES}
                      ${CMAKE_DL_LIBS}
                      ${Database_target_name}

                      )

SET(TESTDBSETUP_PATH ${DatabaseManagement_SOURCE_DIR}/test/testdata/testdb.sql)

ADD_CUSTOM_COMMAND(TARGET DatabaseTester
     PRE_BUILD
     COMMAND ${DatabaseManagement_SOURCE_DIR}/test/testdata//setupDatabases.sh "${TESTDBSETUP_PATH}"
     WORKING_DIR ${DatabaseManagement_SOURCE_DIR}
     VERBATIM
)

FILE(GLOB Tests_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/*Test.cpp)

FOREACH(test ${Tests_SRCS})
        GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
        ADD_TEST(${TestName} DatabaseTester ${TestName})
ENDFOREACH(test)
