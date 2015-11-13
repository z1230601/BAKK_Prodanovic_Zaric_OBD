#ifndef DBREPRESENTER_H_
#define DBREPRESENTER_H_

#include <string>
#include <vector>
#include <libxml++/libxml++.h>

#include "mysql_connection.h"
#include "mysql_driver.h"


#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#define ADDRESS_TAG "address"
#define USER_TAG "user"
#define PASSWORD_TAG "password"
#define DBNAME_TAG "dbname"

typedef std::vector<std::vector<std::string>> SQLTable;

class DBRepresenter {
public:
	DBRepresenter();
	DBRepresenter(std::string);
	~DBRepresenter();

	bool isValid();
	bool isConnected();


	void connectToDatabase();
	void closeConnection();

	SQLTable executeSQLStatement(std::string statement);
	SQLTable readData(std::string table, std::vector<std::string> columns, std::string condition);

	std::string getHostAddress() const;
	std::string getPassword() const;
	std::string getUsername() const;

private:
	bool valid_construction_ = false;

	bool parseConfigurationFile(std::string);
	std::string getTextFromNode(xmlpp::Node*);
	void parseNode(xmlpp::Node*);
	void checkIfValid();
	std::vector<std::string> getResultRowAsVector(sql::ResultSet* row, bool header = false);

	std::string host_address_;
	std::string username_;
	std::string password_;
	std::string dbname_;

	sql::mysql::MySQL_Driver* driver_;
	sql::Connection* connection_;
};

#endif /* DBREPRESENTER_H_ */
