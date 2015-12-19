#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>

class Configuration {
private:
	Configuration();
	static Configuration* instance_;
	std::string database_path_;

public:
	virtual ~Configuration();

	static Configuration* getInstance();

	std::string getDatabaseConfigFilePath();
	void setDatabaseConfigFilePath(std::string &path);
};

#endif /* CONFIGURATION_H_ */
