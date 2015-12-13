/*
 * maincontroller.h
 *
 *  Created on: Dec 12, 2015
 *      Author: zlatan
 */

#ifndef MAINCONTROLLER_H_
#define MAINCONTROLLER_H_

class DBExecuter;

class MainController {
public:
	virtual ~MainController();
	static MainController* getInstance();

	void initDatabase();//void initDatabase(std::string &configuration_path);

private:
	static MainController* instance_;
	MainController();

	DBExecuter* db_;

};

#endif /* MAINCONTROLLER_H_ */
