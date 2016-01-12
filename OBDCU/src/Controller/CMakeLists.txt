INCLUDE_DIRECTORIES(includes)

# find all cpp files in src dir and set internal Cmake variable EXECS
FILE(GLOB_RECURSE controller_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

ADD_LIBRARY(Controller STATIC ${controller_SOURCES})
