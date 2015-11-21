#ifndef DBEXECUTER_H_
#define DBEXECUTER_H_

#include "DBRepresenter.h"
using std::string;
using std::vector;

class DBExecuter {
public:
	DBExecuter();
	DBExecuter(DBRepresenter* representer);
	DBExecuter(std::string);
	~DBExecuter();

	DBRepresenter* getDatabase();
	void setDatabase(DBRepresenter* database);
	SQLTable readData(std::string table, std::vector<std::string> columns, std::string condition);
	bool insertData(string to_table, vector<string> columns, SQLTable data);
	std::string getValuesFromInput(SQLTable data);


private:
	DBRepresenter* database_;
};

#endif /* DBEXECUTER_H_ */
