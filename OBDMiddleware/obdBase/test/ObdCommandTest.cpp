#include "ObdCommandTest.h"
#include "../src/ObdCommand.h"
#include "../src/AbstractOBDValue.h"
#include <string>

void ObdCommandTest::setUp()
{
    obdcommand_under_test_ = new ObdCommand();

    calculation_input_.pid_ = 0x66;
    calculation_input_.description_ = "Luftmassenmesser";
    calculation_input_.validity_mapping_mode_ = ValidityMappingMode::AUTO;

    {
        OBDCommandValueInput value;
        value.is_mapping_ = false;
        value.name_ = "MAF Sensor A";
        value.bytes_ = 2;
        value.min_ = 0;
        value.max_ = 2047.96875;
        value.unit_ = "g/s";

        calculation_input_.values_.push_back(value);
    }
    {
        OBDCommandValueInput value;
        value.is_mapping_ = false;
        value.name_ = "MAF Sensor B";
        value.bytes_ = 2;
        value.min_ = 0;
        value.max_ = 2047.96875;
        value.unit_ = "g/s";

        calculation_input_.values_.push_back(value);
    }

    value_input_.pid_ = 0x5F;
    value_input_.description_ = "Für das Fahrzeug gültige Abgasnorm";
    value_input_.validity_mapping_mode_ = ValidityMappingMode::OFF;

    {
        OBDCommandValueInput value;
        value.is_mapping_ = true;
        value.bytes_ = 1;
        value.mapping_type_ = MappingType::VALUE;
        {
            MappingEntry entry;
            entry.from_ = "0E";
            entry.content_ = "LKW (Euro IV) B1";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "0F";
            entry.content_ = "LKW (Euro V) B2";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "10";
            entry.content_ = "LKW (Euro EEV) C";
            value.mapping_.push_back(entry);
        }
        value_input_.values_.push_back(value);
    }

    bit_input_.pid_ = 0x65;
    bit_input_.description_ = "Zusätzliche Ein- und Ausgänge";
    bit_input_.validity_mapping_mode_ = ValidityMappingMode::AUTO;
    {
        OBDCommandValueInput value;
        value.is_mapping_ = true;
        value.bytes_ = 1;
        value.mapping_type_ = MappingType::BIT;
        {
            MappingEntry entry;
            entry.from_ = "0";
            entry.set_ = "false";
            entry.content_ = "Kraftaufnahme inaktiv";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "0";
            entry.set_ = "true";
            entry.content_ = "Kraftaufnahme aktiv";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "1";
            entry.set_ = "false";
            entry.content_ = "Automatikgetriebe in Park-/Neutralstellung";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "1";
            entry.set_ = "true";
            entry.content_ = "Vorwärts- oder Rückwärtsgang";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "2";
            entry.set_ = "false";
            entry.content_ =
                    "Manuelles Getriebe in Neutralstellung und/oder Kupplung getreten";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "2";
            entry.set_ = "true";
            entry.content_ = "Gang eingelegt";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "3";
            entry.set_ = "false";
            entry.content_ = "Vorglühlampe aus";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "3";
            entry.set_ = "true";
            entry.content_ = "Lampe ein";
            value.mapping_.push_back(entry);
        }
        bit_input_.values_.push_back(value);
    }

    bitcombination_input_.pid_ = 0x70;
    bitcombination_input_.description_ = "Ladedruckregelung";
    bitcombination_input_.validity_mapping_mode_ = ValidityMappingMode::MANUAL;
    {
        OBDCommandValueInput value;
        value.is_mapping_ = false;
        value.name_ = "Soll Ladedruck A";
        value.bytes_ = 2;
        value.min_ = 0;
        value.max_ = 2047.96875;
        value.unit_ = "kPa";
        value.mapping_type_ = MappingType::NOTMAPPED;
        ValidityBitEntry valentry;
        valentry.content_ = "0";
        value.man_validity_entries_.push_back(valentry);
        bitcombination_input_.values_.push_back(value);
    }
    {
        OBDCommandValueInput value;
        value.is_mapping_ = false;
        value.name_ = "Ist Ladedruck A";
        value.bytes_ = 2;
        value.min_ = 0;
        value.max_ = 2047.96875;
        value.unit_ = "kPa";
        value.mapping_type_ = MappingType::NOTMAPPED;
        ValidityBitEntry valentry;
        valentry.content_ = "1";
        value.man_validity_entries_.push_back(valentry);
        bitcombination_input_.values_.push_back(value);
    }
    {
        OBDCommandValueInput value;
        value.is_mapping_ = false;
        value.name_ = "Soll Ladedruck B";
        value.bytes_ = 2;
        value.min_ = 0;
        value.max_ = 2047.96875;
        value.unit_ = "kPa";
        value.mapping_type_ = MappingType::NOTMAPPED;
        ValidityBitEntry valentry;
        valentry.content_ = "3";
        value.man_validity_entries_.push_back(valentry);
        bitcombination_input_.values_.push_back(value);
    }
    {
        OBDCommandValueInput value;
        value.is_mapping_ = false;
        value.name_ = "Ist Ladedruck B";
        value.bytes_ = 2;
        value.min_ = 0;
        value.max_ = 2047.96875;
        value.unit_ = "kPa";
        value.mapping_type_ = MappingType::NOTMAPPED;
        ValidityBitEntry valentry;
        valentry.content_ = "4";
        value.man_validity_entries_.push_back(valentry);
        bitcombination_input_.values_.push_back(value);
    }
    {
        OBDCommandValueInput value;
        value.is_mapping_ = true;
        value.bytes_ = 1;
        value.mapping_type_ = MappingType::BITCOMBINATION;
        {
            ValidityBitEntry entry;
            entry.from_ = "01";
            entry.content_ = "2";
            value.man_validity_entries_.push_back(entry);
        }
        {
            ValidityBitEntry entry;
            entry.from_ = "23";
            entry.content_ = "5";
            value.man_validity_entries_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "01";
            entry.set_ = "01";
            entry.content_ = "Offener Kreislauf, kein Fehler";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "01";
            entry.set_ = "10";
            entry.content_ = "Geschlossener Kreislauf, kein Fehler";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "01";
            entry.set_ = "11";
            entry.content_ = "Fehler vorhanden, Wert unzuverlässig";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "23";
            entry.set_ = "01";
            entry.content_ = "Offener Kreislauf, kein Fehler";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "23";
            entry.set_ = "10";
            entry.content_ = "Geschlossener Kreislauf, kein Fehler";
            value.mapping_.push_back(entry);
        }
        {
            MappingEntry entry;
            entry.from_ = "23";
            entry.set_ = "11";
            entry.content_ = "Fehler vorhanden, Wert unzuverlässig";
            value.mapping_.push_back(entry);
        }
        bitcombination_input_.values_.push_back(value);
    }
    expected_sids_.push_back(1);
    expected_sids_.push_back(2);
}

