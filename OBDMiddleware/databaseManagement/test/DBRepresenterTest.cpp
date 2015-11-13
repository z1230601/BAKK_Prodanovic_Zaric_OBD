#include "DBRepresenterTest.h"
#include "../src/DBRepresenter.h"

#include <vector>

void DBRepresenterTest::setUp() {
	representer_under_test_ = new DBRepresenter("../test/testdata/configuration.xml");
}
void DBRepresenterTest::tearDown() {
	delete representer_under_test_;
}

void DBRepresenterTest::testInit() {
	std::string expected_host_address = "tcp://127.0.0.1:3306";
	std::string expected_username = "obd";
	std::string expected_password = "";

	CPPUNIT_ASSERT(representer_under_test_->isValid());
	CPPUNIT_ASSERT_EQUAL(expected_host_address, representer_under_test_->getHostAddress());
	CPPUNIT_ASSERT_EQUAL(expected_username, representer_under_test_->getUsername());
	CPPUNIT_ASSERT_EQUAL(expected_password, representer_under_test_->getPassword());
}

void DBRepresenterTest::testConnect() {
	representer_under_test_->connectToDatabase();
	CPPUNIT_ASSERT(representer_under_test_->isConnected());
}

void DBRepresenterTest::testConnectMultipleTimes() {
	representer_under_test_->connectToDatabase();
	CPPUNIT_ASSERT(representer_under_test_->isConnected());
	representer_under_test_->closeConnection();
	CPPUNIT_ASSERT(!representer_under_test_->isConnected());
	CPPUNIT_ASSERT_NO_THROW(representer_under_test_->connectToDatabase());
	CPPUNIT_ASSERT(representer_under_test_->isConnected());
}

void DBRepresenterTest::testDoubleConnect() {
	representer_under_test_->connectToDatabase();
	CPPUNIT_ASSERT(representer_under_test_->isConnected());
	CPPUNIT_ASSERT_NO_THROW(representer_under_test_->connectToDatabase());
}

void DBRepresenterTest::testExecuteSQLStatement() {
	std::string statement = "SELECT * from testdata";
	representer_under_test_->connectToDatabase();
	CPPUNIT_ASSERT(representer_under_test_->isConnected());
	SQLTable result = representer_under_test_->executeSQLStatement(statement);
	representer_under_test_->closeConnection();
	CPPUNIT_ASSERT(!representer_under_test_->isConnected());
	std::vector<std::vector<std::string>> expected;
	expected.push_back(std::vector<std::string>{"ID","Name"});
	expected.push_back(std::vector<std::string>{"1","Adolf"});
	expected.push_back(std::vector<std::string>{"2","Borat"});
	expected.push_back(std::vector<std::string>{"3","Caesar"});

	CPPUNIT_ASSERT_EQUAL(result.size(), expected.size());
	for(unsigned int i=0; i < expected.size(); i++){
		CPPUNIT_ASSERT_EQUAL(expected.at(i).size(), result.at(i).size());
		for(unsigned int j=0; j < expected.at(i).size();j++){
			CPPUNIT_ASSERT_EQUAL(expected.at(i).at(j), result.at(i).at(j));
		}
	}
}

namespace {
  bool searchForStringInResult(std::vector<std::vector<std::string>> results, std::string search_string) {
	for (unsigned int i = 0; i < results.size(); i++) {
		for (unsigned int j = 0; j < results.at(i).size(); j++) {
			if (results.at(i).at(j) == search_string) {
				return true;
			}
		}
	}
	return false;
  }
}

void DBRepresenterTest::testCreateTableForExecuteSQLStatement() {
	std::string create_statement = "create table if not exists `newtable` (`ID` int(10) unsigned NOT NULL)";
	representer_under_test_->connectToDatabase();
	CPPUNIT_ASSERT(representer_under_test_->isConnected());
	SQLTable result = representer_under_test_->executeSQLStatement(create_statement);
	std::string expected = "newtable";
	CPPUNIT_ASSERT(::searchForStringInResult(result, expected));

	std::string drop_statement = "drop table if exists newtable";
	CPPUNIT_ASSERT(representer_under_test_->isConnected());
	representer_under_test_->executeSQLStatement(drop_statement);
	representer_under_test_->closeConnection();
	CPPUNIT_ASSERT(!representer_under_test_->isConnected());
	CPPUNIT_ASSERT(! ::searchForStringInResult(result, expected));
}


void DBRepresenterTest::testReadData(){
	representer_under_test_->connectToDatabase();
	CPPUNIT_ASSERT(representer_under_test_->isConnected());

	std::string fromTable = "testdata";
	std::vector<std::string> columns{"ID","Name"};
	std::string condition = "ID IS NOT NULL";

	SQLTable result = representer_under_test_->readData(fromTable, columns, condition);
//	CPPUNIT_ASSERT_EQUAL((size_t) 4, result.size());
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
