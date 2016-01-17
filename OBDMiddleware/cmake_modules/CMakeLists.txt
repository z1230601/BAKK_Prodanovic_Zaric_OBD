FILE(GLOB_RECURSE modules ${CMAKE_CURRENT_SOURCE_DIR}/*.cmake)

SET(cmake_INSTALL_DIR "$ENV{HOME}/.cmake_modules/")
INSTALL(FILES
  ${modules}
  DESTINATION ${cmake_INSTALL_DIR})