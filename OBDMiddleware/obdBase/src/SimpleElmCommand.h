#ifndef SIMPLEELMCOMMAND_H_
#define SIMPLEELMCOMMAND_H_

#include "BaseElmCommand.h"

class SimpleElmCommand : public BaseElmCommand {
public:
	SimpleElmCommand();
	SimpleElmCommand(float minReqElmVersion, std::string command, std::string description, std::string group);
	virtual ~SimpleElmCommand();

	uint8_t* getCommandAsByteArray();
};

#endif /* SIMPLEELMCOMMAND_H_ */
