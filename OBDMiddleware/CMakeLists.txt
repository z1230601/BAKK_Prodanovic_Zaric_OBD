cmake_minimum_required(VERSION 2.6)
PROJECT(OBDMiddleware)

SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "-g -Wall")


SET(middleware_VERSION_MAJOR 0)
SET(middleware_VERSION_MINOR 0)
SET(middleware_VERSION_PATCH 1)

SET(middleware_VESION_STRING "${middleware_VERSION_MAJOR}.${middleware_VERSION_MINOR}.${middleware_VERSION_PATCH}")

MESSAGE("Building Middleware with version: " ${middleware_VESION_STRING})

# add sub-parts
ADD_SUBDIRECTORY(communicationInterface)
ADD_SUBDIRECTORY(databaseManagement)
ADD_SUBDIRECTORY(obdBase)

##Packaging      ##############################################################
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Zoran Prodanovic") #required
SET(CPACK_PACKAGE_VERSION ${middleware_VESION_STRING})
INCLUDE(CPack)