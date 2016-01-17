INCLUDE_DIRECTORIES(includes)

# find all cpp files in src dir and set internal Cmake variable EXECS
FILE(GLOB_RECURSE controller_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

ADD_LIBRARY(Controller STATIC ${controller_SOURCES})

TARGET_LINK_LIBRARIES(Controller
   Qt4::QtGui 
   Qt4::QtXml
)