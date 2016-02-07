#ifndef OBDCUXMLHANDLER_H_
#define OBDCUXMLHANDLER_H_

#include "DefaultXMLHandler.h"

#define DATABSECONFIG_TAG "databaseconfiguration"
#define OBDCONFIG_TAG "obdcommandconfiguration"
#define ELMCONFIG_TAG "elmcommandconfiguration"

class ObdcuXmlHandler :  public DefaultXMLHandler
{
public:
	ObdcuXmlHandler();
	virtual ~ObdcuXmlHandler();

	void handleNode(xmlpp::Node* node);
};

#endif /* OBDCUXMLHANDLER_H_ */
