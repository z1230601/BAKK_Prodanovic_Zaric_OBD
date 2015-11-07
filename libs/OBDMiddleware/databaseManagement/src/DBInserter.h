#ifndef DBINSERTER_H_
#define DBINSERTER_H_

#include <string.h>

class DBInserter {
private:
	std::string database_name_;
	std::string host_ = "127.0.1.1";
public:
	DBInserter(std::string db_name_);
	~DBInserter();
};


#endif /* DBINSERTER_H_ */
