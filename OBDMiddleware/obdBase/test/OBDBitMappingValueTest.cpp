#include "OBDBitMappingValueTest.h"

#include "../src/OBDBitMappingValue.h"

void OBDBitMappingValueTest::setUp()
{
    value_under_test_ = new OBDBitMappingValue();

    value_.is_mapping_ = true;
    value_.bytes_ = 1;
    value_.mapping_type_ = MappingType::BIT;
    {
        MappingEntry entry;
        entry.from_ = "0";
        entry.set_ = "false";
        entry.content_ = "Kraftaufnahme inaktiv";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "0";
        entry.set_ = "true";
        entry.content_ = "Kraftaufnahme aktiv";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "1";
        entry.set_ = "false";
        entry.content_ = "Automatikgetriebe in Park-/Neutralstellung";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "1";
        entry.set_ = "true";
        entry.content_ = "Vorwärts- oder Rückwärtsgang";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "2";
        entry.set_ = "false";
        entry.content_ =
                "Manuelles Getriebe in Neutralstellung und/oder Kupplung getreten";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "2";
        entry.set_ = "true";
        entry.content_ = "Gang eingelegt";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "3";
        entry.set_ = "false";
        entry.content_ = "Vorglühlampe aus";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "3";
        entry.set_ = "";
        entry.content_ = "Lampe ein";
        value_.mapping_.push_back(entry);
    }
}

void OBDBitMappingValueTest::tearDown()
{
    delete value_under_test_;
}

void OBDBitMappingValueTest::testDefaultConstruction()
{ //Default Consutruction
    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0, value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());
    CPPUNIT_ASSERT(value_under_test_->getTrueMapping().empty());
    CPPUNIT_ASSERT(value_under_test_->getFalseMapping().empty());
}

void OBDBitMappingValueTest::testParameterConstruction()
{
    unsigned int expectedByteAmount = 1;
    delete value_under_test_;
    value_under_test_ = new OBDBitMappingValue(expectedByteAmount);

    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL(expectedByteAmount,
            value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());
    CPPUNIT_ASSERT(value_under_test_->getTrueMapping().empty());
    CPPUNIT_ASSERT(value_under_test_->getFalseMapping().empty());
}

void OBDBitMappingValueTest::testInputStructConstruction()
{
    delete value_under_test_;
    value_under_test_ = new OBDBitMappingValue(value_);

    CPPUNIT_ASSERT_EQUAL((unsigned int) value_.bytes_,
            value_under_test_->getByteAmount());

    CPPUNIT_ASSERT_EQUAL(value_.mapping_.size(),
            value_under_test_->getTrueMapping().size()
                    + value_under_test_->getFalseMapping().size());

    for(MappingEntry entry : value_.mapping_)
    {
        unsigned int key = std::stoi(entry.from_);
        if(entry.set_.compare("false") == 0)
        {
            CPPUNIT_ASSERT(
                    value_under_test_->getFalseMapping().find(key)
                            != value_under_test_->getFalseMapping().end());
            CPPUNIT_ASSERT_EQUAL(entry.content_,
                    value_under_test_->getFalseMapping().at(key));
        } else if(entry.set_.compare("true") == 0 || entry.set_.empty())
        {
            CPPUNIT_ASSERT(
                    value_under_test_->getTrueMapping().find(key)
                            != value_under_test_->getTrueMapping().end());
            CPPUNIT_ASSERT_EQUAL(entry.content_,
                    value_under_test_->getTrueMapping().at(key));
        } else {
            CPPUNIT_FAIL("Invalid set option");
        }
    }
}

void OBDBitMappingValueTest::testValueConversion()
{
    delete value_under_test_;
    value_under_test_ = new OBDBitMappingValue(value_);

    std::vector<uint8_t> expectedByteArray { 2 };
    std::string expectedValueAsString = "Vorwärts- oder Rückwärtsgang";
    std::map<unsigned int, bool> valid_bit_positions;
    valid_bit_positions[1] = true;
    value_under_test_->setBitScope(valid_bit_positions);

    CPPUNIT_ASSERT_EQUAL(expectedValueAsString,
            value_under_test_->interpretToValue(expectedByteArray));
    CPPUNIT_ASSERT_EQUAL(expectedByteArray.size(),
            value_under_test_->interpretToByteArray(expectedValueAsString).size());

    CPPUNIT_ASSERT_EQUAL(
            value_under_test_->calculateCompoundValue(expectedByteArray),
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL(
            (double) value_under_test_->calculateCompoundValue(
                    expectedByteArray),
            value_under_test_->getInterpretedValue());

    for(unsigned int i = 0; i < expectedByteArray.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expectedByteArray.at(i),
                value_under_test_->interpretToByteArray(expectedValueAsString)
                        .at(i));
    }
}

void OBDBitMappingValueTest::testValueConversionMultipleSelections()
{
    delete value_under_test_;
    value_under_test_ = new OBDBitMappingValue(value_);

    std::vector<uint8_t> expectedByteArray { 10 };
    std::string expectedValueAsString =
            "Kraftaufnahme inaktiv\nVorwärts- oder Rückwärtsgang\nManuelles Getriebe in Neutralstellung und/oder Kupplung getreten\nLampe ein";
    std::map<unsigned int, bool> valid_bit_positions;
    valid_bit_positions[0] = true;
    valid_bit_positions[1] = true;
    valid_bit_positions[2] = true;
    valid_bit_positions[3] = true;
    value_under_test_->setBitScope(valid_bit_positions);

    CPPUNIT_ASSERT_EQUAL(expectedValueAsString,
            value_under_test_->interpretToValue(expectedByteArray));
    CPPUNIT_ASSERT_EQUAL(expectedByteArray.size(),
            value_under_test_->interpretToByteArray(expectedValueAsString).size());

    CPPUNIT_ASSERT_EQUAL(
            value_under_test_->calculateCompoundValue(expectedByteArray),
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL(
            (double) value_under_test_->calculateCompoundValue(
                    expectedByteArray),
            value_under_test_->getInterpretedValue());

    for(unsigned int i = 0; i < expectedByteArray.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expectedByteArray.at(i),
                value_under_test_->interpretToByteArray(expectedValueAsString)
                        .at(i));
    }
}
