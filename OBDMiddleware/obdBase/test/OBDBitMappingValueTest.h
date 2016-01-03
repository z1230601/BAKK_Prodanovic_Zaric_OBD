#ifndef OBDBITMAPPINGVALUETEST_H_
#define OBDBITMAPPINGVALUETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "../../configurations/src/OBDCommandInputDefinitions.h"

class OBDBitMappingValue;

class OBDBitMappingValueTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE (OBDBitMappingValueTest);
        CPPUNIT_TEST (testDefaultConstruction);
        CPPUNIT_TEST (testParameterConstruction);
        CPPUNIT_TEST (testInputStructConstruction);
        CPPUNIT_TEST (testValueConversion);
        CPPUNIT_TEST (testValueConversionMultipleSelections);
        CPPUNIT_TEST_SUITE_END();

    private:
        OBDBitMappingValue* value_under_test_;
        OBDCommandValueInput value_;
    public:
        void setUp();
        void tearDown();
        void testDefaultConstruction();
        void testParameterConstruction();
        void testInputStructConstruction();
        void testValueConversion();
        void testValueConversionMultipleSelections();
};
CPPUNIT_TEST_SUITE_REGISTRATION (OBDBitMappingValueTest);

#endif /* OBDBITMAPPINGVALUETEST_H_ */
