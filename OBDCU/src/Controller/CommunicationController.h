#ifndef COMMUNICATIONCONTROLLER_H_
#define COMMUNICATIONCONTROLLER_H_
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QStringListModel>
#include "USBEmulationSupervisor.h"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <QTextBrowser>
#include <map>
#include <string>

class CommunicationController {

private:
	USBEmulationSupervisor* emulation_;
	QStringListModel* languages_model_;
	boost::thread emulation_thread_;
	QTextBrowser* log_browser_;
	std::map<std::string, std::string> response_mapping_;




public:
	CommunicationController();
	virtual ~CommunicationController();

	void initConfigurationPath(QLineEdit* elmcfg);
	void initLanguage(QComboBox* laguage_selection);
	void initDescriptors(QLineEdit* manStringInput, QLineEdit* productStringInput,QLineEdit* serialStringInput);

	void saveSettings(QString config_path, QString language, QString manString, QString productString, QString serialString);
	void runEmulation();
	void stopEmulation();

	void setLogDisplay(QTextBrowser* emulationLogBrowser);
	void refresh();

	void commandCallback(std::string &got_command);
};

#endif /* COMMUNICATIONCONTROLLER_H_ */
