#include "OBDValueMappingValueTest.h"

#include "../src/OBDValueMappingValue.h"

void OBDValueMappingValueTest::setUp()
{
    value_under_test_ = new OBDValueMappingValue();
}

void OBDValueMappingValueTest::tearDown()
{
    delete value_under_test_;
}

void OBDValueMappingValueTest::testDefaultConstruction()
{
    //Default Consutruction
    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0, value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());
}

void OBDValueMappingValueTest::testParameterConstruction()
{

}

void OBDValueMappingValueTest::testInputStructConstruction()
{

}

void OBDValueMappingValueTest::testToValueConversion()
{
}

void OBDValueMappingValueTest::testToSendableByteConversion()
{
}

