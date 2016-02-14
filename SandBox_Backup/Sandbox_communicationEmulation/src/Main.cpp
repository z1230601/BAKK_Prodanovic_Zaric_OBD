#include "USBEmulationSupervisor.h"
#include "USBRequestHandler.h"
#include "boost/function.hpp"

USBEmulationSupervisor* sup;

void testHandler(std::string &command){
	std::cout << "TestHandle: " << command << std::endl;
	if(command == "atz"){
		sup->getRequestHandler()->getDevice()->addAnswerToQueue("ELM327 v1.4");
	}

	if(command == "something"){
		sup->getRequestHandler()->getDevice()->addAnswerToQueue("ANSWER");
	}
}

int main() {
	sup = new USBEmulationSupervisor();
	sup->getRequestHandler()->initCallback(&testHandler);
	sup->run();

	return 0;
}

