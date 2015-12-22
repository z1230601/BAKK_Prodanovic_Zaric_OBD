#include "SimpleElmCommandTest.h"
#include "../src/SimpleElmCommand.h"

void SimpleElmCommandTest::setUp() {
	command_for_test_ = new SimpleElmCommand(0.0, "bogey", "some bogus command",
			"OBD");
}

void SimpleElmCommandTest::tearDown() {
	delete command_for_test_;
}

void SimpleElmCommandTest::testSimpleCommandCreation() {
	float expectedMinimumRequiredElmVersion = 1.0;
	std::string expectedCommand = "@1";
	std::string expectedDescription = "display the device description";
	std::string expectedGroup = "General";

	command_for_test_ = new SimpleElmCommand(expectedMinimumRequiredElmVersion,
			expectedCommand, expectedDescription, expectedGroup);

	CPPUNIT_ASSERT_EQUAL(expectedMinimumRequiredElmVersion,
			command_for_test_->getMinimumRequiredElmVersion());
	CPPUNIT_ASSERT_EQUAL(expectedCommand, command_for_test_->getCommand());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			command_for_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedGroup, command_for_test_->getGroup());
}

void SimpleElmCommandTest::testCommandConversionToSerial() {
	uint8_t expected[] = { 98, 111, 103, 101, 121 };
	uint8_t* actual = command_for_test_->getCommandAsByteArray();
	CPPUNIT_ASSERT(actual != NULL);
	CPPUNIT_ASSERT_EQUAL((unsigned int) 5,
			command_for_test_->getCommandLength());

	for (int i = 0; i < 5; i++) {
		CPPUNIT_ASSERT_EQUAL(expected[i], actual[i]);
	}

	delete actual;
}
