#ifndef MAINCONTROLLER_H_
#define MAINCONTROLLER_H_

#include <string>
#include "OBDController.h"
#include "CommunicationController.h"
#include "DBExecuter.h"

class MainController {
public:
	virtual ~MainController();
	static MainController* getInstance();

	void initDatabase();

	OBDController* getOBDController();
	CommunicationController* getCommunicationController();
	bool init(std::string configuration_file);

	DBExecuter* getDb();
	void setDb(DBExecuter* db);

private:
	static MainController* instance_;
	MainController();
	OBDController* command_controller_;
	CommunicationController* communication_controller_;
	DBExecuter* db_;
};

#endif /* MAINCONTROLLER_H_ */
