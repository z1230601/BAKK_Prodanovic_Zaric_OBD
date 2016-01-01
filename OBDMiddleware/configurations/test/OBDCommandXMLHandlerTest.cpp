#include "OBDCommandXMLHandlerTest.h"
#include "../src/OBDCommandInputDefinitions.h"

#include <iostream>
#include <string>

void OBDCommandXMLHandlerTest::tearDown()
{
    delete handler_for_test_;
}

void OBDCommandXMLHandlerTest::testServiceModeParse()
{
    CPPUNIT_ASSERT(handler_for_test_->getParsedData().size() >= 1);
    CPPUNIT_ASSERT_EQUAL(expected_.sid_.size(),
            handler_for_test_->getParsedData().at(0).sid_.size());

    for(unsigned int i = 0;
            i < handler_for_test_->getParsedData().at(0).sid_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expected_.sid_.at(i),
                handler_for_test_->getParsedData().at(0).sid_.at(i));
    }
}

void OBDCommandXMLHandlerTest::testPureValueCommand()
{
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).pid_,
            handler_for_test_->getParsedData().at(0).commands_.at(0).pid_);
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).description_,
            handler_for_test_->getParsedData().at(0).commands_.at(0) .description_);
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).validity_mapping_mode_,
            handler_for_test_->getParsedData().at(0).commands_.at(0) .validity_mapping_mode_);

    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).values_.size(),
            handler_for_test_->getParsedData().at(0).commands_.at(0).values_ .size());

    for(unsigned int i = 0; i < expected_.commands_.at(0).values_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(0).values_.at(i).is_mapping_,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).is_mapping_);

        CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).values_.at(i).bytes_,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).bytes_);
        CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).values_.at(i).min_,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).min_);
        CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).values_.at(i).max_,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).max_);
        CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).values_.at(i).name_,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).name_);
        CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(0).values_.at(i).unit_,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).unit_);

        CPPUNIT_ASSERT_EQUAL((size_t) 0,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).man_validity_entries_.size());
        CPPUNIT_ASSERT_EQUAL((size_t) 0,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).mapping_.size());
        CPPUNIT_ASSERT_EQUAL(MappingType::NOTMAPPED,
                handler_for_test_->getParsedData().at(0).commands_.at(0).values_.at(i).mapping_type_);
    }
}

void OBDCommandXMLHandlerTest::testSimpleMappingValueCommand()
{
    CPPUNIT_ASSERT(handler_for_test_->getParsedData().size() >= 1);
    ServiceModeInput actual = handler_for_test_->getParsedData().at(0);
    unsigned int commandNr = 1;
    CPPUNIT_ASSERT(actual.commands_.size() >= commandNr);

    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).pid_,
            actual.commands_.at(commandNr).pid_);
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).description_,
            actual.commands_.at(commandNr).description_);
    CPPUNIT_ASSERT_EQUAL(
            expected_.commands_.at(commandNr).validity_mapping_mode_,
            actual.commands_.at(commandNr).validity_mapping_mode_);
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).values_.size(),
            actual.commands_.at(commandNr).values_.size());

    for(unsigned int i = 0;
            i < expected_.commands_.at(commandNr).values_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).is_mapping_,
                actual.commands_.at(commandNr).values_.at(i).is_mapping_);

        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).bytes_,
                actual.commands_.at(commandNr).values_.at(i).bytes_);
        CPPUNIT_ASSERT_EQUAL(0.0,
                actual.commands_.at(commandNr).values_.at(i).min_);
        CPPUNIT_ASSERT_EQUAL(0.0,
                actual.commands_.at(commandNr).values_.at(i).max_);
        CPPUNIT_ASSERT(
                actual.commands_.at(commandNr).values_.at(i).name_.empty());
        CPPUNIT_ASSERT(
                actual.commands_.at(commandNr).values_.at(i).unit_.empty());

        CPPUNIT_ASSERT_EQUAL((size_t) 0,
                actual.commands_.at(commandNr).values_.at(i).man_validity_entries_.size());
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).mapping_type_,
                actual.commands_.at(commandNr).values_.at(i).mapping_type_);

        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).mapping_.size(),
                actual.commands_.at(commandNr).values_.at(i).mapping_.size());
        std::vector<MappingEntry> expectedMapping = expected_.commands_.at(
                commandNr).values_.at(i).mapping_;
        std::vector<MappingEntry> actualMapping = actual.commands_.at(commandNr)
                .values_.at(i).mapping_;
        for(unsigned int j = 0; j < expectedMapping.size(); j++)
        {
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).from_,
                    actualMapping.at(j).from_);
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).set_,
                    actualMapping.at(j).set_);
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).content_,
                    actualMapping.at(j).content_);
        }
    }
}

