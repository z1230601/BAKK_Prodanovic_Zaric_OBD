/*
 * XMLReader.cpp
 *
 *  Created on: Dec 25, 2015
 *      Author: zlatan
 */

#include "XMLReader.h"
#include <libxml++/libxml++.h>
#include <iostream>

XMLReader::XMLReader(DefaultXMLHandler* handler):
handler_(handler){}

XMLReader::~XMLReader(){}


bool XMLReader::parseFile(std::string configurationFile) {
    try{
    xmlpp::DomParser parser;
    parser.set_validate();
    parser.set_substitute_entities();
    parser.parse_file(configurationFile);
    if (parser) {
        const xmlpp::Node* currentNode = parser.get_document()->get_root_node();

        xmlpp::Node::NodeList children = currentNode->get_children();
        for(xmlpp::Node::NodeList::iterator it = children.begin(); it != children.end(); ++it) {
            handler_->handleNode(*it);
        }
    }
    }catch(std::exception & e){
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}



