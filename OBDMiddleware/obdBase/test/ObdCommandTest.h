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
            CPPUNIT_TEST(testConstruction);
            CPPUNIT_TEST(testParameterConstruction);
            CPPUNIT_TEST(testInputStructConstruction);
            CPPUNIT_TEST(testValidityMappingConstruction);
            CPPUNIT_TEST(testRequestString);
            CPPUNIT_TEST(testInterpretReceivedBytesCalculationValue);
            CPPUNIT_TEST(testInterpretReceivedBytesValueMapping);
            CPPUNIT_TEST(testInterpretReceivedBytesBitMapping);
            CPPUNIT_TEST(testInterpretReceivedBytesBitCombinationMapping);
            CPPUNIT_TEST(testConvertToSendableBytesCalculationValue);
            CPPUNIT_TEST(testConvertToSendableBytesValueMapping);
            CPPUNIT_TEST(testConvertToSendableBytesBitMapping);
            CPPUNIT_TEST(testConvertToSendableBytesBitCombinationMapping);
        CPPUNIT_TEST_SUITE_END();

    private:
        ObdCommand* obdcommand_under_test_;
        OBDCommandInput calculation_input_;
        OBDCommandInput value_input_;
        OBDCommandInput bit_input_;
        OBDCommandInput bitcombination_input_;
        std::vector<unsigned int> expected_sids_;

    public:
        void setUp();
        void tearDown();
        void testConstruction();
        void testParameterConstruction();
        void testInputStructConstruction();
        void testValidityMappingConstruction();
        void testInterpretReceivedBytesCalculationValue();
        void testInterpretReceivedBytesValueMapping();
        void testInterpretReceivedBytesBitMapping();
        void testInterpretReceivedBytesBitCombinationMapping();
        void testConvertToSendableBytesCalculationValue();
        void testConvertToSendableBytesValueMapping();
        void testConvertToSendableBytesBitMapping();
        void testConvertToSendableBytesBitCombinationMapping();

        void testRequestString();

};
CPPUNIT_TEST_SUITE_REGISTRATION(ObdCommandTest);
#endif /* OBDCOMMANDTEST_H_ */
