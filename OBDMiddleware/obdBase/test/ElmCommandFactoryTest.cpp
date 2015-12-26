#include "ElmCommandFactoryTest.h"
#include "../src/ElmCommandFactory.h"
#include "../src/ElmCommand.h"

void ElmCommandFactoryTest::setUp() {

}

void ElmCommandFactoryTest::tearDown() {

}

void ElmCommandFactoryTest::testFactory() {
    std::vector<ElmCommand*> expected;
    expected.push_back(new ElmCommand(1.3 ,"@3","store the device identifier","General","cccccccccccc"));
    expected.push_back(new ElmCommand(1.0,"<CR>","repeat the last command","General"));
    expected.push_back(new ElmCommand(1.3,"CRA","set CAN Receive Address to hhhhhhhh","CAN","hhhhhhhh"));
    expected.push_back(new ElmCommand(1.4,"PB","set Protocol B options and baud rate","CAN","xx yy"));
    expected.push_back(new ElmCommand(1.1,"PP","for PP xx, Set the Value to yy","PPs","xx","SV","yy"));

    std::vector<ElmCommand* > actualCommand = ElmCommandFactory::createElmCommands("../test/testdata/elmcommandconfigurationTest.xml");

    CPPUNIT_ASSERT_EQUAL(expected.size(), actualCommand.size());

    for(unsigned int i = 0; i < expected.size();  i ++){
        CPPUNIT_ASSERT_EQUAL(expected.at(i)->getCompleteCommandAsString(),
                actualCommand.at(i)->getCompleteCommandAsString());
        CPPUNIT_ASSERT_EQUAL(expected.at(i)->getDescription(), actualCommand.at(i)->getDescription());
        CPPUNIT_ASSERT_EQUAL(expected.at(i)->getGroup(), actualCommand.at(i)->getGroup());
        CPPUNIT_ASSERT_EQUAL(expected.at(i)->getMinimumRequiredElmVersion(), actualCommand.at(i)->getMinimumRequiredElmVersion());
    }

    for(unsigned int i = 0; i < expected.size();  i ++){
        delete expected.at(i);
        delete actualCommand.at(i);
    }
}

