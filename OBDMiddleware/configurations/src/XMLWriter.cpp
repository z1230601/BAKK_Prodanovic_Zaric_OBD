#include "XMLWriter.h"
#include <iostream>

XMLWriter::XMLWriter(DefaultXMLHandler* handler)
        : handler_(handler)
{
}

XMLWriter::~XMLWriter()
{
}

bool XMLWriter::writeFile(std::string configurationFile)
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
            parser.get_document()->write_to_file_formatted(configurationFile);
        }
    } catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

void XMLWriter::iterateChildren(const xmlpp::Node* parent)
{
    xmlpp::Node::NodeList children = parent->get_children();
    for(xmlpp::Node::NodeList::iterator it = children.begin();
            it != children.end(); ++it)
    {
        handler_->handleNode(*it);
        iterateChildren(*it);
    }
}

