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
    CPPUNIT_ASSERT_EQUAL((size_t) 1, handler_for_test_->getParsedData().size());
    CPPUNIT_ASSERT_EQUAL(expected_.sid_.size(),
            handler_for_test_->getParsedData().at(0).sid_.size());
    CPPUNIT_ASSERT_EQUAL(expected_.sid_.at(0),
                handler_for_test_->getParsedData().at(0).sid_.at(0));
    CPPUNIT_ASSERT_EQUAL(expected_.sid_.at(1),
                    handler_for_test_->getParsedData().at(0).sid_.at(1));
}

void OBDCommandXMLHandlerTest::testPureValueCommand()
{
//    CPP
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
    doc_ = new xmlpp::Document();
    xmlpp::Element* root = doc_->create_root_node("servicemodes");

    xmlpp::Element* service_mode = nullptr;

    service_mode = root->add_child("servicemode");
    addChildWithText(service_mode, "sid", "1");
    addChildWithText(service_mode, "sid", "2");
    xmlpp::Element* commands = service_mode->add_child("obdcommands");
    {
        xmlpp::Element* command = commands->add_child("obdcommand");

        addChildWithText(command, "pid", "66");
        addChildWithText(command, "description", "Luftmassenmesser");
        addChildWithText(command, "validitymapping", "true");

        xmlpp::Element* values = command->add_child("values");
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "calculation");

            addChildWithText(value, "name", "MAF Sensor A");
            addChildWithText(value, "bytes", "2");
            addChildWithText(value, "min", "0");
            addChildWithText(value, "max", "2047,96875");
            addChildWithText(value, "unit", "g/s");
        }
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "calculation");

            addChildWithText(value, "name", "MAF Sensor B");
            addChildWithText(value, "bytes", "2");
            addChildWithText(value, "min", "0");
            addChildWithText(value, "max", "2047,96875");
            addChildWithText(value, "unit", "g/s");
        }
    }

    {
        xmlpp::Element* command = commands->add_child("obdcommand");

        addChildWithText(command, "pid", "5F");
        addChildWithText(command, "description",
                "Für das Fahrzeug gültige Abgasnorm");

        xmlpp::Element* values = command->add_child("values");
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "mapping");

            addChildWithText(value, "bytes", "1");
            xmlpp::Element* mapping = value->add_child("mapping");
            mapping->set_attribute("type", "value");
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "LKW (Euro IV) B1");
                entry->set_attribute("from", "0E");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "LKW (Euro V) B2");
                entry->set_attribute("from", "0F");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "LKW (Euro EEV) C");
                entry->set_attribute("from", "10");
            }
        }
    }

    {
        xmlpp::Element* command = commands->add_child("obdcommand");

        addChildWithText(command, "pid", "65");
        addChildWithText(command, "description",
                "Zusätzliche Ein- und Ausgänge");
        xmlpp::Element* validity = addChildWithText(command, "validitymapping",
                "true");
        validity->set_attribute("mode", "auto");

        xmlpp::Element* values = command->add_child("values");
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "mapping");

            addChildWithText(value, "bytes", "1");
            xmlpp::Element* mapping = value->add_child("mapping");
            mapping->set_attribute("type", "bit");
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Kraftaufnahme inaktiv");
                entry->set_attribute("from", "0");
                entry->set_attribute("set", "false");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Kraftaufnahme aktiv");
                entry->set_attribute("from", "0");
                entry->set_attribute("set", "true");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Automatikgetriebe in Park-/Neutralstellun");
                entry->set_attribute("from", "1");
                entry->set_attribute("set", "false");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Vorwärts- oder Rückwärtsgang");
                entry->set_attribute("from", "1");
                entry->set_attribute("set", "true");
            }
            {
                xmlpp::Element* entry =
                        addChildWithText(mapping, "entry",
                                "Manuelles Getriebe in Neutralstellung und/oder Kupplung getreten");
                entry->set_attribute("from", "2");
                entry->set_attribute("set", "false");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Gang eingelegt");
                entry->set_attribute("from", "2");
                entry->set_attribute("set", "true");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Vorglühlampe aus");
                entry->set_attribute("from", "3");
                entry->set_attribute("set", "false");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Lampe ein");
                entry->set_attribute("from", "3");
                entry->set_attribute("set", "true");
            }
        }
    }
    {
        xmlpp::Element* command = commands->add_child("obdcommand");

        addChildWithText(command, "pid", "70");
        addChildWithText(command, "description", "Ladedruckregelung");
        xmlpp::Element* validity = addChildWithText(command, "validitymapping",
                "true");
        validity->set_attribute("mode", "manual");

        xmlpp::Element* values = command->add_child("values");
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "calculation");

            addChildWithText(value, "name", "Soll Ladedruck A");
            addChildWithText(value, "bytes", "2");
            addChildWithText(value, "min", "0");
            addChildWithText(value, "max", "2047,96875");
            addChildWithText(value, "unit", "kPa");
            addChildWithText(value, "validitybit", "0");
        }
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "calculation");

            addChildWithText(value, "name", "Ist Ladedruck A");
            addChildWithText(value, "bytes", "2");
            addChildWithText(value, "min", "0");
            addChildWithText(value, "max", "2047,96875");
            addChildWithText(value, "unit", "kPa");
            addChildWithText(value, "validitybit", "1");
        }
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "calculation");

            addChildWithText(value, "name", "Soll Ladedruck B");
            addChildWithText(value, "bytes", "2");
            addChildWithText(value, "min", "0");
            addChildWithText(value, "max", "2047,96875");
            addChildWithText(value, "unit", "kPa");
            addChildWithText(value, "validitybit", "3");
        }
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "calculation");

            addChildWithText(value, "name", "Ist Ladedruck B");
            addChildWithText(value, "bytes", "2");
            addChildWithText(value, "min", "0");
            addChildWithText(value, "max", "2047,96875");
            addChildWithText(value, "unit", "kPa");
            addChildWithText(value, "validitybit", "4");
        }
        {
            xmlpp::Element* value = values->add_child("value");
            value->set_attribute("interpretation", "mapping");

            addChildWithText(value, "bytes", "1");
            xmlpp::Element* mapping = value->add_child("mapping");
            mapping->set_attribute("type", "bitcombination");
            {
                xmlpp::Element* validity = addChildWithText(mapping,
                        "validitybit", "2");
                validity->set_attribute("from", "01");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Offener Kreislauf, kein Fehler");
                entry->set_attribute("from", "01");
                entry->set_attribute("set", "01");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Geschlossener Kreislauf, kein Fehler");
                entry->set_attribute("from", "01");
                entry->set_attribute("set", "10");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Fehler vorhanden, Wert unzuverlässig");
                entry->set_attribute("from", "01");
                entry->set_attribute("set", "11");
            }

            {
                xmlpp::Element* validity = addChildWithText(mapping,
                        "validitybit", "5");
                validity->set_attribute("from", "23");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Offener Kreislauf, kein Fehler");
                entry->set_attribute("from", "23");
                entry->set_attribute("set", "01");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Geschlossener Kreislauf, kein Fehler");
                entry->set_attribute("from", "23");
                entry->set_attribute("set", "10");
            }
            {
                xmlpp::Element* entry = addChildWithText(mapping, "entry",
                        "Fehler vorhanden, Wert unzuverlässig");
                entry->set_attribute("from", "23");
                entry->set_attribute("set", "11");
            }
        }
    }

    for(xmlpp::Node::NodeList::iterator it =
            doc_->get_root_node()->get_children().begin();
            it != doc_->get_root_node()->get_children().end(); ++it)
    {
        iterateChildren(*it);
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

    std::cout << expect
}

void OBDCommandXMLHandlerTest::iterateChildren(const xmlpp::Node* parent)
{
    xmlpp::Node::NodeList children = parent->get_children();
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        handler_for_test_->handleNode(*it);
        iterateChildren(*it);
    }
}
