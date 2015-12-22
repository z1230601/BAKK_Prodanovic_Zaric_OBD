#include "ValueElmCommandTest.h"
#include "../src/ValueElmCommand.h"

void ValueElmCommandTest::setUp() {

}

void ValueElmCommandTest::tearDown() {
	delete command_for_test_;
}

void ValueElmCommandTest::testCommandWithValues() {
	float expectedMinimumRequiredElmVersion = 1.2;
	std::string expectedCommand = "BRD";
	unsigned int expectedValue = 0x12;
	std::string expectedDescription = "try Baud rate Divisor hh";
	std::string expectedGroup = "General";

	command_for_test_ = new ValueElmCommand(expectedMinimumRequiredElmVersion,
			expectedCommand, expectedValue, expectedDescription,
			expectedGroup);

	CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
			command_for_test_->getMinimumRequiredElmVersion());
	CPPUNIT_ASSERT_EQUAL(expectedCommand, command_for_test_->getCommand());
	CPPUNIT_ASSERT_EQUAL(expectedValues, command_for_test_->getSingleValue());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			command_for_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

