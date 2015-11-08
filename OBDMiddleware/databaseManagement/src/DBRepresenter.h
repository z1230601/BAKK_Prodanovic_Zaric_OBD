#ifndef DBREPRESENTER_H_
#define DBREPRESENTER_H_

#include <string>
#include <vector>
#include <libxml++/libxml++.h>

#include "mysql_connection.h"
#include "mysql_driver.h"


#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

#define ADDRESS_TAG "address"
#define USER_TAG "user"
#define PASSWORD_TAG "password"
#define DBNAME_TAG "dbname"

class DBRepresenter {
public:
	DBRepresenter();
	DBRepresenter(std::string);
	~DBRepresenter();

	bool isValid();
	bool isConnected();


	void connectToDatabase();
	void closeConnection();

	std::vector<std::vector<std::string>> executeSQLStatement(std::string statement);

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
