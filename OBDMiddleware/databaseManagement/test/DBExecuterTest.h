#ifndef DBEXECUTERTEST_H_
#define DBEXECUTERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "../src/DBRepresenter.h"

class DBExecuter;

class DBExecuterTest : public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE(DBExecuterTest);
	CPPUNIT_TEST(testInit);
	CPPUNIT_TEST(testReadData);
	CPPUNIT_TEST(testReadDataSelectOnlyID);
	CPPUNIT_TEST(testSimpleInsert);
	CPPUNIT_TEST(testInsertExistingID);
	CPPUNIT_TEST(testDeleteEntry);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	void setUpDatabase();
	void testInit();
	void assertSQLTable(SQLTable expected, SQLTable actual);

	void testReadData();
	void testReadDataSelectOnlyID();
	void testSimpleInsert();
	void testInsertExistingID();
	void testDeleteEntry();

private:
	DBExecuter* executer_under_test_;
};

CPPUNIT_TEST_SUITE_REGISTRATION(DBExecuterTest);

#endif /* DBEXECUTERTEST_H_ */
