#include "DatabaseXMLHandlerTest.h"
#include "../src/DatabaseXMLHandler.h"

void DatabaseXMLHandlerTest::setUp()
{
    tested_handler_ = new DatabaseXMLHandler();
    doc_ = new xmlpp::Document();
    xmlpp::Element* root = doc_->create_root_node("database");
    xmlpp::Element* el = nullptr;

    el = root->add_child("address");
    el->add_child_text("testAddress");

    el = root->add_child("user");
    el->add_child_text("testUser");

    el = root->add_child("password");
    el->add_child_text("testPw");

    el = root->add_child("dbname");
    el->add_child_text("testDBName");
}

void DatabaseXMLHandlerTest::tearDown()
{
    delete doc_;
    delete tested_handler_;
}

void DatabaseXMLHandlerTest::testHandle()
{
    std::string expectedAddress = "testAddress";
    std::string expectedUser = "testUser";
    std::string expectedPassword = "testPw";
    std::string expectedDBName = "testDBName";

    const xmlpp::Node* currentNode = doc_->get_root_node();

    xmlpp::Node::NodeList children = currentNode->get_children();
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        tested_handler_->handleNode(*it);
    }

    CPPUNIT_ASSERT_EQUAL("tcp://" + expectedAddress + ":3306",
            tested_handler_->getHostAddress());
    CPPUNIT_ASSERT_EQUAL(expectedPassword, tested_handler_->getPassword());
    CPPUNIT_ASSERT_EQUAL(expectedUser, tested_handler_->getUsername());
    CPPUNIT_ASSERT_EQUAL(expectedDBName, tested_handler_->getDBName());
}
