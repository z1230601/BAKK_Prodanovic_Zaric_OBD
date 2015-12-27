#include "ElmCommandXMLHandlerTest.h"
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

    command_child = command_node->add_child("basecommand");
    command_child->add_child_text("@1");

    command_child = command_node->add_child("description");
    command_child->add_child_text("display the device description");

    command_child = command_node->add_child("group");
    command_child->add_child_text("General");

    command_child = command_node->add_child("basevalueformat");
    command_child->add_child_text("");

    command_child = command_node->add_child("subcommand");
    command_child->add_child_text("");

    command_child = command_node->add_child("subvalueformat");
    command_child->add_child_text("");

    //---------------------------------------------------------------

    command_node = root->add_child("command");
    command_child = command_node->add_child("version");
    command_child->add_child_text("1.1");

    command_child = command_node->add_child("basecommand");
    command_child->add_child_text("@2");

    command_child = command_node->add_child("description");
    command_child->add_child_text("display the device description2");

    command_child = command_node->add_child("group");
    command_child->add_child_text("General");

}

void ElmCommandXMLHandlerTest::tearDown()
{
    delete doc_;
    delete tested_handler_;
}


void ElmCommandXMLHandlerTest::iterateChildren(const xmlpp::Node* parent)
{
    xmlpp::Node::NodeList children = parent->get_children();
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        tested_handler_->handleNode(*it);
        iterateChildren(*it);
    }
}


void ElmCommandXMLHandlerTest::testHandle()
{
    std::vector<ElmCommandInput> expectedElmCommands;
    expectedElmCommands.push_back(
            ElmCommandInput(1.0, "@1", "display the device description",
                    "General", "", "", ""));
    expectedElmCommands.push_back(
            ElmCommandInput(1.1, "@2", "display the device description2",
                    "General", "", "",""));

    iterateChildren(doc_->get_root_node());


    CPPUNIT_ASSERT_EQUAL(expectedElmCommands.size(), tested_handler_->getParsedCommands().size());
    for(unsigned int i = 0; i < expectedElmCommands.size(); i++) {
        CPPUNIT_ASSERT_EQUAL(expectedElmCommands.at(i).basecommand_, tested_handler_->getParsedCommands().at(i).basecommand_);
        CPPUNIT_ASSERT_EQUAL(expectedElmCommands.at(i).basevalueformat_, tested_handler_->getParsedCommands().at(i).basevalueformat_);
        CPPUNIT_ASSERT_EQUAL(expectedElmCommands.at(i).description_, tested_handler_->getParsedCommands().at(i).description_);
        CPPUNIT_ASSERT_EQUAL(expectedElmCommands.at(i).group_, tested_handler_->getParsedCommands().at(i).group_);
        CPPUNIT_ASSERT_EQUAL(expectedElmCommands.at(i).subcommand_, tested_handler_->getParsedCommands().at(i).subcommand_);
        CPPUNIT_ASSERT_EQUAL(expectedElmCommands.at(i).subvalueformat_, tested_handler_->getParsedCommands().at(i).subvalueformat_);
        CPPUNIT_ASSERT_EQUAL(expectedElmCommands.at(i).version_, tested_handler_->getParsedCommands().at(i).version_);
    }
}
