#include "OBDCalculationValueTest.h"

#include "../src/OBDCalculationValue.h"
#include "../../configurations/src/OBDCommandInputDefinitions.h"

void OBDCalculationValueTest::setUp(){
    value_under_test_ = new OBDCalculationValue();
}

void OBDCalculationValueTest::tearDown(){

}

void OBDCalculationValueTest::testDefaultConstruction(){
    //Default Consutruction
    CPPUNIT_ASSERT_NOT_NULL(value_under_test_);
    CPPUNIT_ASSERT_EQUAL(0,value_under_test_->getByteAmount());
    CPPUNIT_ASSERT(value_under_test_->getUninterpretedValue().empty());
    CPPUNIT_ASSERT(0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());
}

