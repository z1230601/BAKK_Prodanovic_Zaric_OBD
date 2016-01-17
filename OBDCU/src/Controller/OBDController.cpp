#include "OBDController.h"
#include "XMLReader.h"
#include "OBDCommandXMLHandler.h"
#include "Configuration.h"
#include "OBDCommandInputDefinitions.h"
#include <iostream>
#include "QtCore/qstring.h"
#include "QtCore/qstringlist.h"
//#include "qt5/QtCore/qstring.h"
//#include "qt5/QtCore/qstringlist.h"

OBDController::OBDController() {
}

OBDController::~OBDController() {
}

void OBDController::init() {
	initCommands();
}

QStringList OBDController::getListModel(QString currentInput) {
}

void OBDController::initCommands() {
	OBDCommandXMLHandler xmlconfiguration;
		XMLReader reader(&xmlconfiguration);
		std::cout << "parsing file: " << Configuration::getInstance()->getOBDCommandConfigFilePath() << std::endl;
		reader.parseFile(Configuration::getInstance()->getOBDCommandConfigFilePath());

		int i = 0;

		for(ServiceModeInput input : xmlconfiguration.getParsedData()){
			std::vector<ObdCommand*> pids;
			for(OBDCommandInput command: input.commands_){
				pids.push_back(new ObdCommand(input.sid_, command));

				i++;
			}
			for(unsigned int sid: input.sid_){
				commands_[sid] = pids;
			}
		}
		std::cout << "Parsed commands: " << i << std::endl;
}
