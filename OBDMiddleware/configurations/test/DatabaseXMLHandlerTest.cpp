#include "DatabaseXMLHandlerTest.h"
#include "../src/DatabaseXMLHandler.h"


void DatabaseXMLHandlerTest::setUp()
{
    tested_handler_ = new DatabaseXMLHandler();
    doc_ = new xmlpp::Document();
    xmlpp::Element* root = doc_->create_root_node("database");
    xmlpp::Element* el = nullptr;

    el = root->add_child("address");
    el->add_child_text(expected_address.c_str());

    el = root->add_child("user");
    el->add_child_text(expected_user.c_str());

    el = root->add_child("password");
    el->add_child_text(expected_password.c_str());

    el = root->add_child("dbname");
    el->add_child_text(expected_db_name.c_str());
}

void DatabaseXMLHandlerTest::tearDown()
{
    delete doc_;
    delete tested_handler_;
}

void DatabaseXMLHandlerTest::testHandle()
{
    const xmlpp::Node* currentNode = doc_->get_root_node();

    xmlpp::Node::NodeList children = currentNode->get_children();
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        tested_handler_->handleNode(*it);
    }

    CPPUNIT_ASSERT_EQUAL("tcp://" + expected_address + ":3306",  tested_handler_->getHostAddress());
    CPPUNIT_ASSERT_EQUAL(expected_password, tested_handler_->getPassword());
    CPPUNIT_ASSERT_EQUAL(expected_user,     tested_handler_->getUsername());
    CPPUNIT_ASSERT_EQUAL(expected_db_name,  tested_handler_->getDBName());
}
