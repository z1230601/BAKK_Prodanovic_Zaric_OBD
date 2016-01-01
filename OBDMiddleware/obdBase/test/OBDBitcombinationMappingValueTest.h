#ifndef OBDBITCOMBINATIONMAPPINGVALUETEST_H_
#define OBDBITCOMBINATIONMAPPINGVALUETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class OBDBitcombinationMappingValue;

class OBDBitcombinationMappingValueTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE (OBDBitMappingValueTest);
    CPPUNIT_TEST (testDefaultConstruction);
    CPPUNIT_TEST (testParameterConstruction);
    CPPUNIT_TEST (testInputStructConstruction);
    CPPUNIT_TEST (testToSendableByteConversion);
    CPPUNIT_TEST (testToValueConversion);
    CPPUNIT_TEST_SUITE_END();

    private:
        OBDBitcombinationMappingValue* value_under_test_;
    public:
        void setUp();
        void tearDown();
        void testDefaultConstruction();
        void testParameterConstruction();
        void testInputStructConstruction();
        void testToValueConversion();
        void testToSendableByteConversion();
};
CPPUNIT_TEST_SUITE_REGISTRATION (OBDBitcombinationMappingValueTest);
#endif /* OBDBITCOMBINATIONMAPPINGVALUETEST_H_ */
