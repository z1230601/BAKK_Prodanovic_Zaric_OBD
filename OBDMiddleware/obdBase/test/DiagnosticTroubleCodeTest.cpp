#include "DiagnosticTroubleCodeTest.h"
#include "../src/DiagnosticTroubleCode.h"

#include <string>
#include "../src/Configuration.h"

void DiagnosticTroubleCodeTest::setUp() {
	dtc_under_test_ = new DiagnosticTroubleCode();
	std::string configpath = "../../obdBase/test/testdata/dbconfiguration.xml";
	Configuration::getInstance()->setDatabaseConfigFilePath(configpath);
}

void DiagnosticTroubleCodeTest::tearDown() {
	delete dtc_under_test_;
}

void DiagnosticTroubleCodeTest::testConstruction() {
	CPPUNIT_ASSERT(!dtc_under_test_->isValidlyConstructed());

	std::string expectedCodeClass = "Generic";
	std::string expectedSourceClass = "Fuel & Air Metering";
	std::string expectedDescription = "some long long description";
	unsigned int expectedCodeClassID = 0;
	unsigned int expectedSourceClassID = 1;

	dtc_under_test_ = new DiagnosticTroubleCode(expectedCodeClassID,
			expectedSourceClassID, expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClassID,
			dtc_under_test_->getCodeClassID());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClassID,
			dtc_under_test_->getSourceClassID());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());

	dtc_under_test_ = new DiagnosticTroubleCode(expectedCodeClass,
			expectedSourceClass, expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClass, dtc_under_test_->getCodeClass());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClass,
			dtc_under_test_->getSourceClass());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());
}

void DiagnosticTroubleCodeTest::testConversion() {
	std::string expectedCodeClass = "Generic";
	std::string expectedSourceClass = "Fuel & Air Metering";
	std::string expectedDescription = "some long long description";
	unsigned int expectedCodeClassID = 0;
	unsigned int expectedSourceClassID = 1;

	dtc_under_test_ = new DiagnosticTroubleCode(expectedCodeClassID,
			expectedSourceClassID, expectedDescription);

	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClass, dtc_under_test_->getCodeClass());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClass,
			dtc_under_test_->getSourceClass());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());

	dtc_under_test_ = new DiagnosticTroubleCode(expectedCodeClass,
			expectedSourceClass, expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClassID,
			dtc_under_test_->getCodeClassID());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClassID,
			dtc_under_test_->getSourceClassID());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());
}

void DiagnosticTroubleCodeTest::testHexConversion(){
	unsigned int hexvalue = 0x143A; // = P143A
	unsigned int expectedCodeClassId = 1;
	unsigned int expectedSourceClassId = 4;
	unsigned int expectedFaultId = 0x3A;

	dtc_under_test_->fromElmHexValue(hexvalue);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClassId,
			dtc_under_test_->getCodeClassID());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClassId,
			dtc_under_test_->getSourceClassID());
	CPPUNIT_ASSERT_EQUAL(expectedFaultId, dtc_under_test_->getFaultID());

	unsigned int actualHex = dtc_under_test_->toElmHexValue();
	CPPUNIT_ASSERT_EQUAL(hexvalue, actualHex);
}
