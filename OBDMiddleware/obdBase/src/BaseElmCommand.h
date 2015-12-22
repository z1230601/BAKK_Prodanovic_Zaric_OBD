#ifndef ELMCOMMAND_H_
#define ELMCOMMAND_H_

#include <string>

class BaseElmCommand {
protected:
	std::string command_;

private:
	float min_req_version_;
	std::string description_;
	std::string group_;

public:
	BaseElmCommand();
	BaseElmCommand(float minReqElmVersion, std::string command, std::string description, std::string group);
	virtual ~BaseElmCommand();
	float getMinimumRequiredElmVersion();
	std::string getCommand();
	std::string getDescription();
	std::string getGroup();
    unsigned int getCommandLength();

	virtual uint8_t* getCommandAsByteArray() = 0;

	void setMinimumRequiredElmVersion(float version);
	void setCommand(std::string command);
	void setDescription(std::string description);
	void setGroup(std::string group);
};

#endif /* ELMCOMMAND_H_ */
