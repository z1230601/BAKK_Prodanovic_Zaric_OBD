#include "USBEmulationSupervisor.h"
#include "USBRequestHandler.h"
#include "boost/function.hpp"

void testHandler(std::string &command){
	std::cout << "TestHandle: " << command << std::endl;
	if(command == "atz"){
		USBRequestHandler::getDevice()->addAnswerToQueue("ELM327 v1.4");
	}

	if(command == "something"){
		USBRequestHandler::getDevice()->addAnswerToQueue("ANSWER");
	}
}

int main() {
	USBEmulationSupervisor sup;
	USBRequestHandler::initCallback(&testHandler);
//	USBRequestHandler::getDevice()->setCallbackFunction(&testHandler);
	sup.run();

	return 0;
}

