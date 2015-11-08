#ifndef DBREPRESENTERTEST_H_
#define DBREPRESENTERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class DBRepresenter;

class DBRepresenterTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE (DBRepresenterTest);
	CPPUNIT_TEST (testInit);
	CPPUNIT_TEST (testConnect);
	CPPUNIT_TEST (testConnectMultipleTimes);
	CPPUNIT_TEST(testDoubleConnect);
	CPPUNIT_TEST(testExecuteSQLStatement);
	CPPUNIT_TEST_SUITE_END();

	//	static CppUnit::TestSuite *suite();
private:
	DBRepresenter* representer_under_test_;
public:
	void setUp();
	void tearDown();
	void testInit();
	void testConnect();
	void testConnectMultipleTimes();
	void testDoubleConnect();
	void testExecuteSQLStatement();
};
CPPUNIT_TEST_SUITE_REGISTRATION (DBRepresenterTest);
#endif /* DBREPRESENTERTEST_H_ */
