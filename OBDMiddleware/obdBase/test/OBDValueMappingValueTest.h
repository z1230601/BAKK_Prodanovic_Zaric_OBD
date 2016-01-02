#ifndef OBDVALUEMAPPINGVALUETEST_H_
#define OBDVALUEMAPPINGVALUETEST_H_

#include "../../configurations/src/OBDCommandInputDefinitions.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class OBDValueMappingValue;

class OBDValueMappingValueTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE (OBDValueMappingValueTest);
        CPPUNIT_TEST (testDefaultConstruction);
        CPPUNIT_TEST (testParameterConstruction);
        CPPUNIT_TEST (testInputStructConstruction);
        CPPUNIT_TEST (testValueConversionFail);
        CPPUNIT_TEST (testValueConversion);

        CPPUNIT_TEST_SUITE_END();

    private:
        OBDValueMappingValue* value_under_test_;
        OBDCommandValueInput input;
    public:
        void setUp();
        void tearDown();
        void testDefaultConstruction();
        void testParameterConstruction();
        void testInputStructConstruction();
        void testValueConversion();
        void testValueConversionFail();

};
CPPUNIT_TEST_SUITE_REGISTRATION (OBDValueMappingValueTest);

#endif /* OBDVALUEMAPPINGVALUETEST_H_ */
