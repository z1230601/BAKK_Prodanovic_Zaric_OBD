#ifndef OBDCOMMANDCONTROLLER_H_
#define OBDCOMMANDCONTROLLER_H_

#include <vector>
#include <map>
#include "ObdCommand.h"
#include "DiagnosticTroubleCode.h"
#include "DBRepresenter.h"
#include "DiagnosticTroubleCode.h"
#include <QStringList>
#include <QString>

class OBDController {
public:
	OBDController();
	virtual ~OBDController();

	void init();
	QStringList searchModelList(QString table, QString column, QString currentInput);
	QStringList getTableList();
	QStringList getColumnList(QString currentInput);

	QStringList addToPermanent(QString command);
	QStringList getCurrentDTCList();

private:
	std::map<unsigned int, std::vector<ObdCommand*>> commands_;

	std::vector<DiagnosticTroubleCode*> current_permanent_trouble_codes_;
	std::vector<std::string> columns_;
	std::map<QString, DiagnosticTroubleCode*> current_trouble_codes_;


	void initCommands();
	void freeDTC(std::vector<DiagnosticTroubleCode*> toFree);
	void freeDTC(std::map<QString, DiagnosticTroubleCode*> toFree);
};

#endif /* OBDCOMMANDCONTROLLER_H_ */
