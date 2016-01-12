#ifndef OBDCOMMANDCONTROLLER_H_
#define OBDCOMMANDCONTROLLER_H_

#include <vector>
#include "ObdCommand.h"

class OBDCommandController {
public:
	OBDCommandController();
	virtual ~OBDCommandController();

private:
	std::vector<ObdCommand*> commands_;
};

#endif /* OBDCOMMANDCONTROLLER_H_ */
