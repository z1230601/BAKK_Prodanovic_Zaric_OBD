#ifndef DIAGNOSTICTROUBLECODE_H_
#define DIAGNOSTICTROUBLECODE_H_

#include <string>
#include <vector>

class DiagnosticTroubleCode {
private:
	std::string code_class_;
	std::string source_class_;
	std::string description_;
	unsigned int code_class_ID_;
	unsigned int source_class_ID_;
	bool valid_construction_;

	bool parseClasses(bool idMode);
	std::string getStringFromIdDB(std::string tablename, std::vector<std::string> columnnames, std::string condition);
	unsigned int getIdFromStringDB(std::string tablename, std::vector<std::string> columnnames, std::string condition);
public:
	DiagnosticTroubleCode();
	DiagnosticTroubleCode(unsigned int code_id, unsigned int source_id, std::string &description);
	DiagnosticTroubleCode(std::string &codeclass, std::string &sourceclass, std::string &description);
	virtual ~DiagnosticTroubleCode();

	bool isValidlyConstructed();
	std::string getCodeClass();
	std::string getSourceClass();
	std::string getDescription();
	unsigned int getCodeClassID();
	unsigned int getSourceClassID();
};

#endif /* DIAGNOSTICTROUBLECODE_H_ */
