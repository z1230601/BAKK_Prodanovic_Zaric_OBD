#ifndef OBDBITCOMBINATIONMAPPINGVALUETEST_H_
#define OBDBITCOMBINATIONMAPPINGVALUETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "../../configurations/src/OBDCommandInputDefinitions.h"

class OBDBitcombinationMappingValue;

class OBDBitcombinationMappingValueTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE (OBDBitcombinationMappingValueTest);
    CPPUNIT_TEST (testDefaultConstruction);
    CPPUNIT_TEST (testParameterConstruction);
    CPPUNIT_TEST (testInputStructConstruction);
    CPPUNIT_TEST (testValueConversion);
    CPPUNIT_TEST (testValueConversionSlightlyMoreComplicated);
    CPPUNIT_TEST (testValueConversionMultipleValues);
    CPPUNIT_TEST_SUITE_END();

    private:
        OBDBitcombinationMappingValue* value_under_test_;
        OBDCommandValueInput value_;
    public:
        void setUp();
        void tearDown();
        void testDefaultConstruction();
        void testParameterConstruction();
        void testInputStructConstruction();
        void testValueConversion();
        void testValueConversionSlightlyMoreComplicated();
        void testValueConversionMultipleValues();
};
CPPUNIT_TEST_SUITE_REGISTRATION (OBDBitcombinationMappingValueTest);
#endif /* OBDBITCOMBINATIONMAPPINGVALUETEST_H_ */
