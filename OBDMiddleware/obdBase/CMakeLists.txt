CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(OBDBase)

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

# Find required external libraries ##############################################
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

# find all cpp files in src dir and set internal Cmake variable EXECS
FILE(GLOB_RECURSE EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)

SET(OBDBase_target_name "obd-base-dev")
#Make also shared library out of found cpps and set internal CMAKE VAR
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../databaseManagement/src/)

ADD_LIBRARY(${OBDBase_target_name} SHARED ${EXECS})
SET(LIBRARY_NAME "lib${OBDBase_target_name}.so")


# link the libraries to the executable (most of them found by cmake modules)
TARGET_LINK_LIBRARIES(${OBDBase_target_name}
  ${database_library_location}
  ${LibXML++_LIBRARIES}
  ${Boost_LIBRARIES}
)

MESSAGE("Adding dependcies to ${OBDBase_target_name}: " ${Database_target_name})

# setup linking posibility ########################################################

FILE(GLOB_RECURSE dev_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# Link result into home folder for easier finding
GET_PROPERTY(obd_library_location TARGET ${OBDBase_target_name} PROPERTY LOCATION)
MESSAGE (STATUS "obd_base_lib_location == ${obd_library_location} linking to ${OBDMiddleware_SOURCE_DIR}/")

#ADD_CUSTOM_COMMAND(TARGET ${OBDBase_target_name}
#   POST_BUILD
#   COMMAND ln -s -f ${obd_library_location} ${LIBRARY_NAME}
#   COMMAND mkdir -p middleware_includes
#   COMMAND ln -s -f ${dev_INCLUDES} middleware_includes/.
#   WORKING_DIRECTORY "${OBDMiddleware_SOURCE_DIR}/"
#)

########################################################################################

## Install & Packaging #################################################################
SET(INSTALL_DIR "/usr/lib/")
INSTALL(TARGETS
   ${OBDBase_target_name}
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

ADD_EXECUTABLE(OBDBaseTester 
     ${UnitTests_SRCS})

TARGET_LINK_LIBRARIES(OBDBaseTester
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${CPPUNIT_LIBRARIES}
                      ${CMAKE_DL_LIBS}
                      ${OBDBase_target_name}

                      )

SET(TESTDBSETUP_PATH ${OBDBase_SOURCE_DIR}/test/testdata/testdb.sql)

ADD_CUSTOM_COMMAND(TARGET OBDBaseTester
     PRE_BUILD
     COMMAND ${OBDBase_SOURCE_DIR}/test/testdata//setupDatabases.sh "${TESTDBSETUP_PATH}"
     WORKING_DIR ${OBDBase_SOURCE_DIR}
     VERBATIM
)

FILE(GLOB Tests_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/*Test.cpp)

FOREACH(test ${Tests_SRCS})
        GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
        ADD_TEST(${TestName} OBDBaseTester ${TestName})
ENDFOREACH(test)
