#include "ValueElmCommandTest.h"
#include "../src/ValueElmCommand.h"

void ValueElmCommandTest::setUp() {
    command_for_test_ = new ValueElmCommand();
}

void ValueElmCommandTest::tearDown() {
	delete command_for_test_;
}

void ValueElmCommandTest::testCommandWithoutValue() {
    float expectedMinimumRequiredElmVersion = 1.0;
    std::string expectedCommand = "@1";
    std::string expectedDescription = "display the device description";
    std::string expectedGroup = "General";

    command_for_test_ = new ValueElmCommand(expectedMinimumRequiredElmVersion,
            expectedCommand, expectedDescription, expectedGroup);

    CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
            command_for_test_->getMinimumRequiredElmVersion());
    CPPUNIT_ASSERT_EQUAL(expectedCommand, command_for_test_->getCommand());
    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            command_for_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ValueElmCommandTest::testCommandWithOneValue() {
	float expectedMinimumRequiredElmVersion = 1.1;
	std::string expectedCommand = "FC SM";
	std::string expectedValue = "A";
	std::string expectedDescription = "Flow Control Set the Mode to h";
	std::string expectedGroup = "CAN";
	std::string expectedFormat = "h";

	command_for_test_ = new ValueElmCommand(expectedMinimumRequiredElmVersion,
			expectedCommand, expectedValue, expectedDescription, expectedGroup,
			expectedFormat);

	CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
			command_for_test_->getMinimumRequiredElmVersion());
	CPPUNIT_ASSERT_EQUAL(expectedCommand, command_for_test_->getCommand());
	CPPUNIT_ASSERT_EQUAL(expectedValue, command_for_test_->getValueAsString());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			command_for_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ValueElmCommandTest::testCommandWithTwoValues() {
	float expectedMinimumRequiredElmVersion = 1.2;
	std::string expectedCommand = "BRD";
	std::string expectedValue = "12";
	std::string expectedDescription = "try Baud rate Divisor hh";
	std::string expectedGroup = "General";
	std::string expectedFormat = "hh";

	command_for_test_ = new ValueElmCommand(expectedMinimumRequiredElmVersion,
			expectedCommand, expectedValue, expectedDescription, expectedGroup,
			expectedFormat);

	CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
			command_for_test_->getMinimumRequiredElmVersion());
	CPPUNIT_ASSERT_EQUAL(expectedCommand, command_for_test_->getCommand());
	CPPUNIT_ASSERT_EQUAL(expectedValue, command_for_test_->getValueAsString());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			command_for_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ValueElmCommandTest::testCommandWithThreeValues() {
	float expectedMinimumRequiredElmVersion = 1.1;
	std::string expectedCommand = "FC SH";
	std::string expectedValue = "ABC";
	std::string expectedDescription = "Flow Control Set the Header to hhh";
	std::string expectedGroup = "CAN";
	std::string expectedFormat = "hhh";

	command_for_test_ = new ValueElmCommand(expectedMinimumRequiredElmVersion,
			expectedCommand, expectedValue, expectedDescription, expectedGroup,
			expectedFormat);

	CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
			command_for_test_->getMinimumRequiredElmVersion());
	CPPUNIT_ASSERT_EQUAL(expectedCommand, command_for_test_->getCommand());
	CPPUNIT_ASSERT_EQUAL(expectedValue, command_for_test_->getValueAsString());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			command_for_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void ValueElmCommandTest::testCommandWithEightValues() {
	float expectedMinimumRequiredElmVersion = 1.1;
	std::string expectedCommand = "FC SH";
	std::string expectedValue = "12345678";
	std::string expectedDescription = "Flow Control Set the Header to hhhhhhhh";
	std::string expectedGroup = "CAN";
	std::string expectedFormat = "hhhhhhhh";

	command_for_test_ = new ValueElmCommand(expectedMinimumRequiredElmVersion,
			expectedCommand, expectedValue, expectedDescription, expectedGroup,
			expectedFormat);

	CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
			command_for_test_->getMinimumRequiredElmVersion());
	CPPUNIT_ASSERT_EQUAL(expectedCommand, command_for_test_->getCommand());
	CPPUNIT_ASSERT_EQUAL(expectedValue, command_for_test_->getValueAsString());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			command_for_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

