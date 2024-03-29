#ifndef OBDCALCULATIONVALUETEST_H_
#define OBDCALCULATIONVALUETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class OBDCalculationValue;

class OBDCalculationValueTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE (OBDCalculationValueTest);
        CPPUNIT_TEST (testDefaultConstruction);
        CPPUNIT_TEST(testParameterConstruction);
        CPPUNIT_TEST(testInputStructConstruction);
        CPPUNIT_TEST(testAutoModeInputConstruction);
        CPPUNIT_TEST(testManualModeInputConstruction);
        CPPUNIT_TEST(testToSendableByteConversion);
        CPPUNIT_TEST(testToValueConversion);
        CPPUNIT_TEST(testAuxiliaryFunctions);
        CPPUNIT_TEST_SUITE_END();

    private:
        OBDCalculationValue* value_under_test_;

    public:
        void setUp();
        void tearDown();
        void testDefaultConstruction();
        void testParameterConstruction();
        void testInputStructConstruction();
        void testAutoModeInputConstruction();
        void testManualModeInputConstruction();
        void testToValueConversion();
        void testToSendableByteConversion();
        void testAuxiliaryFunctions();
};
CPPUNIT_TEST_SUITE_REGISTRATION(OBDCalculationValueTest);
#endif /* OBDCALCULATIONVALUETEST_H_ */
