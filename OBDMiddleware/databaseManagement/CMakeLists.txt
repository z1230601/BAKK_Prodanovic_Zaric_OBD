cmake_minimum_required(VERSION 2.6)
project(DatabaseManagement)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0")

IF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64") 
  ADD_DEFINITIONS(-fPIC) 
ENDIF(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")

add_subdirectory(src)
add_subdirectory(test)
include_directories(includes)
# Find required external libraries
find_package(Threads REQUIRED)
find_package(Boost COMPONENTS thread system REQUIRED)


#reset CMAKE Module path for special find scripts
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
MESSAGE( STATUS "CMAKE_MODULE_PATH:         " ${CMAKE_MODULE_PATH} )
find_package(CppUnit REQUIRED)
find_package(Xml++ REQUIRED)
find_package(MySQLConnectorCPP REQUIRED)


include_directories(${LibXML++_INCLUDE_DIRS})
include_directories(${MYSQLCONNECTORCPP_INCLUDE_DIRS})
# find all cpp files in src dir and set internal Cmake variable EXECS
FILE(GLOB_RECURSE EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
list(REMOVE_ITEM EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)
message(STATUS "without main: " ${EXECS})

#Make also shared library out of found cpps and set internal CMAKE VAR
add_library(database-connection-manager-dev SHARED ${EXECS})

set(SRC_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/build/libdatabase-connection-manager-dev.a)

message(status ${SRC_LIBRARY})
# link the libraries to the executable (most of them found by cmake modules)
target_link_libraries (database-connection-manager-dev
         ${CMAKE_THREAD_LIBS_INIT}
         ${Boost_LIBRARIES}
         ${LibXML++_LIBRARIES}
         ${MYSQLCONNECTORCPP_LIBRARIES})

##Testing        ##############################################################
include(CTest)

FILE(GLOB UnitTests_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

MESSAGE( STATUS "looking in:         " ${CMAKE_CURRENT_SOURCE_DIR}/test/ )

ADD_EXECUTABLE(DatabaseTester 
     ${UnitTests_SRCS})

target_link_libraries(DatabaseTester
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${CPPUNIT_LIBRARIES}
                      ${CMAKE_DL_LIBS}
                      database-connection-manager-dev

                      )

#ADD_DEPENDENCIES(DatabaseTester SetupTestDb)

MESSAGE("PATH TO SQL: ${DatabaseManagement_SOURCE_DIR}/test/testdata/testdb.sql")
ADD_CUSTOM_COMMAND(TARGET DatabaseTester
     PRE_BUILD
     COMMAND ${DatabaseManagement_SOURCE_DIR}/test/testdata//setupDatabases.sh "${DatabaseManagement_SOURCE_DIR}/test/testdata/testdb.sql"
     WORKING_DIR ${DatabaseManagement_SOURCE_DIR}
     VERBATIM
)

message(STATUS " test to be added: " ${UnitTests_SRCS})
FOREACH(test ${UnitTests_SRCS})
        GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
        ADD_TEST(${TestName} DatabaseTester ${TestName})
ENDFOREACH(test)
