#include "CommunicationController.h"
#include "USBRequestHandler.h"
#include "EmulatedDevice.h"
#include "Configuration.h"

#define MANUNFACTURER_STRINGDESCRIPTOR_ID 1
#define PRODUCT_STRINGDESCRIPTOR_ID 2
#define SERIAL_STRINGDESCRIPTOR_ID 3

CommunicationController::CommunicationController() {
	emulation_ = new USBEmulationSupervisor();
}

CommunicationController::~CommunicationController() {

}

void CommunicationController::initConfigurationPath(QLineEdit* elmcfg) {
	elmcfg->setText(QString::fromStdString(Configuration::getInstance()->getOBDCommandConfigFilePath()));
}

void CommunicationController::initLaguage(QComboBox* laguage_selection) {

}

void CommunicationController::initDescriptors(QLineEdit* manStringInput,
		QLineEdit* productStringInput, QLineEdit* serialStringInput) {
	std::string manString = emulation_->getRequestHandler()->getDevice()->getStringFromId(MANUNFACTURER_STRINGDESCRIPTOR_ID);
	std::string productString = emulation_->getRequestHandler()->getDevice()->getStringFromId(PRODUCT_STRINGDESCRIPTOR_ID);
	std::string serialString = emulation_->getRequestHandler()->getDevice()->getStringFromId(SERIAL_STRINGDESCRIPTOR_ID);
	manStringInput     ->setText(QString(manString.c_str()));
	productStringInput ->setText(QString(productString.c_str()));
	serialStringInput  ->setText(QString(serialString.c_str()));
}

