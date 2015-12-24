#include "SimpleElmCommandTest.h"
#include "../src/SimpleElmCommand.h"

void SimpleElmCommandTest::setUp() {
	command_for_test_ = new SimpleElmCommand(0.0, "bogey", "some bogus command",
			"OBD");
}

void SimpleElmCommandTest::tearDown() {
	delete command_for_test_;
}



void SimpleElmCommandTest::testCommandConversionToSerial() {
	uint8_t expected[] = { 98, 111, 103, 101, 121 };
	uint8_t* actual = command_for_test_->();
	CPPUNIT_ASSERT(actual != NULL);
	CPPUNIT_ASSERT_EQUAL((unsigned int) 5,
			command_for_test_->getCommandLength());

	for (int i = 0; i < 5; i++) {
		CPPUNIT_ASSERT_EQUAL(expected[i], actual[i]);
	}

	delete actual;
}
