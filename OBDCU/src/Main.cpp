#include "View/viewadministrator.h"
#include "Controller/maincontroller.h"

int main(int argc, char** argv){
    Q_INIT_RESOURCE(resources);
	MainController::getInstance()->init();
	ViewAdministrator::getInstance()->startView(argc, argv);
	//start view via a singleton in a separate thread since its blocking
	//start/adjust this thread to model thread and use controller as communication and locking!!!!

	return 0;
}