void OBDCommandXMLHandlerTest::testSimpleBitValueMapping()
{
    CPPUNIT_ASSERT(handler_for_test_->getParsedData().size() >= 1);
    ServiceModeInput actual = handler_for_test_->getParsedData().at(0);
    unsigned int commandNr = 2;
    CPPUNIT_ASSERT(actual.commands_.size() >= commandNr);

    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).pid_,
            actual.commands_.at(commandNr).pid_);
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).description_,
            actual.commands_.at(commandNr).description_);
    CPPUNIT_ASSERT_EQUAL(
            expected_.commands_.at(commandNr).validity_mapping_mode_,
            actual.commands_.at(commandNr) .validity_mapping_mode_);
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).values_.size(),
            actual.commands_.at(commandNr).values_ .size());

    for(unsigned int i = 0;
            i < expected_.commands_.at(commandNr).values_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).is_mapping_,
                actual.commands_.at(commandNr).values_.at(i).is_mapping_);

        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).bytes_,
                actual.commands_.at(commandNr).values_.at(i).bytes_);
        CPPUNIT_ASSERT_EQUAL(0.0,
                actual.commands_.at(commandNr).values_.at(i).min_);
        CPPUNIT_ASSERT_EQUAL(0.0,
                actual.commands_.at(commandNr).values_.at(i).max_);
        CPPUNIT_ASSERT(
                actual.commands_.at(commandNr).values_.at(i).name_.empty());
        CPPUNIT_ASSERT(
                actual.commands_.at(commandNr).values_.at(i).unit_.empty());

        CPPUNIT_ASSERT_EQUAL((size_t) 0,
                actual.commands_.at(commandNr).values_.at(i).man_validity_entries_.size());
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).mapping_type_,
                actual.commands_.at(commandNr).values_.at(i).mapping_type_);

        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).mapping_.size(),
                actual.commands_.at(commandNr).values_.at(i).mapping_.size());

        std::vector<MappingEntry> expectedMapping = expected_.commands_.at(
                commandNr).values_.at(i).mapping_;
        std::vector<MappingEntry> actualMapping = actual.commands_.at(commandNr)
                .values_.at(i).mapping_;
        for(unsigned int j = 0; j < expectedMapping.size(); j++)
        {
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).from_,
                    actualMapping.at(j).from_);
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).set_,
                    actualMapping.at(j).set_);
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).content_,
                    actualMapping.at(j).content_);
        }
    }
}

void OBDCommandXMLHandlerTest::testMixedValueMappingWithManualValidityMapping()
{
    CPPUNIT_ASSERT(handler_for_test_->getParsedData().size() >= 1);
    ServiceModeInput actual = handler_for_test_->getParsedData().at(0);
    unsigned int commandNr = 3;
    CPPUNIT_ASSERT(actual.commands_.size() >= commandNr);

    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).pid_,
            actual.commands_.at(commandNr).pid_);
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).description_,
            actual.commands_.at(commandNr).description_);
    CPPUNIT_ASSERT_EQUAL(
            expected_.commands_.at(commandNr).validity_mapping_mode_,
            actual.commands_.at(commandNr) .validity_mapping_mode_);
    CPPUNIT_ASSERT_EQUAL(expected_.commands_.at(commandNr).values_.size(),
            actual.commands_.at(commandNr).values_ .size());

    for(unsigned int i = 0;
            i < expected_.commands_.at(commandNr).values_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).is_mapping_,
                actual.commands_.at(commandNr).values_.at(i).is_mapping_);

        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).bytes_,
                actual.commands_.at(commandNr).values_.at(i).bytes_);
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).min_,
                actual.commands_.at(commandNr).values_.at(i).min_);
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).max_,
                actual.commands_.at(commandNr).values_.at(i).max_);
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).name_,
                actual.commands_.at(commandNr).values_.at(i).name_);
        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).unit_,
                actual.commands_.at(commandNr).values_.at(i).unit_);

        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).man_validity_entries_.size(),
                actual.commands_.at(commandNr).values_.at(i).man_validity_entries_.size());
        std::vector<ValidityBitEntry> expectedValidityBitEntries = expected_
                .commands_.at(commandNr).values_.at(i).man_validity_entries_;
        std::vector<ValidityBitEntry> actualValidityBitEntries = actual
                .commands_.at(commandNr).values_.at(i).man_validity_entries_;

        for(unsigned int j = 0; j < expectedValidityBitEntries.size(); j++)
        {
            CPPUNIT_ASSERT_EQUAL(expectedValidityBitEntries.at(j).content_,
                    actualValidityBitEntries.at(j).content_);
            CPPUNIT_ASSERT_EQUAL(expectedValidityBitEntries.at(j).from_,
                    actualValidityBitEntries.at(j).from_);
        }

        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).mapping_type_,
                actual.commands_.at(commandNr).values_.at(i).mapping_type_);

        CPPUNIT_ASSERT_EQUAL(
                expected_.commands_.at(commandNr).values_.at(i).mapping_.size(),
                actual.commands_.at(commandNr).values_.at(i).mapping_.size());

        std::vector<MappingEntry> expectedMapping = expected_.commands_.at(
                commandNr).values_.at(i).mapping_;
        std::vector<MappingEntry> actualMapping = actual.commands_.at(commandNr)
                .values_.at(i).mapping_;
        for(unsigned int j = 0; j < expectedMapping.size(); j++)
        {
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).from_,
                    actualMapping.at(j).from_);
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).set_,
                    actualMapping.at(j).set_);
            CPPUNIT_ASSERT_EQUAL(expectedMapping.at(j).content_,
                    actualMapping.at(j).content_);
        }
    }
}

