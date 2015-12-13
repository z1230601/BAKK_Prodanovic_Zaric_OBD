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
	std::string expectedShortDescription = "sh. des.";
	unsigned int expectedCodeClassID = 0;
	unsigned int expectedSourceClassID = 1;

	dtc_under_test_ = new DiagnosticTroubleCode(expectedCodeClassID,
			expectedSourceClassID, expectedShortDescription,
			expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClassID,
			dtc_under_test_->getCodeClassID());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClassID,
			dtc_under_test_->getSourceClassID());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedShortDescription,
			dtc_under_test_->getShortDescription());

	dtc_under_test_ = new DiagnosticTroubleCode(expectedCodeClass,
			expectedSourceClass, expectedShortDescription, expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClass, dtc_under_test_->getCodeClass());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClass,
			dtc_under_test_->getSourceClass());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedShortDescription,
			dtc_under_test_->getShortDescription());
}

void DiagnosticTroubleCodeTest::testConversion() {
	std::string expectedCodeClass = "Generic";
	std::string expectedSourceClass = "Fuel & Air Metering";
	std::string expectedDescription = "some long long description";
	std::string expectedShortDescription = "sh. des.";
	unsigned int expectedCodeClassID = 0;
	unsigned int expectedSourceClassID = 1;

	dtc_under_test_ = new DiagnosticTroubleCode(expectedCodeClassID,
			expectedSourceClassID, expectedShortDescription,
			expectedDescription);

	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClass,
			dtc_under_test_->getCodeClass());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClass,
			dtc_under_test_->getSourceClass());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedShortDescription,
			dtc_under_test_->getShortDescription());

	dtc_under_test_ = new DiagnosticTroubleCode(expectedCodeClass,
			expectedSourceClass, expectedShortDescription, expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClassID, dtc_under_test_->getCodeClassID());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClassID,
			dtc_under_test_->getSourceClassID());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());
	CPPUNIT_ASSERT_EQUAL(expectedShortDescription,
			dtc_under_test_->getShortDescription());
}

