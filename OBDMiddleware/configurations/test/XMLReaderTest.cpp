#include "XMLReaderTest.h"
#include "../src/XMLReader.h"
#include <algorithm>
#include <iostream>

MockHandlerReaderTest::MockHandlerReaderTest()
{
}

void MockHandlerReaderTest::handleNode(xmlpp::Node* node)
{
    CPPUNIT_ASSERT(std::any_of(containedTags.begin(), containedTags.end(),
            [node](std::string &s)->bool
                        {
                            return s.compare(node->get_name()) == 0;
                        }
    ));
    notOccured.erase(std::remove_if(notOccured.begin(), notOccured.end(),
            [node](std::string &s)->bool
                        {
                            return s.compare(node->get_name()) == 0;
                        }
    ), notOccured.end());
}

void XMLReaderTest::setUp()
{
    mockhandler_ = new MockHandlerReaderTest();
    xmlreader_under_test_ = new XMLReader(mockhandler_);
}

void XMLReaderTest::tearDown()
{
    delete mockhandler_;
    delete xmlreader_under_test_;
}

void XMLReaderTest::testParseFile()
{
    CPPUNIT_ASSERT(
            xmlreader_under_test_->parseFile(
                    "../test/testdata/dbconfiguration.xml"));
    unsigned int acutalNotOccured = mockhandler_->getNotOccured().size();
    CPPUNIT_ASSERT_EQUAL((unsigned int) 0, acutalNotOccured);
}

