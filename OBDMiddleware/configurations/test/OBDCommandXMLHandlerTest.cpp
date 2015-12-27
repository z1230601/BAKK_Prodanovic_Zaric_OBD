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
    try{
        std::cout << doc_->write_to_string() << std::endl;
    }catch(std::exception &e){
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

//    xmlpp::Node* first_service_mode_tag;
//
//    for(xmlpp::Node::NodeList::iterator it = parser_.get_document()
//            ->get_root_node()->get_children().begin();
//            it != parser_.get_document()->get_root_node()->get_children().end();
//            ++it)
//    {
//        if((*it)->get_name().compare("servicemode") == 0){
////            first_service_mode_tag = (*it);
//            break;
//        }
//    }
//
//    std::cout << "First service mode tag is:" << std::endl;
//    std::cout << first_service_mode_tag->get_name() << std::endl;
//    xmlpp::Node::NodeList
//    root_children = first_service_mode_tag->get_children();
//
//    std::cout << first_service_mode_tag->get_name() << std::endl;
//    handler_for_test_->handleNode(first_service_mode_tag);
//
//    for(xmlpp::Node::NodeList::iterator it = root_children.begin();
//            it != root_children.end(); ++it)
//    {
//        std::cout << (*it)->get_name() << std::endl;
//        if((*it)->get_name().compare("obdcommands") == 0)
//        {
//            break;
//        }
//
//        handler_for_test_->handleNode(*it);
//
//    }
//
//    CPPUNIT_ASSERT_EQUAL((size_t) 1, handler_for_test_->getParsedData().size());
//    CPPUNIT_ASSERT_EQUAL((size_t) 2,
//            handler_for_test_->getParsedData().at(0).sid_.size());
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
}
