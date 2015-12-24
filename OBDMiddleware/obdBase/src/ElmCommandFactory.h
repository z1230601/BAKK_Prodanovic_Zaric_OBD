#ifndef ELMCOMMANDFACTORY_H_
#define ELMCOMMANDFACTORY_H_

#include <string>
#include <vector>
#include "ElmCommand.h"

class ElmCommandFactory {
private:
	ElmCommandFactory();

public:
	virtual ~ElmCommandFactory();
	static std::vector<ElmCommand*> createElmCommands(std::string xmlpath);
};

#endif /* ELMCOMMANDFACTORY_H_ */
