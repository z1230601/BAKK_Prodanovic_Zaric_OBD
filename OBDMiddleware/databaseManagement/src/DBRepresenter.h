#ifndef DBREPRESENTER_H_
#define DBREPRESENTER_H_

#include <string>
#include <vector>

#include "mysql_connection.h"
#include "mysql_driver.h"


#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

typedef std::vector<std::vector<std::string> > SQLTable;

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
	static SQLTable convertToReadableFormat(sql::ResultSet* result);

	std::string getHostAddress() const;
	std::string getPassword() const;
	std::string getUsername() const;
	std::string getDatabaseName() const;


private:
	bool valid_construction_ = false;

	void checkIfValid();
	static std::vector<std::string> getResultRowAsVector(sql::ResultSet* row, bool header = false);

	std::string host_address_;
	std::string username_;
	std::string password_;
	std::string dbname_;

	sql::mysql::MySQL_Driver* driver_;
	sql::Connection* connection_;

	bool parseConfigurationFile(std::string configurationFile);
};

#endif /* DBREPRESENTER_H_ */
