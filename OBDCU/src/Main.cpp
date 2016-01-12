#include "View/viewadministrator.h"

int main(int argc, char** argv){
	MainController::getInstance()->init();
	ViewAdministrator::getInstance()->startView(argc, argv);
	//start view via a singleton in a separate thread since its blocking
	//start/adjust this thread to model thread and use controller as communication and locking!!!!

	return 0;
}

