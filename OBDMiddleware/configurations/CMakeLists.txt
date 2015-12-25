CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Configuration)

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

##################################################################################

INCLUDE_DIRECTORIES(includes)
INCLUDE_DIRECTORIES(${LibXML++_INCLUDE_DIRS})

# find all cpp files in src dir and set internal Cmake variable EXECS
FILE(GLOB_RECURSE EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM EXECS ${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp)

SET(Configuration_target_name "configuration-dev")
#Make also shared library out of found cpps and set internal CMAKE VAR
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../configurations/src/)

ADD_LIBRARY(${Configuration_target_name} SHARED ${EXECS})
SET(LIBRARY_NAME "lib${Configuration_target_name}.so")


# link the libraries to the executable (most of them found by cmake modules)
TARGET_LINK_LIBRARIES(${Configuration_target_name}
  ${LibXML++_LIBRARIES}
  ${Boost_LIBRARIES}
)

# setup linking posibility ########################################################

FILE(GLOB_RECURSE dev_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

# Link result into home folder for easier finding
GET_PROPERTY(configuration_library_location TARGET ${Configuration_target_name} PROPERTY LOCATION)
MESSAGE (STATUS "configuration_base_lib_location == ${obd_library_location} linking to ${OBDMiddleware_SOURCE_DIR}/")

#ADD_CUSTOM_COMMAND(TARGET ${Configuration_target_name}
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
   ${Configuration_target_name}
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

ADD_EXECUTABLE(ConfigurationTester 
     ${UnitTests_SRCS})

TARGET_LINK_LIBRARIES(ConfigurationTester
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${CPPUNIT_LIBRARIES}
                      ${CMAKE_DL_LIBS}
                      ${Configuration_target_name}

                      )

FILE(GLOB Tests_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/*Test.cpp)

FOREACH(test ${Tests_SRCS})
        GET_FILENAME_COMPONENT(TestName ${test} NAME_WE)
        ADD_TEST(${TestName} ConfigurationTester ${TestName})
ENDFOREACH(test)
