#ifndef OBDCOMMANDCONTROLLER_H_
#define OBDCOMMANDCONTROLLER_H_

#include <vector>
#include <map>
#include "ObdCommand.h"
#include "DiagnosticTroubleCode.h"
#include "DBRepresenter.h"
#include "QtCore"

class OBDController {
public:
	OBDController();
	virtual ~OBDController();

	void init();
	QStringList getListModel(QString currentInput);

private:
	std::map<unsigned int, std::vector<ObdCommand*>> commands_;
	std::vector<DiagnosticTroubleCode*> current_loaded_trouble_codes_;

	void initCommands();
};

#endif /* OBDCOMMANDCONTROLLER_H_ */
