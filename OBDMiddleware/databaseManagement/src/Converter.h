#include <cppconn/resultset.h>
#include <cppconn/resultset_metadata.h>
#include <string>


#ifndef CONVERTER_HPP_
#define CONVERTER_HPP_

class Converter{
public:
	static std::string convertDBEntryToCString(unsigned int index, sql::ResultSet* result);
};


#endif /* CONVERTER_HPP_ */
