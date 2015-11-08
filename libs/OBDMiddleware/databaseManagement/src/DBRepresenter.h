#ifndef DBREPRESENTER_H_
#define DBREPRESENTER_H_

#include <string>

class DBRepresenter {
private:
	bool valid_construction_ = false;

public:
	DBRepresenter();
	DBRepresenter(std::string configurationFile);
	~DBRepresenter();

	bool isValid();
};

#endif /* DBREPRESENTER_H_ */
