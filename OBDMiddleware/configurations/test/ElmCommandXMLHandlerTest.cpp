#include "ElmCommandXMLHandlerTest.h"
#include "../src/ElmCommandXMLHandler.h"
#include <string>

void ElmCommandXMLHandlerTest::setUp()
{
    tested_handler_ = new ElmCommandXMLHandler();
    doc_ = new xmlpp::Document();

    xmlpp::Element* root = doc_->create_root_node("commands");
    xmlpp::Element* command_node = nullptr;
    xmlpp::Element* command_child = nullptr;

    command_node = root->add_child("command");
    command_child = command_node->add_child("version");
    command_child->add_child_text("1.0");

    command_child = command_node->add_child("elmcommand");
    command_child->add_child_text("@1");

    command_child = command_node->add_child("description");
    command_child->add_child_text("display the device description");

    command_child = command_node->add_child("group");
    command_child->add_child_text("General");

    command_child = command_node->add_child("valueformat");
    command_child->add_child_text("");
}

void ElmCommandXMLHandlerTest::tearDown()
{
    delete doc_;
    delete tested_handler_;
}

void ElmCommandXMLHandlerTest::testHandle()
{
    float expectedMinVersion = 1.0;
    std::string expectedBaseCommand = "@1";
    std::string expectedDescription = "display the device description";
    std::string expectedGroup = "General";
    std::string expectedBaseValueFormat = "";
    std::string expectedSubCommand = "";
    std::string expectedSubValueFormat = "";

    const xmlpp::Node* currentNode = doc_->get_root_node();

    xmlpp::Node::NodeList children = currentNode->get_children();
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        tested_handler_->handleNode(*it);
    }

    CPPUNIT_ASSERT_EQUAL(expectedMinVersion, tested_handler_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedBaseCommand, tested_handler_->getBaseCommand());
    CPPUNIT_ASSERT_EQUAL(expectedDescription, tested_handler_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, tested_handler_->getGroup());
    CPPUNIT_ASSERT_EQUAL(expectedBaseValueFormat, tested_handler_->getBaseValueFormat());
    CPPUNIT_ASSERT_EQUAL(expectedSubCommand,tested_handler_->getSubCommand());
    CPPUNIT_ASSERT_EQUAL(expectedSubValueFormat,tested_handler_->getSubValueFormat());
}
