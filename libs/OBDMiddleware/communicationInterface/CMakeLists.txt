# Create a library called "communication" which includes all source files ("*.cxx").
# The extension is already found. Any number of sources could be listed here.
add_library (communication *.cxx)

# Make sure the compiler can find include files for our communication library
# when other libraries or executables link to Hello
target_include_directories (communication PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
