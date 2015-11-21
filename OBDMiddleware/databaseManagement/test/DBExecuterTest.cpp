#include "DBExecuterTest.h"
#include "../src/DBExecuter.h"
#include "MockDBRepresenter.h"

using std::string;
using std::vector;

void DBExecuterTest::setUp() {
//	executer_under_test_ = new DBExecuter("../test/testdata/configuration.xml");
	executer_under_test_ = new DBExecuter(new MockDBRepresenter());
}

void DBExecuterTest::tearDown() {
	delete executer_under_test_;
}

void DBExecuterTest::testInit() {
	CPPUNIT_ASSERT(executer_under_test_->getDatabase() != NULL);
}

void DBExecuterTest::testReadData(){
	std::string fromTable = "testdata";
	std::vector<std::string> columns{"ID", "Name"};
	std::string condition = "ID IS NOT NULL";

	SQLTable result = executer_under_test_->readData(fromTable, columns, condition);
	CPPUNIT_ASSERT_EQUAL((size_t) 4, result.size());
	CPPUNIT_ASSERT_EQUAL(columns.size(), result.at(0).size());
	std::vector<std::vector<std::string>> expected;
	expected.push_back(std::vector<std::string>{"ID","Name"});
	expected.push_back(std::vector<std::string> { "1", "Adolf" });
	expected.push_back(std::vector<std::string> { "2", "Borat" });
	expected.push_back(std::vector<std::string> { "3", "Caesar" });

	CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
	for (unsigned int i = 0; i < expected.size(); i++) {
		CPPUNIT_ASSERT_EQUAL(expected.at(i).size(), result.at(i).size());
		for (unsigned int j = 0; j < expected.at(i).size(); j++) {
			CPPUNIT_ASSERT_EQUAL(expected.at(i).at(j), result.at(i).at(j));
		}
	}
}

void DBExecuterTest::testReadDataSelectOnlyID(){
	std::string fromTable = "testdata";
	std::vector<std::string> columns{"ID"};
	std::string condition = "ID IS NOT NULL";

	SQLTable result = executer_under_test_->readData(fromTable, columns, condition);
	CPPUNIT_ASSERT_EQUAL((size_t) 4, result.size());
	CPPUNIT_ASSERT_EQUAL(columns.size(), result.at(0).size());
	std::vector<std::vector<std::string>> expected;
	expected.push_back(std::vector<std::string>{"ID"});
	expected.push_back(std::vector<std::string> { "1" });
	expected.push_back(std::vector<std::string> { "2" });
	expected.push_back(std::vector<std::string> { "3" });

	CPPUNIT_ASSERT_EQUAL(expected.size(), result.size());
	for (unsigned int i = 0; i < expected.size(); i++) {
		CPPUNIT_ASSERT_EQUAL(expected.at(i).size(), result.at(i).size());
		for (unsigned int j = 0; j < expected.at(i).size(); j++) {
			CPPUNIT_ASSERT_EQUAL(expected.at(i).at(j), result.at(i).at(j));
		}
	}
}

void DBExecuterTest::testSimpleInsert(){
	std::string to_table = "testdata";
	vector<string> columns{"ID", "Name"};
	SQLTable data{{"3", "Hänsel"},{"4", "Gretl"}};

	CPPUNIT_ASSERT(executer_under_test_->insertData(to_table, columns, data));
}
