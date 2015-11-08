#ifndef DBINSERTERTEST_H_
#define DBINSERTERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class DBInserter;

class DBInserterTest: public CppUnit::TestCase{
	CPPUNIT_TEST_SUITE( DBInserterTest );
	CPPUNIT_TEST( testInsert );
	CPPUNIT_TEST_SUITE_END();

//	static CppUnit::TestSuite *suite();
private:
	DBInserter* testing_;
public:
	  void setUp();
	  void tearDown();
	  void testInsert();
};
CPPUNIT_TEST_SUITE_REGISTRATION(DBInserterTest);
#endif /* UARTDEVICETEST_H_ */
