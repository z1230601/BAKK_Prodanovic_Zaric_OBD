cmake_minimum_required(VERSION 2.6)
PROJECT(OBDMiddleware)

SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "-g -Wall")


SET(middleware_VERSION_MAJOR 0)
SET(middleware_VERSION_MINOR 0)
SET(middleware_VERSION_PATCH 1)

SET(middleware_VESION_STRING "${middleware_VERSION_MAJOR}.${middleware_VERSION_MINOR}.${middleware_VERSION_PATCH}")

MESSAGE("Building Middleware with version: " ${middleware_VESION_STRING})

SET(Configuration_target_name "configuration-dev")
SET(Database_target_name database-connection-manager-dev)

SET(middleware_include_dir "${CMAKE_CURRENT_BINARY_DIR}/middleware_includes/")

IF(NOT DEFINED configuration_library_location)
  SET(configuration_library_location "${CMAKE_CURRENT_BINARY_DIR}/configurations/libconfiguration-dev.so")
ENDIF(NOT DEFINED configuration_library_location)

IF(NOT DEFINED database_library_location)
  SET(database_library_location "${CMAKE_CURRENT_BINARY_DIR}/databaseManagement/libdatabase-connection-manager-dev.so")
ENDIF(NOT DEFINED database_library_location)


# add sub-parts
ADD_SUBDIRECTORY(configurations)
ADD_SUBDIRECTORY(communicationInterface)
ADD_SUBDIRECTORY(databaseManagement)
ADD_SUBDIRECTORY(obdBase)
ADD_SUBDIRECTORY(cmake_modules)


ADD_CUSTOM_COMMAND(TARGET serial-communication-dev 
   POST_BUILD
   COMMAND ln -s -f ${serial_communication_location} ${LIBRARY_NAME}
   COMMAND mkdir -p ${middleware_include_dir}
   COMMAND ln -s -f ${dev_INCLUDES} ${middleware_include_dir}/.
   WORKING_DIRECTORY "${OBDMiddleware_SOURCE_DIR}/"
)

ADD_DEPENDENCIES(${Database_target_name} ${Configuration_target_name})

##Packaging      ##############################################################
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Zoran Prodanovic") #required
SET(CPACK_PACKAGE_VERSION ${middleware_VESION_STRING})
INCLUDE(CPack)