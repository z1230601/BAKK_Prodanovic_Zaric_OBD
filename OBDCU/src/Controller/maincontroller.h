#ifndef MAINCONTROLLER_H_
#define MAINCONTROLLER_H_

#include <string>
#include "OBDController.h"
#include "DBExecuter.h"

class MainController {
public:
	virtual ~MainController();
	static MainController* getInstance();

	void initDatabase();

	OBDController* getOBDController();
	void init();

	DBExecuter* getDb();
	void setDb(DBExecuter* db);

private:
	static MainController* instance_;
	MainController();
	OBDController* command_controller_;
	DBExecuter* db_;
};

#endif /* MAINCONTROLLER_H_ */
