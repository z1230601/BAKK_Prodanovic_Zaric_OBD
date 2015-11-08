#include "DBRepresenterTest.h"
#include "../src/DBRepresenter.h"

void DBRepresenterTest::setUp() {
	testing_ = new DBRepresenter("./testdata/configuration.xml");
}
void DBRepresenterTest::tearDown() {
	delete testing_;
}

void DBRepresenterTest::testInit() {
	CPPUNIT_ASSERT(testing_->isValid());
//	CPPUNIT_ASSERT(true);
}

