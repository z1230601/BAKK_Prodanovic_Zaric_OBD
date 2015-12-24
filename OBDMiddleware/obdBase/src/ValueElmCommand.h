#ifndef VALUEELMCOMMAND_H_
#define VALUEELMCOMMAND_H_

#include "BaseElmCommand.h"
#include <vector>
#include <string>

#include <boost/dynamic_bitset.hpp>

using boost::dynamic_bitset;
class ValueElmCommand : public BaseElmCommand {
private:
	std::string value_;
	std::string value_format_;

	unsigned int getBitCountFromFormat(std::string valueFormat);
public:
	ValueElmCommand();
	ValueElmCommand(float minReqElmVersion, std::string command,
			std::string value, std::string description, std::string group,
			std::string valueformat);
	virtual ~ValueElmCommand();

	uint8_t* getCommandAsByteArray();

	std::string getValueAsString();
	bool valueStringCheckValid(std::string value);
	bool checkValueToFormat(std::string value);
};

#endif /* VALUEELMCOMMAND_H_ */
