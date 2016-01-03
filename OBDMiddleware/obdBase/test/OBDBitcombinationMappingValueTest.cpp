#include "OBDBitcombinationMappingValueTest.h"

#include "../src/OBDBitcombinationMappingValue.h"

void OBDBitcombinationMappingValueTest::setUp()
{
    value_under_test_ = new OBDBitcombinationMappingValue();

    value_.is_mapping_ = true;
    value_.bytes_ = 1;
    value_.mapping_type_ = MappingType::BITCOMBINATION;
    {
        ValidityBitEntry entry;
        entry.from_ = "01";
        entry.content_ = "2";
        value_.man_validity_entries_.push_back(entry);
    }
    {
        ValidityBitEntry entry;
        entry.from_ = "23";
        entry.content_ = "5";
        value_.man_validity_entries_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "01";
        entry.set_ = "01";
        entry.content_ = "Offener Kreislauf, kein Fehler";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "01";
        entry.set_ = "10";
        entry.content_ = "Geschlossener Kreislauf, kein Fehler";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "01";
        entry.set_ = "11";
        entry.content_ = "Fehler vorhanden, Wert unzuverlässig";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "23";
        entry.set_ = "01";
        entry.content_ = "Offener Kreislauf, kein Fehler";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "23";
        entry.set_ = "10";
        entry.content_ = "Geschlossener Kreislauf, kein Fehler";
        value_.mapping_.push_back(entry);
    }
    {
        MappingEntry entry;
        entry.from_ = "23";
        entry.set_ = "11";
        entry.content_ = "Fehler vorhanden, Wert unzuverlässig";
        value_.mapping_.push_back(entry);
    }
}

void OBDBitcombinationMappingValueTest::tearDown()
{
    delete value_under_test_;
}

void OBDBitcombinationMappingValueTest::testDefaultConstruction()
{
    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0, value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());

    //Mapping check
    CPPUNIT_ASSERT(value_under_test_->getMapping().empty());
}

void OBDBitcombinationMappingValueTest::testParameterConstruction()
{
    unsigned int expectedByteAmount = 1;
    delete value_under_test_;
    value_under_test_ = new OBDBitcombinationMappingValue(expectedByteAmount);

    CPPUNIT_ASSERT(value_under_test_);
    CPPUNIT_ASSERT_EQUAL(expectedByteAmount,
            value_under_test_->getByteAmount());
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0,
            value_under_test_->getUninterpretedValue());
    CPPUNIT_ASSERT_EQUAL((double) 0, value_under_test_->getInterpretedValue());
    CPPUNIT_ASSERT(value_under_test_->getName().empty());

    CPPUNIT_ASSERT(value_under_test_->getMapping().empty());
}

void OBDBitcombinationMappingValueTest::testInputStructConstruction()
{
    delete value_under_test_;
    value_under_test_ = new OBDBitcombinationMappingValue(value_);

    CPPUNIT_ASSERT_EQUAL((unsigned int) value_.bytes_,
            value_under_test_->getByteAmount());

    CPPUNIT_ASSERT_EQUAL((unsigned int) 0b11,
            value_under_test_->getKeyFromBitPositionString("01"));
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0b1100,
            value_under_test_->getKeyFromBitPositionString("23"));
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0b110000,
            value_under_test_->getKeyFromBitPositionString("45"));

    unsigned int actualSize = 0;
    std::map<unsigned int, std::map<unsigned int, std::string> >::iterator it =
            value_under_test_->getMapping().begin();
    for(; it != value_under_test_->getMapping().end(); it++)
    {
        actualSize += (*it).second.size();
    }

    CPPUNIT_ASSERT_EQUAL(value_.mapping_.size(), (size_t) actualSize);

    for(MappingEntry entry : value_.mapping_)
    {
        unsigned int fromkey = value_under_test_->getKeyFromBitPositionString(
                entry.from_);
        unsigned int setkey = std::stoi(entry.set_, nullptr, 2);

        CPPUNIT_ASSERT(
                value_under_test_->getMapping().find(fromkey)
                        != value_under_test_->getMapping().end());
        CPPUNIT_ASSERT(
                value_under_test_->getMapping().at(fromkey).find(setkey)
                        != value_under_test_->getMapping().at(fromkey).end());

        CPPUNIT_ASSERT_EQUAL(entry.content_,
                value_under_test_->getMapping().at(fromkey).at(setkey));
    }
}

void OBDBitcombinationMappingValueTest::testValueConversion()
{
    delete value_under_test_;
    value_under_test_ = new OBDBitcombinationMappingValue(value_);

    std::vector<uint8_t> expectedByteArray { 2 };
    std::string expectedValueAsString = "Geschlossener Kreislauf, kein Fehler";

    std::map<unsigned int, bool> valid_bitcombinations_positions;
    valid_bitcombinations_positions[value_under_test_
            ->getKeyFromBitPositionString("01")] = true;

    value_under_test_->setBitcombinationScope(valid_bitcombinations_positions);

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

void OBDBitcombinationMappingValueTest::testValueConversionSlightlyMoreComplicated()
{
    delete value_under_test_;
    value_under_test_ = new OBDBitcombinationMappingValue(value_);

    std::vector<uint8_t> expectedByteArray { 8 };
    std::string expectedValueAsString = "Geschlossener Kreislauf, kein Fehler";

    std::map<unsigned int, bool> valid_bitcombinations_positions;
    valid_bitcombinations_positions[value_under_test_
            ->getKeyFromBitPositionString("23")] = true;

    value_under_test_->setBitcombinationScope(valid_bitcombinations_positions);

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

void OBDBitcombinationMappingValueTest::testValueConversionMultipleValues()
{
    delete value_under_test_;
    value_under_test_ = new OBDBitcombinationMappingValue(value_);

    std::vector<uint8_t> expectedByteArray { 6 };
    std::string expectedValueAsString =
            "Geschlossener Kreislauf, kein Fehler\nOffener Kreislauf, kein Fehler";

    std::map<unsigned int, bool> valid_bitcombinations_positions;
    valid_bitcombinations_positions[value_under_test_
            ->getKeyFromBitPositionString("01")] = true;
    valid_bitcombinations_positions[value_under_test_
            ->getKeyFromBitPositionString("23")] = true;
    value_under_test_->setBitcombinationScope(valid_bitcombinations_positions);

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
