#ifndef VALUEELMCOMMAND_H_
#define VALUEELMCOMMAND_H_

#include "BaseElmCommand.h"
#include <vector>
#include <string>

#include <boost/dynamic_bitset.hpp>

using boost::dynamic_bitset;
class ValueElmCommand : public BaseElmCommand {
private:
	dynamic_bitset<>* value_;

	std::string valueStringCheckAndAlter(std::string valueFormat);
	unsigned int getBitCount(std::string valueFormat);
public:
	ValueElmCommand();
	ValueElmCommand(float minReqElmVersion, std::string command,
			std::string value, std::string description, std::string group,
			std::string valueformat);
	virtual ~ValueElmCommand();

	uint8_t* getCommandAsByteArray();

	std::string getValueAsString();
};

#endif /* VALUEELMCOMMAND_H_ */
