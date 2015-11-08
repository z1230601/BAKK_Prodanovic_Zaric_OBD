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

/*Database           |
+--------------------+
| information_schema |
| OBD_TroubleCodes   |
| mysql              |
| performance_schema |
| phpmyadmin         |
+--------------------+*/
void DBRepresenterTest::testExecuteSQLStatement(){
	std::string statement = "SELECT * from testdata";
	representer_under_test_->connectToDatabase();
	CPPUNIT_ASSERT(representer_under_test_->isConnected());
	std::vector< std::vector<std::string>> result = representer_under_test_->executeSQLStatement(statement);
	representer_under_test_->closeConnection();
	CPPUNIT_ASSERT(!representer_under_test_->isConnected());
	std::vector<std::vector<std::string>> expected;
	expected.push_back(std::vector<std::string>{"ID","Name"});
	expected.push_back(std::vector<std::string>{"1","Adolf"});
	expected.push_back(std::vector<std::string>{"2","Borat"});
	expected.push_back(std::vector<std::string>{"3","Caesar"});

	CPPUNIT_ASSERT(result.size() == expected.size());
	for(unsigned int i=0; i < expected.size(); i++){
		CPPUNIT_ASSERT(expected.at(i).size() == result.at(i).size());
		for(unsigned int j=0; j < expected.at(i).size();j++){
			CPPUNIT_ASSERT_EQUAL(expected.at(i).at(j), result.at(i).at(j));
		}
	}
}
