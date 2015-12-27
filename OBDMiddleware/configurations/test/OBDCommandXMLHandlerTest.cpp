#include "OBDCommandXMLHandlerTest.h"
#include "../src/OBDCommandInputDefinitions.h"

#include <iostream>

void OBDCommandXMLHandlerTest::setUp()
{
    handler_for_test_ = new OBDCommandXMLHandler();
    try
    {
        parser_.set_substitute_entities();
        parser_.set_validate();
        parser_.parse_file("../test/testdata/obdcommand.xml");
        if(parser_)
        {
            parser_.get_document()->get_root_node();
        }
    } catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
    }
}

void OBDCommandXMLHandlerTest::tearDown()
{
    delete handler_for_test_;
}

void OBDCommandXMLHandlerTest::testServiceModeParse()
{
    std::cout << parser_.get_document()->write_to_string() << std::endl;
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

