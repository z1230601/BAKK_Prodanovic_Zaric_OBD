#ifndef DBEXECUTER_H_
#define DBEXECUTER_H_

#include "DBRepresenter.h"

class DBExecuter {
public:
	DBExecuter();
	DBExecuter(DBRepresenter* representer);
	DBExecuter(std::string);
	~DBExecuter();

	DBRepresenter* getDatabase();
	void setDatabase(DBRepresenter* database);
	SQLTable readData(std::string table, std::vector<std::string> columns, std::string condition);
	bool insertData(std::string to_table, std::vector<std::string> columns, SQLTable data);
	void deleteData(std::string table, std::vector<std::string> columns, std::vector<std::string> condition);
	std::string getValuesFromInput(SQLTable data);


private:
	DBRepresenter* database_;
};

#endif /* DBEXECUTER_H_ */
