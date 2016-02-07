#ifndef COMMUNICATIONCONTROLLER_H_
#define COMMUNICATIONCONTROLLER_H_
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QStringListModel>
#include "USBEmulationSupervisor.h"
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

class CommunicationController {

private:
	USBEmulationSupervisor* emulation_;
	QStringListModel* languages_model_;
	boost::thread emulation_thread_;
public:
	CommunicationController();
	virtual ~CommunicationController();

	void initConfigurationPath(QLineEdit* elmcfg);
	void initLanguage(QComboBox* laguage_selection);
	void initDescriptors(QLineEdit* manStringInput, QLineEdit* productStringInput,QLineEdit* serialStringInput);

	void saveSettings(QString config_path, QString language, QString manString, QString productString, QString serialString);
	void runEmulation();
	void stopEmulation();
};

#endif /* COMMUNICATIONCONTROLLER_H_ */