///////////////////////////////////////////CONSTRUCTION SECTION /////////////////////////////////////////////////////////////
xmlpp::Element* addChildWithText(xmlpp::Element* parent, std::string name,
        std::string text)
{
    xmlpp::Element* child = parent->add_child(name);
    child->add_child_text(text);
    return child;
}
void OBDCommandXMLHandlerTest::setUp()
{
    handler_for_test_ = new OBDCommandXMLHandler();
    try
    {
        xmlpp::DomParser parser;
        parser.set_substitute_entities();
        parser.set_validate();
        parser.parse_file("../test/testdata/obdcommand.xml");
        if(parser)
        {
            iterateChildren(parser.get_document()->get_root_node());
        }
    } catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }

    expected_.sid_.push_back(1);
    expected_.sid_.push_back(2);

    {
        OBDCommandInput input;
        input.pid_ = 0x66;
        input.description_ = "Luftmassenmesser";
        input.validity_mapping_mode_ = ValidityMappingMode::AUTO;

        {
            OBDCommandValueInput value;
            value.is_mapping_ = false;
            value.name_ = "MAF Sensor A";
            value.bytes_ = 2;
            value.min_ = 0;
            value.max_ = 2047.96875;
            value.unit_ = "g/s";

            input.values_.push_back(value);
        }
        {
            OBDCommandValueInput value;
            value.is_mapping_ = false;
            value.name_ = "MAF Sensor B";
            value.bytes_ = 2;
            value.min_ = 0;
            value.max_ = 2047.96875;
            value.unit_ = "g/s";

            input.values_.push_back(value);
        }
        expected_.commands_.push_back(input);
    }
    {
        OBDCommandInput input;
        input.pid_ = 0x5F;
        input.description_ = "Für das Fahrzeug gültige Abgasnorm";
        input.validity_mapping_mode_ = ValidityMappingMode::OFF;

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
            input.values_.push_back(value);
        }
        expected_.commands_.push_back(input);
    }

    {
        OBDCommandInput input;
        input.pid_ = 0x65;
        input.description_ = "Zusätzliche Ein- und Ausgänge";
        input.validity_mapping_mode_ = ValidityMappingMode::AUTO;
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
            input.values_.push_back(value);
        }
        expected_.commands_.push_back(input);
    }
    {
        OBDCommandInput input;
        input.pid_ = 0x70;
        input.description_ = "Ladedruckregelung";
        input.validity_mapping_mode_ = ValidityMappingMode::MANUAL;
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
            input.values_.push_back(value);
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
            input.values_.push_back(value);
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
            input.values_.push_back(value);
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
            input.values_.push_back(value);
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
            input.values_.push_back(value);
        }
        expected_.commands_.push_back(input);
    }
}

void OBDCommandXMLHandlerTest::iterateChildren(const xmlpp::Node* parent)
{
    xmlpp::Node::NodeList children = parent->get_children();
    if(children.empty())
    {
        return;
    }
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        handler_for_test_->handleNode(*it);
        iterateChildren(*it);
    }
}
