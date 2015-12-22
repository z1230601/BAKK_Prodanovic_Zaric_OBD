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

	unsigned int expectedAssemblyId = 0;
	std::string expectedAssembly = "Powertrain";
	std::string expectedCodeClass = "Generic";
	std::string expectedSourceClass = "Fuel & Air Metering";
	std::string expectedDescription = "some long long description";
	unsigned int expectedCodeClassID = 0;
	unsigned int expectedSourceClassID = 1;
	unsigned int expectedFaultID = 0x00;

	dtc_under_test_ = new DiagnosticTroubleCode(expectedAssemblyId,
			expectedCodeClassID, expectedSourceClassID, expectedFaultID,
			expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClassID,
			dtc_under_test_->getCodeClassID());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClassID,
			dtc_under_test_->getSourceClassID());
	CPPUNIT_ASSERT_EQUAL(expectedFaultID, dtc_under_test_->getFaultID());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());

	dtc_under_test_ = new DiagnosticTroubleCode(expectedAssemblyId,
			expectedCodeClass, expectedSourceClass, expectedFaultID,
			expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClass, dtc_under_test_->getCodeClass());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClass,
			dtc_under_test_->getSourceClass());
	CPPUNIT_ASSERT_EQUAL(expectedFaultID, dtc_under_test_->getFaultID());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());

	CPPUNIT_ASSERT_EQUAL(expectedAssembly, dtc_under_test_->getAssemblyName());
}

void DiagnosticTroubleCodeTest::testConversion() {
	unsigned int expectedAssemblyId = 1;
	std::string expectedAssembly = "Chassis";
	std::string expectedCodeClass = "Generic";
	std::string expectedSourceClass = "Fuel & Air Metering";
	std::string expectedDescription = "some long long description";
	unsigned int expectedCodeClassID = 0;
	unsigned int expectedSourceClassID = 1;
	unsigned int expectedFaultID = 0x01;

	dtc_under_test_ = new DiagnosticTroubleCode(expectedAssemblyId,
			expectedCodeClassID, expectedSourceClassID, expectedFaultID,
			expectedDescription);

	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClass, dtc_under_test_->getCodeClass());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClass,
			dtc_under_test_->getSourceClass());
	CPPUNIT_ASSERT_EQUAL(expectedFaultID, dtc_under_test_->getFaultID());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());

	CPPUNIT_ASSERT_EQUAL(expectedAssembly, dtc_under_test_->getAssemblyName());

	dtc_under_test_ = new DiagnosticTroubleCode(expectedAssemblyId,
			expectedCodeClass, expectedSourceClass, expectedFaultID,
			expectedDescription);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	CPPUNIT_ASSERT_EQUAL(expectedCodeClassID,
			dtc_under_test_->getCodeClassID());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClassID,
			dtc_under_test_->getSourceClassID());
	CPPUNIT_ASSERT_EQUAL(expectedFaultID, dtc_under_test_->getFaultID());
	CPPUNIT_ASSERT_EQUAL(expectedDescription,
			dtc_under_test_->getDescription());

	CPPUNIT_ASSERT_EQUAL(expectedAssembly, dtc_under_test_->getAssemblyName());
}

void DiagnosticTroubleCodeTest::testHexConversionSimple() {
	unsigned int hexvalue = 0x143A; // = P143A
	unsigned int expectedAssembly = 0;
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
	CPPUNIT_ASSERT_EQUAL(expectedAssembly,
			dtc_under_test_->getAssemblyAreaID());

	unsigned int actualHex = dtc_under_test_->toElmHexValue();
	CPPUNIT_ASSERT_EQUAL(hexvalue, actualHex);
}

void DiagnosticTroubleCodeTest::testHexConversionDifferentCodes() {
	unsigned int hexvalue = 0x57C4; // = C17C4
	unsigned int expectedAssembly = 1;
	unsigned int expectedCodeClassId = 1;
	unsigned int expectedSourceClassId = 7;
	unsigned int expectedFaultId = 0xC4;

	dtc_under_test_->fromElmHexValue(hexvalue);
	CPPUNIT_ASSERT(dtc_under_test_->isValidlyConstructed());
	unsigned int actualHex = dtc_under_test_->toElmHexValue();
	CPPUNIT_ASSERT_EQUAL(expectedCodeClassId,
			dtc_under_test_->getCodeClassID());
	CPPUNIT_ASSERT_EQUAL(expectedSourceClassId,
			dtc_under_test_->getSourceClassID());
	CPPUNIT_ASSERT_EQUAL(expectedFaultId, dtc_under_test_->getFaultID());

	CPPUNIT_ASSERT_EQUAL(expectedAssembly,
			dtc_under_test_->getAssemblyAreaID());

	CPPUNIT_ASSERT_EQUAL(hexvalue, actualHex);

}
