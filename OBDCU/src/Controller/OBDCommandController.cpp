#include "OBDCommandController.h"
#include "XMLReader.h"
#include "OBDCommandXMLHandler.h"
#include "Configuration.h"

OBDCommandController::OBDCommandController() {
	OBDCommandXMLHandler xmlconfiguration;
	XMLReader reader(&xmlconfiguration);
	reader.parseFile(Configuration::getInstance()->getOBDCommandConfigFilePath());
}

OBDCommandController::~OBDCommandController() {

}

