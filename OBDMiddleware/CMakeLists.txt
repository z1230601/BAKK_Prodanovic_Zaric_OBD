cmake_minimum_required(VERSION 2.6)
PROJECT(OBDMiddleware)

SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "-g -Wall")


SET(middleware_VERSION_MAJOR 0)
SET(middleware_VERSION_MINOR 0)
SET(middleware_VERSION_PATCH 0)

SET(middleware_VESION_STRING ${middleware_VERSION_MAJOR} "." ${middleware_VERSION_MINOR} "." ${middleware_VERSION_PATCH})

MESSAGE("Building Middleware with version: " ${middleware_VESION_STRING})

# add sub-parts
ADD_SUBDIRECTORY(communicationInterface)
ADD_SUBDIRECTORY(databaseManagement)