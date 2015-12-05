#include "DBExecuterTest.h"
#include "../src/DBExecuter.h"

void DBExecuterTest::setUp() {
	executer_under_test_ = new DBExecuter("../test/testdata/configuration.xml");
	setUpDatabase();
}

void DBExecuterTest::tearDown() {
	setUpDatabase();
	delete executer_under_test_;
}

void DBExecuterTest::setUpDatabase() {
	system("../test/testdata/setupDatabases.sh ../test/testdata/testdb.sql");
}

void DBExecuterTest::testInit() {
	CPPUNIT_ASSERT(executer_under_test_->getDatabase() != NULL);
}


void DBExecuterTest::assertSQLTable(SQLTable expected, SQLTable actual) {
	CPPUNIT_ASSERT_EQUAL(expected.size(), actual.size());

	for (unsigned int i = 0; i < expected.size(); i++) {
		CPPUNIT_ASSERT_EQUAL(expected.at(i).size(), actual.at(i).size());
		for (unsigned int j = 0; j < expected.at(i).size(); j++) {
			CPPUNIT_ASSERT_EQUAL(expected.at(i).at(j), actual.at(i).at(j));
		}
	}
}


void DBExecuterTest::testReadData() {
	std::string fromTable = "testdata";
	std::vector<std::string> columns { "ID", "Name" };
	std::string condition = "ID IS NOT NULL";

	SQLTable result = executer_under_test_->readData(fromTable, columns,
			condition);
	CPPUNIT_ASSERT_EQUAL((size_t) 4, result.size());
	CPPUNIT_ASSERT_EQUAL(columns.size(), result.at(0).size());
	std::vector<std::vector<std::string>> expected;
	expected.push_back(std::vector<std::string> { "ID", "Name" });
	expected.push_back(std::vector<std::string> { "1", "Adolf" });
	expected.push_back(std::vector<std::string> { "2", "Borat" });
	expected.push_back(std::vector<std::string> { "3", "Caesar" });

	assertSQLTable(expected, result);

}

void DBExecuterTest::testReadDataSelectOnlyID() {
	std::string fromTable = "testdata";
	std::vector<std::string> columns { "ID" };
	std::string condition = "ID IS NOT NULL";

	SQLTable result = executer_under_test_->readData(fromTable, columns,
			condition);
	CPPUNIT_ASSERT_EQUAL((size_t) 4, result.size());
	CPPUNIT_ASSERT_EQUAL(columns.size(), result.at(0).size());
	SQLTable expected;
	expected.push_back(std::vector<std::string> { "ID" });
	expected.push_back(std::vector<std::string> { "1" });
	expected.push_back(std::vector<std::string> { "2" });
	expected.push_back(std::vector<std::string> { "3" });

	assertSQLTable(expected, result);
}

void DBExecuterTest::testSimpleInsert() {
	std::string to_table = "testdata";
	std::vector<std::string> columns { "ID", "Name" };
	SQLTable data { { "4", "Hänsel" }, { "5", "Gretl" } };

	CPPUNIT_ASSERT(executer_under_test_->insertData(to_table, columns, data));
}

void DBExecuterTest::testInsertExistingID() {
	std::string to_table = "testdata";
	std::vector<std::string> columns { "ID", "Name" };
	SQLTable data { { "3", "ShouldFail" } };

	CPPUNIT_ASSERT(!executer_under_test_->insertData(to_table, columns, data));
}

void DBExecuterTest::testDeleteEntry() {
	std::string table = "testdata";
	std::vector<std::string> columns = { "ID" };
	std::vector<std::string> conditions = { "1" };

	executer_under_test_->deleteData(table, columns, conditions);

	sql::mysql::MySQL_Driver* driver_ = new sql::mysql::MySQL_Driver();

	sql::Connection* connection = driver_->connect(
			executer_under_test_->getDatabase()->getHostAddress(),
			executer_under_test_->getDatabase()->getUsername(),
			executer_under_test_->getDatabase()->getPassword());
	connection->setSchema(executer_under_test_->getDatabase()->getDatabaseName());

	sql::Statement* statement;
	sql::ResultSet* result;
	CPPUNIT_ASSERT(!connection->isClosed());

	statement = connection->createStatement();
	CPPUNIT_ASSERT(statement != NULL);
	result = statement->executeQuery("SELECT ID FROM " + table);

	SQLTable actual = DBRepresenter::convertToReadableFormat(result);

	SQLTable expected;
	expected.push_back(std::vector<std::string> { "ID" });
	expected.push_back(std::vector<std::string> { "2" });
	expected.push_back(std::vector<std::string> { "3" });

	assertSQLTable(expected, actual);
}
