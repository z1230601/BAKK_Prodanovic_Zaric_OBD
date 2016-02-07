#include "View/viewadministrator.h"
#include "Controller/maincontroller.h"
#include <iostream>

int main(int argc, char** argv){
    Q_INIT_RESOURCE(resources);

    if(argc != 2){
    	std::cout << "usage ./OBDCU <path to obdcuconfig>\n";
    	return -1;
    }
    std::cout << "Using OBDCU config: " << argv[1] << std::endl;
	if(!MainController::getInstance()->init(argv[1])){
		std::cout << "Error parsing config file!" << std::endl;
	}
	std::cout << "Starting view \n";
	ViewAdministrator::getInstance()->startView(argc, argv);
	//start view via a singleton in a separate thread since its blocking
	//start/adjust this thread to model thread and use controller as communication and locking!!!!

	return 0;
}

