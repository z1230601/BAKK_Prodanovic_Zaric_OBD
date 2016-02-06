#include "CommunicationController.h"
#include "USBRequestHandler.h"
#include "EmulationDevice.h"

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
	emulation_->getRequestHandler()->getDevice();
}

