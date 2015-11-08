#include "DBRepresenter.h"
#include <libxml++/libxml++.h>

DBRepresenter::DBRepresenter() {

	valid_construction_ = true;
}

DBRepresenter::DBRepresenter(std::string configurationFile) {
	xmlpp::DomParser parser;
	parser.set_validate();
	parser.set_substitute_entities(); //We just want the text to be resolved/unescaped automatically.
	parser.parse_file(configurationFile);
	if (parser) {
		//Walk the tree:
		const xmlpp::Node* pNode = parser.get_document()->get_root_node(); //deleted by DomParser.
	}
}

DBRepresenter::~DBRepresenter() {

}

bool DBRepresenter::isValid() {
	return valid_construction_;
}