void ObdCommandTest::tearDown()
{
    delete obdcommand_under_test_;
}

void ObdCommandTest::testConstruction()
{
    std::string expectedDescription = "";
    unsigned int expectedPid = 0;
    std::vector<unsigned int> expectedSids = { };

    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            obdcommand_under_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedPid, obdcommand_under_test_->getPid());
    CPPUNIT_ASSERT_EQUAL(expectedSids.size(),
            obdcommand_under_test_->getSids().size());
    CPPUNIT_ASSERT_EQUAL((size_t) 0,
            obdcommand_under_test_->getValues().size());
}

void ObdCommandTest::testParameterConstruction()
{
    unsigned int expectedPid = 0x65;
    std::string expectedDescription = "Zusätzliche Ein- und Ausgänge";

    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, expectedPid,
            expectedDescription);

    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            obdcommand_under_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedPid, obdcommand_under_test_->getPid());
    CPPUNIT_ASSERT_EQUAL(expected_sids_.size(),
            obdcommand_under_test_->getSids().size());
    CPPUNIT_ASSERT_EQUAL((size_t) 0,
            obdcommand_under_test_->getValues().size());
}

void ObdCommandTest::testInputStructConstruction()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, calculation_input_);

    CPPUNIT_ASSERT_EQUAL(expected_sids_.size(),
            obdcommand_under_test_->getSids().size());
    for(unsigned i = 0; i < expected_sids_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expected_sids_.at(i),
                obdcommand_under_test_->getSids().at(i));
    }

    CPPUNIT_ASSERT_EQUAL(calculation_input_.pid_,
            obdcommand_under_test_->getPid());
    CPPUNIT_ASSERT_EQUAL(calculation_input_.description_,
            obdcommand_under_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(calculation_input_.values_.size(),
            obdcommand_under_test_->getValues().size());

}

