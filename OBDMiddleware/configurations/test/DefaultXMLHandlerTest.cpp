#include "DefaultXMLHandlerTest.h"
#include "../src/DefaultXMLHandler.h"
#include <iostream>

MockHandlerHandlerTest::MockHandlerHandlerTest()
{
}

void MockHandlerHandlerTest::handleNode(xmlpp::Node* node)
{

}

std::string MockHandlerHandlerTest::getTextFromNodeForTest(xmlpp::Node* node)
{
    return getTextFromNode(node);
}

void DefaultXMLHandlerTest::setUp()
{
    doc = new xmlpp::Document();
    xmlpp::Element* root = doc->create_root_node("RootNode");
    node_for_test_ = root->add_child("test");
    dynamic_cast<xmlpp::Element*>(node_for_test_)->add_child_text(
            "testingText");
}

void DefaultXMLHandlerTest::tearDown()
{
    delete doc;
}

void DefaultXMLHandlerTest::testGetTextNode()
{
    MockHandlerHandlerTest mock_handler;
    std::string expectedContent = "testingText";
    CPPUNIT_ASSERT_EQUAL(expectedContent,
            mock_handler.getTextFromNodeForTest(node_for_test_));
}

void DefaultXMLHandlerTest::testWrongNode()
{
    MockHandlerHandlerTest mock_handler;
    std::string expectedContent = "";
    CPPUNIT_ASSERT_EQUAL(expectedContent,
            mock_handler.getTextFromNodeForTest(doc->get_root_node()));
}
