#ifndef DIAGNOSTICTROUBLECODE_H_
#define DIAGNOSTICTROUBLECODE_H_

#define HEX_LENGTH 4

#include <string>
#include <vector>
#include <map>

class DiagnosticTroubleCode {
private:
	std::map<unsigned int, std::string> assembly_table_{
		{0,"Powertrain"},
		{1,"Chassis"},
		{2,"Body"},
		{3,"Network"},
	};

	unsigned int assembly_area_;
	std::string code_class_;
	std::string source_class_;
	std::string description_;
	unsigned int code_class_ID_;
	unsigned int source_class_ID_;
	unsigned int fault_ID_;
	bool valid_construction_;

	bool parseClasses(bool idMode);
	std::string getStringFromIdDB(std::string tablename, std::vector<std::string> columnnames, std::string condition);
	unsigned int getIdFromStringDB(std::string tablename, std::vector<std::string> columnnames, std::string condition);
	unsigned int idsFromHexValue(unsigned int hexvalue, unsigned int id_position);
public:
	DiagnosticTroubleCode();
	DiagnosticTroubleCode(unsigned int assembly_id, unsigned int code_id, unsigned int source_id, unsigned int fault_id, std::string &description);
	DiagnosticTroubleCode(unsigned int assembly_id, std::string &codeclass, std::string &sourceclass, unsigned int fault_id, std::string &description);
	DiagnosticTroubleCode(std::string table, std::string codeClassAsHexString, std::string source_class_as_hex_string,
	        std::string fault_id_as_hex_string, std::string description);
	virtual ~DiagnosticTroubleCode();

	bool isValidlyConstructed();
	std::string getCodeClass();
	std::string getSourceClass();
	std::string getDescription();
	std::string getAssemblyName();
	std::string getTableName();

	std::string toStringForView();

	unsigned int getAssemblyAreaID();
	unsigned int getCodeClassID();
	unsigned int getSourceClassID();
	unsigned int getFaultID();

	void setAssemblyID(unsigned int id);

	void fromElmHexValue(int hexvalue);
	unsigned int toElmHexValue();


};

#endif /* DIAGNOSTICTROUBLECODE_H_ */
