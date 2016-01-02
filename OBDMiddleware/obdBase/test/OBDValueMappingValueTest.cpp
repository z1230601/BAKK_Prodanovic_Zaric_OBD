#include "OBDValueMappingValueTest.h"

#include "../src/OBDValueMappingValue.h"

void OBDValueMappingValueTest::setUp()
{
    value_under_test_ = new OBDValueMappingValue();

    input.is_mapping_ = true;
    input.bytes_ = 1;
    input.mapping_type_ = MappingType::VALUE;
    {
        MappingEntry entry;
        entry.from_ = "0E";
        entry.content_ = "LKW (Euro IV) B1";
        input.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "0F";
        entry.content_ = "LKW (Euro V) B2";
        input.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "10";
        entry.content_ = "LKW (Euro EEV) C";
        input.mapping_.push_back(entry);
    }
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
    CPPUNIT_ASSERT(value_under_test_->getMapping().empty());
}

void OBDValueMappingValueTest::testParameterConstruction()
{
    unsigned int expectedByte = 1;
    std::string expectedName = "AbgasMapping";

    delete value_under_test_;
    value_under_test_ = new OBDValueMappingValue(expectedByte);
    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL((unsigned int) 1, value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());
    CPPUNIT_ASSERT(value_under_test_->getMapping().empty());

    delete value_under_test_;
    value_under_test_ = new OBDValueMappingValue(expectedByte, expectedName);
    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL((unsigned int) 1, value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT_EQUAL(expectedName, value_under_test_->getName());
    CPPUNIT_ASSERT(value_under_test_->getMapping().empty());
}

void OBDValueMappingValueTest::testInputStructConstruction()
{
    delete value_under_test_;
    value_under_test_ = new OBDValueMappingValue(input);
    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL((unsigned int) 1, value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());

    CPPUNIT_ASSERT_EQUAL(input.mapping_.size(),
            value_under_test_->getMapping().size());

    for(MappingEntry entry : input.mapping_)
    {
        unsigned int key = std::stoi(entry.from_, nullptr, 16);
        CPPUNIT_ASSERT(
                value_under_test_->getMapping().find(key)
                        != value_under_test_->getMapping().end());
        CPPUNIT_ASSERT_EQUAL(entry.content_,
                value_under_test_->getMapping().at(key));
    }
}

void OBDValueMappingValueTest::testValueConversion()
{
    delete value_under_test_;
    value_under_test_ = new OBDValueMappingValue(input);

    std::vector<uint8_t> expectedByteArray { 14 };
    std::string expectedValueAsString = "LKW (Euro IV) B1";

    CPPUNIT_ASSERT_EQUAL(expectedValueAsString,
            value_under_test_->interpretToValue(expectedByteArray));
    CPPUNIT_ASSERT_EQUAL(expectedByteArray.size(),
            value_under_test_->interpretToByteArray(expectedValueAsString).size());

    CPPUNIT_ASSERT_EQUAL(value_under_test_->calculateCompoundValue(expectedByteArray), value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) value_under_test_->calculateCompoundValue(expectedByteArray), value_under_test_->getInterpretedValue());

    for(unsigned int i = 0; i < expectedByteArray.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expectedByteArray.at(i),
                value_under_test_->interpretToByteArray(expectedValueAsString)
                        .at(i));
    }
}

void OBDValueMappingValueTest::testValueConversionFail()
{
    delete value_under_test_;
    value_under_test_ = new OBDValueMappingValue(input);

    std::vector<uint8_t> expectedByteArray { 10 };
    std::string expectedValueAsString = "LKW (FAIL) B";

    CPPUNIT_ASSERT(value_under_test_->interpretToValue(expectedByteArray).empty());
    CPPUNIT_ASSERT(value_under_test_->interpretToByteArray(expectedValueAsString).empty());
}

