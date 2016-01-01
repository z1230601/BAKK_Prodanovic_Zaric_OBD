#include "OBDCalculationValueTest.h"

#include "../src/OBDCalculationValue.h"
#include "../../configurations/src/OBDCommandInputDefinitions.h"

void OBDCalculationValueTest::setUp()
{
    value_under_test_ = new OBDCalculationValue();
}

void OBDCalculationValueTest::tearDown()
{
    delete value_under_test_;
}

void OBDCalculationValueTest::testDefaultConstruction()
{
    //Default Consutruction
    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0, value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());
}

void OBDCalculationValueTest::testParameterConstruction()
{
    std::string expectedName = "testcommand";
    unsigned int expectedByteAmount = 2;
    double expectedMin = 0;
    double expectedMax = 2047.98;
    std::string expectedUnit = "lbs/m";

    delete value_under_test_;
    value_under_test_ = new OBDCalculationValue(expectedName,
            expectedByteAmount, expectedMin, expectedMax, expectedUnit);

    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL(expectedByteAmount,
            value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT_EQUAL(expectedName, value_under_test_->getName());

    CPPUNIT_ASSERT_EQUAL(expectedMin, value_under_test_->getMin());
    CPPUNIT_ASSERT_EQUAL(expectedMax, value_under_test_->getMax());
    CPPUNIT_ASSERT_EQUAL(expectedUnit, value_under_test_->getUnit());
}

void OBDCalculationValueTest::testInputStructConstruction()
{
    OBDCommandValueInput expected;
    expected.bytes_ = 2;
    expected.is_mapping_ = false;
    expected.min_ = 0.0;
    expected.max_ = 2047.98;
    expected.name_ = "testcommand";
    expected.unit_ = "lbs/m";

    delete value_under_test_;
    value_under_test_ = new OBDCalculationValue(expected);

    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL((unsigned int) expected.bytes_,
            value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT_EQUAL(expected.name_, value_under_test_->getName());

    CPPUNIT_ASSERT_EQUAL(expected.min_, value_under_test_->getMin());
    CPPUNIT_ASSERT_EQUAL(expected.max_, value_under_test_->getMax());
    CPPUNIT_ASSERT_EQUAL(expected.unit_, value_under_test_->getUnit());
}

void OBDCalculationValueTest::testToValueConversion()
{
    OBDCommandValueInput expected;
    expected.bytes_ = 2;
    expected.is_mapping_ = false;
    expected.min_ = 0.0;
    expected.max_ = 2047.96875;
    expected.name_ = "testcommand";
    expected.unit_ = "lbs/m";

    std::vector<uint8_t> testData { 127, 255 }; // = 32767
    double expectedValue = 1023.96875;
    std::string expectedValueString = "1023.96875";

    delete value_under_test_;
    value_under_test_ = new OBDCalculationValue(expected);

    value_under_test_->interpretToValue(testData);

    CPPUNIT_ASSERT_EQUAL(expectedValue,
            value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT_EQUAL(value_under_test_->calculateCompoundValue(testData),
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL(expectedValueString, value_under_test_->getInterpretedValueAsString());
}

void OBDCalculationValueTest::testToSendableByteConversion()
{
    OBDCommandValueInput expected;
    expected.bytes_ = 2;
    expected.is_mapping_ = false;
    expected.min_ = 0.0;
    expected.max_ = 2047.96875;
    expected.name_ = "testcommand";
    expected.unit_ = "lbs/m";

    std::vector<uint8_t> expectedByteArray { 127, 255 }; // = 32767
    double expectedValue = 1023.96875;
    std::string expectedValueString = "1023.96875";

    delete value_under_test_;
    value_under_test_ = new OBDCalculationValue(expected);

    value_under_test_->interpretToByteArray(expectedValue);

    CPPUNIT_ASSERT_EQUAL(expectedValue,
            value_under_test_->getInterpretedValue());

    CPPUNIT_ASSERT_EQUAL(expectedValueString, value_under_test_->getInterpretedValueAsString());

    CPPUNIT_ASSERT_EQUAL(
            value_under_test_->calculateCompoundValue(expectedByteArray),
            value_under_test_->getUninterpretedValue());

    std::vector<uint8_t> actual = value_under_test_
            ->calculateByteArrayFromCompoundValue(
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL(expectedByteArray.size(), actual.size());
    for(unsigned int i = 0; i < expectedByteArray.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expectedByteArray.at(i), actual.at(i));
    }
}

void OBDCalculationValueTest::testAuxiliaryFunctions()
{
    std::string expectedName = "";
    unsigned int expectedByteAmount = 4;
    double expectedMin = 0;
    double expectedMax = 0;
    std::string expectedUnit = "";

    delete value_under_test_;
    value_under_test_ = new OBDCalculationValue(expectedName,
            expectedByteAmount, expectedMin, expectedMax, expectedUnit);

    std::vector<uint8_t> expectedByteArray { 42, 85, 127, 255 };
    unsigned int expectedCompoundValue = ((((((42 * 256) + 85) * 256) + 127)
            * 256) + 255);

    CPPUNIT_ASSERT_EQUAL(expectedCompoundValue,
            value_under_test_->calculateCompoundValue(expectedByteArray));

    std::vector<uint8_t> actual = value_under_test_->calculateByteArrayFromCompoundValue(expectedCompoundValue);

    CPPUNIT_ASSERT_EQUAL(expectedByteArray.size(), actual.size());
    for(unsigned int i = 0; i < expectedByteArray.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL((unsigned int) expectedByteArray.at(i), (unsigned int) actual.at(i));
    }

}