/*
 * SQLStatementFactory.h
 *
 *  Created on: 14.11.2015
 *      Author: zoran
 */

#ifndef SQLSTATEMENTFACTORY_H_
#define SQLSTATEMENTFACTORY_H_

#include <string>
#include <map>

class SQLStatementFactory {
private:
	SQLStatementFactory();
	SQLStatementFactory(SQLStatementFactory &);

	static SQLStatementFactory* instance_;

	std::map<std::string, std::string> commandMap_ { { "read", "SELECT" },
		{ "insert", "INSERT INTO" }, { "delete", "DROP" } };

public:
	static SQLStatementFactory* getInstance();

	std::string getStatement(std::string key, std::string table,
			std::string columns, std::string condition);
};

#endif /* SQLSTATEMENTFACTORY_H_ */
