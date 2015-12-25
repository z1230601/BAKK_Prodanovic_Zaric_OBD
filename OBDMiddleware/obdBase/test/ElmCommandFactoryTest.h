#ifndef ELMCOMMANDFACTORYTEST_H_
#define ELMCOMMANDFACTORYTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class ElmCommandFactory;

class ElmCommandFactoryTest : public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE (ElmCommandFactoryTest);
	CPPUNIT_TEST(testFactory);
	CPPUNIT_TEST_SUITE_END();

private:
	ElmCommandFactory* ecf_for_test_;

public:
	void setUp();
	void tearDown();
	void testFactory();
};

CPPUNIT_TEST_SUITE_REGISTRATION (ElmCommandFactoryTest);

#endif /* ELMCOMMANDFACTORYTEST_H_ */
