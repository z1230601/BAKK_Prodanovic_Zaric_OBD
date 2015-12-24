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
    std::string expectedBaseCommand = "@1";
    std::string expectedDescription = "display the device description";
    std::string expectedGroup = "General";

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedBaseCommand, command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testCommandWithOneValue() {
    float expectedMinimumRequiredElmVersion = 1.1;
    std::string expectedBaseCommand = "FC SM";
    std::string expectedBaseValue = "A";
    std::string expectedDescription = "Flow Control Set the Mode to h";
    std::string expectedGroup = "CAN";
    std::string expectedBaseValueFormat = "h";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedBaseCommand, expectedDescription, expectedGroup, expectedBaseValueFormat);

    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedBaseCommand + " " + expectedBaseValue, command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testCommandWithTwoDigitValue()
{
    float expectedMinimumRequiredElmVersion = 1.2;
    std::string expectedBaseCommand = "BRD";
    std::string expectedBaseValue = "12";
    std::string expectedDescription = "try Baud rate Divisor hh";
    std::string expectedGroup = "General";
    std::string expectedBaseValueFormat = "hh";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedBaseCommand, expectedDescription, expectedGroup, expectedBaseValueFormat);
    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedBaseCommand + " " + expectedBaseValue, command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testCommandWithThreeDigitValue()
{
    float expectedMinimumRequiredElmVersion = 1.1;
    std::string expectedBaseCommand = "FC SH";
    std::string expectedBaseValue = "ABC";
    std::string expectedDescription = "Flow Control Set the Header to hhh";
    std::string expectedGroup = "CAN";
    std::string expectedBaseValueFormat = "hhh";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedBaseCommand, expectedDescription, expectedGroup, expectedBaseValueFormat);
    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedBaseCommand + " " + expectedBaseValue,
            command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testCommandWithEightDigitValue()
{
    float expectedMinimumRequiredElmVersion = 1.1;
    std::string expectedBaseCommand = "FC SH";
    std::string expectedBaseValue = "12345678";
    std::string expectedDescription = "Flow Control Set the Header to hhhhhhhh";
    std::string expectedGroup = "CAN";
    std::string expectedBaseFormat = "hhhhhhhh";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedBaseCommand, expectedDescription, expectedGroup,
            expectedBaseFormat);
    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedBaseCommand + " " + expectedBaseValue,
            command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ElmCommandTest::testInvalidValueString() {
    CPPUNIT_ASSERT(command_for_test_->isValidValue("AB12CD34"));
    CPPUNIT_ASSERT(!command_for_test_->isValidValue("ABCZlatan"));
    CPPUNIT_ASSERT(!command_for_test_->isValidValue("123 456"));
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

void ElmCommandTest::testValueWrappedWithCommands() {
    float expectedMinimumRequiredElmVersion = 1.1;
    std::string expectedBaseCommand = "PP";
    std::string expectedBaseValue = "1F";
    std::string expectedDescription = "disable Prog Parameter xx";
    std::string expectedGroup = "PPs";
    std::string expectedBaseFormat = "xx";
    std::string expectedSubCommand = "OFF";

    command_for_test_ = new ElmCommand(expectedMinimumRequiredElmVersion,
            expectedBaseCommand, expectedDescription, expectedGroup,
            expectedBaseFormat, expectedSubCommand);
    command_for_test_->setBaseValue(expectedBaseValue);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
                command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedBaseCommand + " " + expectedBaseValue + " " + expectedSubCommand,
                command_for_test_->getCompleteCommandAsString());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
                command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());

}

void ElmCommandTest::testCommandAndSubcommandWithValues() {

}
