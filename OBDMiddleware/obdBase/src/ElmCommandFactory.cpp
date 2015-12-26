#include "ElmCommandFactory.h"
#include "../../configurations/src/ElmCommandXMLHandler.h"
#include "../../configurations/src/XMLReader.h"

ElmCommandFactory::ElmCommandFactory() {
	// TODO Auto-generated constructor stub

}

ElmCommandFactory::~ElmCommandFactory() {
	// TODO Auto-generated destructor stub
}

std::vector<ElmCommand*> ElmCommandFactory::createElmCommands(std::string xmlpath) {
    ElmCommandXMLHandler* handler = new ElmCommandXMLHandler();
    XMLReader reader(handler);

    std::vector<ElmCommand*> elmcommands;
    if(reader.parseFile(xmlpath)){
       std::vector<ElmCommandInput> configs = handler->getParsedCommands();
       for(ElmCommandInput input: configs){
           elmcommands.push_back(new ElmCommand(input));
       }
    }

    return elmcommands;
}


