#include "ElmCommandTest.h"
#include "../src/ElmCommand.h"

void ElmCommandTest::setUp() {
    command_for_test_ = new ElmCommand(1.0, "@1",
            "display the device description", "General");
}

void ElmCommandTest::tearDown() {
    delete command_for_test_;
}

void ElmCommandTest::testCommandWithoutValue() {
    float expectedMinimumRequiredElmVersion = 1.0;
    std::string expectedCommand = "@1";
    std::string expectedDescription = "display the device description";
    std::string expectedGroup = "General";

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedCommand, command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testCommandWithOneValue() {
    float expectedMinimumRequiredElmVersion = 1.1;
    std::string expectedCommand = "FC SM";
    std::string expectedBaseValue = "A";
    std::string expectedDescription = "Flow Control Set the Mode to h";
    std::string expectedGroup = "CAN";
    std::string expectedBaseValueFormat = "h";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedCommand, expectedDescription, expectedGroup, expectedBaseValueFormat);

    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedCommand + " " + expectedBaseValue, command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testCommandWithTwoDigitValue()
{
    float expectedMinimumRequiredElmVersion = 1.2;
    std::string expectedCommand = "BRD";
    std::string expectedBaseValue = "12";
    std::string expectedDescription = "try Baud rate Divisor hh";
    std::string expectedGroup = "General";
    std::string expectedBaseValueFormat = "hh";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedCommand, expectedDescription, expectedGroup, expectedBaseValueFormat);
    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedCommand + " " + expectedBaseValue, command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testCommandWithThreeDigitValue()
{
    float expectedMinimumRequiredElmVersion = 1.1;
    std::string expectedCommand = "FC SH";
    std::string expectedBaseValue = "ABC";
    std::string expectedDescription = "Flow Control Set the Header to hhh";
    std::string expectedGroup = "CAN";
    std::string expectedBaseValueFormat = "hhh";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedCommand, expectedDescription, expectedGroup, expectedBaseValueFormat);
    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedCommand + " " + expectedBaseValue,
            command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testCommandWithEightDigitValue()
{
    float expectedMinimumRequiredElmVersion = 1.1;
    std::string expectedCommand = "FC SH";
    std::string expectedBaseValue = "12345678";
    std::string expectedDescription = "Flow Control Set the Header to hhhhhhhh";
    std::string expectedGroup = "CAN";
    std::string expectedBaseFormat = "hhhhhhhh";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedCommand, expectedDescription, expectedGroup,
            expectedBaseFormat);
    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedCommand + " " + expectedBaseValue,
            command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testInvalidValueString() {
    CPPUNIT_ASSERT(!command_for_test_->isValidValue("z"));
    CPPUNIT_ASSERT(command_for_test_ -> isValidValue("123456789aBcDEF"));
    CPPUNIT_ASSERT(!command_for_test_ -> isValidValue("1234Q56789aBcDEF"));
}

void ElmCommandTest::testFormatValueCheck(){
    command_for_test_ = new ElmCommand(1.0, "@1",
                "display the device description", "General", "hhhhhh n", "SV", "cccccccccc");

    //not fail check
    CPPUNIT_ASSERT(command_for_test_->checkBaseValueToFormat("FEDCBA 9"));
    CPPUNIT_ASSERT(command_for_test_->checkSubValueToFormat("HELLOWORLD"));

    //fail check
    CPPUNIT_ASSERT(!command_for_test_->checkBaseValueToFormat("FE CBA"));
    CPPUNIT_ASSERT(!command_for_test_->checkSubValueToFormat("hello world!"));
    CPPUNIT_ASSERT(!command_for_test_->checkBaseValueToFormat("hello world!"));
}
