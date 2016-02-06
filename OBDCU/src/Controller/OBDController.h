#ifndef OBDCOMMANDCONTROLLER_H_
#define OBDCOMMANDCONTROLLER_H_

#include <vector>
#include <map>
#include <utility>
#include <tuple>

#include "ObdCommand.h"
#include "DiagnosticTroubleCode.h"
#include "DBRepresenter.h"
#include "DiagnosticTroubleCode.h"
#include <QStringList>
#include <QString>
#include <QStringListModel>

class OBDController {
public:
	OBDController();
	virtual ~OBDController();

	void init();
	void searchForDTC(QString table, QString column, QString currentInput);
	QStringList getTableList();

	void updateColumnModel(QString currentInput);
	void updateDTCList();
	void updatePermanentModel();
	void updatePendingModel();

	void addToPermanent(QString command);
	void removeFromPermanent(QString command);

	void addToPending(QString command);
	void removeFromPending(QString command);

	bool checkDTCExistence(DiagnosticTroubleCode& DTC_to_add, QString code, QString description);
	bool addDTCToDatabase(QString code, QString description);
	void removeDTCFromDatabase(QString actual);
	std::pair<QString, QString> getDTCData(QString actual);
	void editDTCInDatabase(QString actual, QString code, QString description);

	QStringListModel* getColumnModel() const;
	QStringListModel* getDtcListModel() const;
	QStringListModel* getPendingListModel() const;
	QStringListModel* getPermanentListModel() const;
	QStringListModel* getTableModel();

private:
	std::map<unsigned int, std::vector<ObdCommand*>> commands_;

	std::vector<DiagnosticTroubleCode*> current_permanent_trouble_codes_;
	std::vector<DiagnosticTroubleCode*> current_pending_trouble_codes_;

	std::vector<std::string> columns_;
	std::map<QString, DiagnosticTroubleCode*> current_trouble_codes_;
	QStringListModel* column_model_;
	QStringListModel* table_model_;
	QStringListModel* dtc_list_model_;
	QStringListModel* permanent_list_model_;
	QStringListModel* pending_list_model_;
	std::tuple<QString, QString, QString> last_search_;


	void initCommands();
	void initViewModels();

	void freeDTC(std::vector<DiagnosticTroubleCode*> toFree);
	void freeDTC(std::map<QString, DiagnosticTroubleCode*> toFree);

	bool inCurrentPermanentCodes(std::string stringForView);
	bool inCurrentPendingCodes(std::string stringForView);
};

#endif /* OBDCOMMANDCONTROLLER_H_ */
