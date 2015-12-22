#ifndef VALUEELMCOMMAND_H_
#define VALUEELMCOMMAND_H_

#include "BaseElmCommand.h"
#include <vector>
#include <string>

class ValueElmCommand : public BaseElmCommand {
private:
	std::vector<unsigned int> values_;

public:
	ValueElmCommand();
	ValueElmCommand(float minReqElmVersion, std::string command,
			unsigned int value, std::string description, std::string group);
	ValueElmCommand(float minReqElmVersion, std::string command,
			std::vector<unsigned int> values, std::string description,
			std::string group);
	virtual ~ValueElmCommand();

	uint8_t* getCommandAsByteArray();

	unsigned int getSingleValue();
};

#endif /* VALUEELMCOMMAND_H_ */
