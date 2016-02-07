#include "DatabaseXMLHandlerTest.h"
#include "../src/DatabaseXMLHandler.h"

void DatabaseXMLHandlerTest::setUp()
{
    tested_handler_ = new DatabaseXMLHandler();
    doc_ = new xmlpp::Document();
    xmlpp::Element* root = doc_->create_root_node("database");
    xmlpp::Element* el = nullptr;

    el = root->add_child("address");
    el->add_child_text("tcp://testAddress:3306");

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
    std::string expectedAddress = "tcp://testAddress:3306";
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

    CPPUNIT_ASSERT_EQUAL(expectedAddress, tested_handler_->getHostAddress());
    CPPUNIT_ASSERT_EQUAL(expectedPassword, tested_handler_->getPassword());
    CPPUNIT_ASSERT_EQUAL(expectedUser, tested_handler_->getUsername());
    CPPUNIT_ASSERT_EQUAL(expectedDBName, tested_handler_->getDBName());
}

void DatabaseXMLHandlerTest::testWriteHandle()
{
    std::string expectedAddress = "newAddress";
    std::string expectedUser = "newUser";
    std::string expectedPassword = "newPw";
    std::string expectedDBName = "newDBName";

    tested_handler_->setHostAddress(expectedAddress);
    tested_handler_->setUsername(expectedUser);
    tested_handler_->setPassword(expectedPassword);
    tested_handler_->setDBName(expectedDBName);
    tested_handler_->setWriting(true);

    const xmlpp::Node* currentNode = doc_->get_root_node();

    xmlpp::Node::NodeList children = currentNode->get_children();
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        tested_handler_->handleNode(*it);
    }

    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        xmlpp::Element* node = dynamic_cast<xmlpp::Element*>(*it);

        CPPUNIT_ASSERT(node);

        if((*it)->get_name().compare(ADDRESS_TAG) == 0)
        {
            CPPUNIT_ASSERT_EQUAL(expectedAddress, std::string(node->get_child_text()->get_content().c_str()));
        }
        if((*it)->get_name().compare(USER_TAG) == 0)
        {
            CPPUNIT_ASSERT_EQUAL(expectedUser, std::string(node->get_child_text()->get_content().c_str()));
        }
        if((*it)->get_name().compare(PASSWORD_TAG) == 0)
        {
            CPPUNIT_ASSERT_EQUAL(expectedPassword, std::string(node->get_child_text()->get_content().c_str()));
        }
        if((*it)->get_name().compare(DBNAME_TAG) == 0)
        {
            CPPUNIT_ASSERT_EQUAL(expectedDBName, std::string(node->get_child_text()->get_content().c_str()));
        }
    }

}
