#include "CommunicationController.h"
#include "USBRequestHandler.h"
#include "EmulatedDevice.h"
#include "Configuration.h"
#include <iostream>
#include <QStringList>
#include <pthread.h>
#include <boost/bind.hpp>

#define MANUNFACTURER_STRINGDESCRIPTOR_ID 1
#define PRODUCT_STRINGDESCRIPTOR_ID 2
#define SERIAL_STRINGDESCRIPTOR_ID 3

CommunicationController::CommunicationController() {
	emulation_ = new USBEmulationSupervisor();
	languages_model_ = new QStringListModel();

}

CommunicationController::~CommunicationController() {

}

void CommunicationController::initConfigurationPath(QLineEdit* elmcfg) {
	elmcfg->setText(
			QString::fromStdString(
					Configuration::getInstance()->getOBDCommandConfigFilePath()));
}

void CommunicationController::initLanguage(QComboBox* language_selection) {
	QStringList languages;
	std::cout << "init languages"
			<< emulation_->getRequestHandler()->getDevice()->getSelectableLanguages().size()
			<< "\n";
	for (std::string lang : emulation_->getRequestHandler()->getDevice()->getSelectableLanguages()) {
		std::cout << "ADDING: " << lang << std::endl;
		languages << QString(lang.c_str());
	}
	languages_model_->setStringList(languages);
	language_selection->setModel(languages_model_);
}

void CommunicationController::initDescriptors(QLineEdit* manStringInput,
		QLineEdit* productStringInput, QLineEdit* serialStringInput) {
	std::string manString =
			emulation_->getRequestHandler()->getDevice()->getStringFromId(
					MANUNFACTURER_STRINGDESCRIPTOR_ID);
	std::string productString =
			emulation_->getRequestHandler()->getDevice()->getStringFromId(
					PRODUCT_STRINGDESCRIPTOR_ID);
	std::string serialString =
			emulation_->getRequestHandler()->getDevice()->getStringFromId(
					SERIAL_STRINGDESCRIPTOR_ID);
	std::cout << "Setting to:  " << manString << " " << productString << " "
			<< serialString << std::endl;
	manStringInput->setText(QString(manString.c_str()));
	productStringInput->setText(QString(productString.c_str()));
	serialStringInput->setText(QString(serialString.c_str()));
}

void CommunicationController::saveSettings(QString config_path,
		QString language, QString manString, QString productString,
		QString serialString) {
	Configuration::getInstance()->setOBDCommandConfigFilePath(
			config_path.toStdString());
	emulation_->getRequestHandler()->getDevice()->setCurrentLanguage(
			language.toStdString());
	emulation_->getRequestHandler()->getDevice()->setStringWithId(
			MANUNFACTURER_STRINGDESCRIPTOR_ID, manString.toStdString());
	emulation_->getRequestHandler()->getDevice()->setStringWithId(
			SERIAL_STRINGDESCRIPTOR_ID, serialString.toStdString());
	emulation_->getRequestHandler()->getDevice()->setStringWithId(
			PRODUCT_STRINGDESCRIPTOR_ID, productString.toStdString());
}

void CommunicationController::runEmulation() {
	boost::function<void (std::string)> callback = boost::bind(&CommunicationController::commandCallback, this, _1);
	emulation_->getRequestHandler()->getDevice()->setCallback(callback);
	if(emulation_->isRunning()){
		emulation_->terminate();
	}
	try {
		emulation_thread_ = boost::thread(&USBEmulationSupervisor::run,
				emulation_);
	} catch (boost::thread_interrupted& interruption) {
		// thread was interrupted, this is expected.
		std::cout << "interrupted" << std::endl;
	} catch (std::exception& e) {

	}
}

void CommunicationController::stopEmulation() {
	if(emulation_->isRunning()){
		emulation_->terminate();
	}
}

void CommunicationController::setLogDisplay(QTextBrowser* emulationLogBrowser) {
	log_browser_ = emulationLogBrowser;
}


void CommunicationController::commandCallback(std::string &got_command) {
	if(got_command.empty()){
		return;
	}
	std::string pending = "0700";
	std::string permanent = "0300";
	std::string deleteRequest = "0400";
	if(got_command.at(0) == '0'){
		emulation_->getRequestHandler()->getDevice()->addAnswerTo
	}
	if(got_command == pending){
		std::cout << "pending command"<< std::endl;
	}
	else if(got_command == permanent){
		std::cout << "permanent command"<< std::endl;
	}else if(got_command == deleteRequest){
		std::cout << "delete command"<< std::endl;
	}else if(got_command.find("at") == 0){
		std::cout << "elm command"<< std::endl;
	}else{
		std::cout << "Command get: " << got_command << std::endl;
	}
}

void CommunicationController::refresh() {
	std::string new_string = emulation_->getMessages();
	log_browser_->setText(QString(new_string.c_str()));
}



