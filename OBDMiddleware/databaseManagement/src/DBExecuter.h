#ifndef DBEXECUTER_H_
#define DBEXECUTER_H_

#include "DBRepresenter.h"

class DBExecuter {
public:
	DBExecuter();
	DBExecuter(std::string);
	~DBExecuter();

	DBRepresenter* getDatabase();
	SQLTable readData(std::string table, std::vector<std::string> columns, std::string condition);

private:
	DBRepresenter* database_;
};

#endif /* DBEXECUTER_H_ */