void ObdCommandTest::testValidityMappingConstruction()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, calculation_input_);

    CPPUNIT_ASSERT_EQUAL(expected_sids_.size(),
            obdcommand_under_test_->getSids().size());
    for(unsigned int i = 0; i < expected_sids_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expected_sids_.at(i),
                obdcommand_under_test_->getSids().at(i));
    }
    CPPUNIT_ASSERT_EQUAL(calculation_input_.description_,
            obdcommand_under_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(calculation_input_.pid_,
            obdcommand_under_test_->getPid());

    CPPUNIT_ASSERT_EQUAL(calculation_input_.values_.size(),
            obdcommand_under_test_->getValues().size());
}

void ObdCommandTest::testRequestString()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, calculation_input_);

    std::stringstream expected;
    expected << "0" << expected_sids_.at(0) << " " << std::hex
            << calculation_input_.pid_ << std::dec;
    unsigned int selected_sid = 1;
    CPPUNIT_ASSERT_EQUAL(expected.str(),
            obdcommand_under_test_->getRequestString(selected_sid));

    expected.str("");
    expected << "0" << expected_sids_.at(1) << " " << std::hex
            << calculation_input_.pid_ << std::dec;
    selected_sid = 2;
    CPPUNIT_ASSERT_EQUAL(expected.str(),
            obdcommand_under_test_->getRequestString(selected_sid));
}

void ObdCommandTest::testInterpretReceivedBytesCalculationValue()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, calculation_input_);

    std::vector<uint8_t> input_bytes { 3, 0x40, 0, 0x80, 0 };

    double expected_result1 = 512;
    double expected_result2 = 1024;

    obdcommand_under_test_->interpretReceivedBytes(input_bytes);

    CPPUNIT_ASSERT_EQUAL((size_t) 2,
            obdcommand_under_test_->getValues().size());
    CPPUNIT_ASSERT_EQUAL(expected_result1,
            obdcommand_under_test_->getValues().at(0)->getInterpretedValue());
    CPPUNIT_ASSERT_EQUAL(expected_result2,
            obdcommand_under_test_->getValues().at(1)->getInterpretedValue());

}

void ObdCommandTest::testConvertToSendableBytesCalculationValue()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, calculation_input_);

    std::vector<uint8_t> expected_bytes { 3, 0x40, 0, 0x80, 0 };
    std::vector<std::string> input { "512", "1024" };

    for(unsigned int i = 0; i < obdcommand_under_test_->getValues().size(); i++)
    {
        obdcommand_under_test_->getValues().at(i)->interpretToByteArray(
                input.at(i));
    }

    std::vector<uint8_t> actual = obdcommand_under_test_
            ->convertToSendableByteArray();

    CPPUNIT_ASSERT_EQUAL(expected_bytes.size(), actual.size());

    for(unsigned int i = 0; i < expected_bytes.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expected_bytes.at(i), actual.at(i));
    }
}

void ObdCommandTest::testInterpretReceivedBytesValueMapping()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, value_input_);

    std::vector<uint8_t> input_bytes { 0x0E };
    std::string expected_result = "LKW (Euro IV) B1";

    obdcommand_under_test_->interpretReceivedBytes(input_bytes);

    CPPUNIT_ASSERT_EQUAL(expected_result,
            obdcommand_under_test_->getValues().at(0)->getInterpretedValueAsString());

    input_bytes.clear();
    input_bytes.push_back(0x0F);
    expected_result = "LKW (Euro V) B2";

    obdcommand_under_test_->interpretReceivedBytes(input_bytes);

    CPPUNIT_ASSERT_EQUAL(expected_result,
            obdcommand_under_test_->getValues().at(0)->getInterpretedValueAsString());
}

void ObdCommandTest::testConvertToSendableBytesValueMapping()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, value_input_);

    std::vector<uint8_t> expected_bytes { 0x0E };
    std::string input = "LKW (Euro IV) B1";

    CPPUNIT_ASSERT_EQUAL((size_t) 1,
            obdcommand_under_test_->getValues().size());

    obdcommand_under_test_->getValues().at(0)->interpretToByteArray(input);

    std::vector<uint8_t> actual = obdcommand_under_test_
            ->convertToSendableByteArray();

    CPPUNIT_ASSERT_EQUAL(expected_bytes.size(), actual.size());

    for(unsigned int i = 0; i < expected_bytes.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expected_bytes.at(i), actual.at(i));
    }
}

