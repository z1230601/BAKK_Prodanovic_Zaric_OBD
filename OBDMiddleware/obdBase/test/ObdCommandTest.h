#ifndef OBDCOMMANDTEST_H_
#define OBDCOMMANDTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "../../configurations/src/OBDCommandInputDefinitions.h"

#include <vector>

class ObdCommand;

class ObdCommandTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE (ObdCommandTest);
        CPPUNIT_TEST (testConstruction);
        CPPUNIT_TEST (testParameterConstruction);
        CPPUNIT_TEST (testInputStructConstruction);
        CPPUNIT_TEST (testValidityMappingConstruction);
        CPPUNIT_TEST (testRequestString);
        CPPUNIT_TEST (testInterpretReceivedBytes);
        CPPUNIT_TEST_SUITE_END();

    private:
        ObdCommand* obdcommand_under_test_;
        OBDCommandInput input_;
        std::vector<unsigned int> expected_sids_;

    public:
        void setUp();
        void tearDown();
        void testConstruction();
        void testParameterConstruction();
        void testInputStructConstruction();
        void testValidityMappingConstruction();
        void testInterpretReceivedBytes();
        void testRequestString();

};
CPPUNIT_TEST_SUITE_REGISTRATION (ObdCommandTest);
#endif /* OBDCOMMANDTEST_H_ */
