#ifndef MAINCONTROLLER_H_
#define MAINCONTROLLER_H_

#include "OBDCommandController.h"
#include "DBExecuter.h"

class MainController {
public:
	virtual ~MainController();
	static MainController* getInstance();

	void initDatabase();//void initDatabase(std::string &configuration_path);

	OBDCommandController* commandController();
	void init();
private:
	static MainController* instance_;
	MainController();

	OBDCommandController* command_controller_;


	DBExecuter* db_;

};

#endif /* MAINCONTROLLER_H_ */
