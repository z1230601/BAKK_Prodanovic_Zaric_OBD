include_directories (${PROJECT_SRC_DIR}/src) 

add_executable (test 
        TestMain.cpp
	UartDeviceTest.cpp) 

add_test(NAME SerialCommunication
    COMMAND test)

target_link_libraries(test
                      ${Boost_FILESYSTEM_LIBRARY}
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                      ${CPPUNIT_LIBRARIES}
                      )