void ObdCommandTest::testInterpretReceivedBytesBitMapping()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, bit_input_);

    std::vector<uint8_t> input_bytes { 0x01, 0x01 };
    std::string expected_result = "Kraftaufnahme aktiv";

    obdcommand_under_test_->interpretReceivedBytes(input_bytes);

    CPPUNIT_ASSERT_EQUAL(expected_result,
            obdcommand_under_test_->getValues().at(0)->getInterpretedValueAsString());

    input_bytes.clear();
    input_bytes.push_back(0x01);
    input_bytes.push_back(0x00);
    expected_result = "Kraftaufnahme inaktiv";

    obdcommand_under_test_->interpretReceivedBytes(input_bytes);

    CPPUNIT_ASSERT_EQUAL(expected_result,
            obdcommand_under_test_->getValues().at(0)->getInterpretedValueAsString());

    input_bytes.clear();
    input_bytes.push_back(0x06);
    input_bytes.push_back(0x04);
    expected_result =
            "Automatikgetriebe in Park-/Neutralstellung\nGang eingelegt";

    obdcommand_under_test_->interpretReceivedBytes(input_bytes);

    CPPUNIT_ASSERT_EQUAL(expected_result,
            obdcommand_under_test_->getValues().at(0)->getInterpretedValueAsString());
}

void ObdCommandTest::testConvertToSendableBytesBitMapping()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, bit_input_);

    std::vector<uint8_t> expected_bytes { 0x01, 0x01 };
    std::string input = "Kraftaufnahme aktiv";

    CPPUNIT_ASSERT_EQUAL((size_t) 1,
            obdcommand_under_test_->getValues().size());

    obdcommand_under_test_->getValues().at(0)->interpretToByteArray(input);

    std::vector<uint8_t> actual = obdcommand_under_test_
            ->convertToSendableByteArray();

    CPPUNIT_ASSERT_EQUAL(expected_bytes.size(), actual.size());

    for(unsigned int i = 0; i < expected_bytes.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL((unsigned int) expected_bytes.at(i),
                (unsigned int) actual.at(i));
    }
}

void ObdCommandTest::testInterpretReceivedBytesBitCombinationMapping()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_,
            bitcombination_input_);

    std::vector<uint8_t> input_bytes { 0x3F, 0x00, 0x20, 0xFF, 0xE0, 0x61, 0x20,
            0xB4, 0x80, 0x09 };
    std::vector<double> expected_calc_results { 1, 2047, 777, 1444 };
    std::string expected_bitcombination_result =
            "Offener Kreislauf, kein Fehler\nGeschlossener Kreislauf, kein Fehler";

    obdcommand_under_test_->interpretReceivedBytes(input_bytes);

    CPPUNIT_ASSERT_EQUAL(expected_calc_results.size(),
            obdcommand_under_test_->getValues().size() - 1);

    unsigned i = 0;
    for(; i < expected_calc_results.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expected_calc_results.at(i),
                obdcommand_under_test_->getValues().at(i)->getInterpretedValue());
    }

    CPPUNIT_ASSERT_EQUAL(expected_bitcombination_result,
            obdcommand_under_test_->getValues().at(i)->getInterpretedValueAsString());
}

void ObdCommandTest::testConvertToSendableBytesBitCombinationMapping()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_,
            bitcombination_input_);

    std::vector<uint8_t> expected_bytes { 0x3F, 0x00, 0x20, 0xFF, 0xE0, 0x61,
            0x20, 0xB4, 0x80, 0x09 };
    std::vector<std::string> inputs { "1", "2047", "777", "1444",
            "Offener Kreislauf, kein Fehler\nGeschlossener Kreislauf, kein Fehler" };

    CPPUNIT_ASSERT_EQUAL(inputs.size(), obdcommand_under_test_->getValues().size());
    for(unsigned int i=0; i < inputs.size(); i++){
        obdcommand_under_test_->getValues().at(i)->interpretToByteArray(inputs.at(i));
    }

    std::vector<uint8_t> actual = obdcommand_under_test_
            ->convertToSendableByteArray();

    CPPUNIT_ASSERT_EQUAL(expected_bytes.size(), actual.size());

    for(unsigned int i = 0; i < expected_bytes.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL((unsigned int) expected_bytes.at(i),
                (unsigned int) actual.at(i));
    }

}
