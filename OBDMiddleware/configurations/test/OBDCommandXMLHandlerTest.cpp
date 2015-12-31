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
    xmlpp::Element* rootNode = nullptr;
    try
    {
        xmlpp::DomParser parser;
        parser.set_substitute_entities();
        parser.set_validate();
        parser.parse_file("../test/testdata/obdcommand.xml");
        if(parser)
        {
            rootNode = parser.get_document()->get_root_node();
        }
    } catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }

    for(xmlpp::Node::NodeList::iterator it =
            rootNode->get_children().begin();
            it != rootNode->get_children().end(); ++it)
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
