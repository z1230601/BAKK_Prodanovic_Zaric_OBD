INCLUDE_DIRECTORIES(includes)

# find all cpp files in src dir and set internal Cmake variable EXECS
FILE(GLOB_RECURSE model_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

ADD_LIBRARY(Model STATIC ${model_SOURCES})

TARGET_LINK_LIBRARIES(Model
   Qt4::QtGui 
   Qt4::QtXml
)