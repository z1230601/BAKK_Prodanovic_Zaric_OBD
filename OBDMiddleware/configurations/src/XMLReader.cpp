/*
 * XMLReader.cpp
 *
 *  Created on: Dec 25, 2015
 *      Author: zlatan
 */

#include "XMLReader.h"
#include <libxml++/libxml++.h>
#include <iostream>

XMLReader::XMLReader(DefaultXMLHandler* handler)
        : handler_(handler)
{
}

XMLReader::~XMLReader()
{
}

bool XMLReader::parseFile(std::string configurationFile)
{
    try
    {
        xmlpp::DomParser parser;
        parser.set_validate();
        parser.set_substitute_entities();
        parser.parse_file(configurationFile);
        if(parser)
        {
            iterateChildren(parser.get_document()->get_root_node());
        }
    } catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

void XMLReader::iterateChildren(const xmlpp::Node* parent)
{
    xmlpp::Node::NodeList children = parent->get_children();
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        handler_->handleNode(*it);
        iterateChildren(*it);
    }
}

