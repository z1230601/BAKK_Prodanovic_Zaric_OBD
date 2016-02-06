#ifndef COMMUNICATIONCONTROLLER_H_
#define COMMUNICATIONCONTROLLER_H_
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include "USBEmulationSupervisor.h"

class CommunicationController {

private:
	USBEmulationSupervisor* emulation_;

public:
	CommunicationController();
	virtual ~CommunicationController();

	void initConfigurationPath(QLineEdit* elmcfg);
	void initLaguage(QComboBox* laguage_selection);
	void initDescriptors(QLineEdit* manStringInput, QLineEdit* productStringInput,QLineEdit* serialStringInput);

};

#endif /* COMMUNICATIONCONTROLLER_H_ */
