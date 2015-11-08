#ifndef DBREPRESENTERTEST_H_
#define DBREPRESENTERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class DBRepresenter;

class DBRepresenterTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE (DBRepresenterTest);
	CPPUNIT_TEST (testInit);
	CPPUNIT_TEST_SUITE_END();

	//	static CppUnit::TestSuite *suite();
private:
	DBRepresenter* testing_;
public:
	void setUp();
	void tearDown();
	void testInit();
};
CPPUNIT_TEST_SUITE_REGISTRATION (DBRepresenterTest);
#endif /* DBREPRESENTERTEST_H_ */
