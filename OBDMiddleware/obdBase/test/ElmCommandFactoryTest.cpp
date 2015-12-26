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
    expected.push_back(new ElmCommand(1.3,"CRA","hhhhhhhh","set CAN Receive Address to hhhhhhhh","CAN"));
    expected.push_back(new ElmCommand(1.4,"PB","xx yy","set Protocol B options and baud rate","CAN"));
    expected.push_back(new ElmCommand(1.1,"PP","for PP xx, Set the Value to yy","PPs","xx","SV","yy"));

    std::vector<ElmCommand* > acutalCommand = ElmCommandFactory::createElmCommands("../test/testdata/elmcommandconfigurationTest.xml");

    CPPUNIT_ASSERT_EQUAL(expected.size(), acutalCommand.size());

    for(unsigned int i = 0; i < expected.size();  i ++){
        CPPUNIT_ASSERT_EQUAL(expected.at(i)->getCompleteCommandAsString(),
                acutalCommand.at(i)->getCompleteCommandAsString());
    }
}

