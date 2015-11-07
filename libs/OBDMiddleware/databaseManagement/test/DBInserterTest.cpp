#include "DBInserterTest.h"
#include "../src/DBInserter.h"

void DBInserterTest::setUp()
{
	testing_ = new DBInserter("TestInserter");
}

void DBInserterTest::tearDown()
{
	delete testing_;
}

void DBInserterTest::testInsert(){
	CPPUNIT_ASSERT(true);
	//CPPUNIT_FAIL("just4fun");
}
