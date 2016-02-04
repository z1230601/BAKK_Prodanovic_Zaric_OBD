#include "DiagnosticTroubleCode.h"
#include "../../databaseManagement/src/DBExecuter.h"
#include "../../configurations/src/Configuration.h"

#include <sstream>

DiagnosticTroubleCode::DiagnosticTroubleCode()
        : assembly_area_(0), code_class_(""), source_class_(""), description_(
                ""), code_class_ID_(-1), source_class_ID_(-1), fault_ID_(-1), valid_construction_(
                false)
{

}

DiagnosticTroubleCode::DiagnosticTroubleCode(std::string table,
        std::string code_class_as_hex_string,
        std::string source_class_as_hex_string,
        std::string fault_id_as_hex_string, std::string description,
        bool is_database)
        : description_(description)
{
    std::map<unsigned int, std::string>::iterator it = assembly_table_.begin();
    for(; it != assembly_table_.end(); it++)
    {
        if((*it).second.compare(table) == 0
                || (table.size() == 1
                        && (*it).second.substr(0, 1).compare(table) == 0))
        {
            assembly_area_ = (*it).first;
            break;
        }
    }
    try
    {
        int base = 16;

        if(is_database)
        {
            base = 10;
        }
        code_class_ID_ = std::stoi(code_class_as_hex_string, nullptr, base);
        source_class_ID_ = std::stoi(source_class_as_hex_string, nullptr, base);
        fault_ID_ = std::stoi(fault_id_as_hex_string, nullptr, base);
    } catch (std::exception & e)
    {
        std::cout << e.what() << std::endl;
        return;
    }
    if(!parseClasses(true))
    {
        return;
    }

    valid_construction_ = true;
}

DiagnosticTroubleCode::DiagnosticTroubleCode(unsigned int assembly_id,
        unsigned int code_id, unsigned int source_id, unsigned int fault_id,
        std::string &description)
        : assembly_area_(assembly_id), description_(description), code_class_ID_(
                code_id), source_class_ID_(source_id), fault_ID_(fault_id)
{

    if(!parseClasses(true))
    {
        return;
    }

    valid_construction_ = true;
}

DiagnosticTroubleCode::DiagnosticTroubleCode(unsigned int assembly_id,
        std::string &codeclass, std::string &sourceclass, unsigned int fault_id,
        std::string &description)
        : assembly_area_(assembly_id), code_class_(codeclass), source_class_(
                sourceclass), description_(description), fault_ID_(fault_id)
{

    if(!parseClasses(false))
    {
        return;
    }

    valid_construction_ = true;
}

DiagnosticTroubleCode::~DiagnosticTroubleCode()
{
    // TODO Auto-generated destructor stub
}

bool DiagnosticTroubleCode::parseClasses(bool idMode)
{
    if(idMode)
    {
        code_class_ = getStringFromIdDB("CodeClass", std::vector<std::string> {
                "Property" },
                "ID = \"" + std::to_string(code_class_ID_) + "\"");
        source_class_ = getStringFromIdDB("Source", std::vector<std::string> {
                "Name" }, "ID = \"" + std::to_string(source_class_ID_) + "\"");

        if(source_class_.empty() || code_class_.empty())
        {
            return false;
        }
    } else
    {
        code_class_ID_ = getIdFromStringDB("CodeClass",
                std::vector<std::string> { "ID" },
                "Property = \"" + code_class_ + "\"");

        source_class_ID_ = getIdFromStringDB("Source",
                std::vector<std::string> { "ID" },
                "Name = \"" + source_class_ + "\"");
        if(code_class_ID_ == (unsigned int) -1
                || source_class_ID_ == (unsigned int) -1)
        {
            return false;
        }
    }
    return true;
}

std::string DiagnosticTroubleCode::getStringFromIdDB(std::string tablename,
        std::vector<std::string> columnnames, std::string condition)
{
    DBExecuter exec(Configuration::getInstance()->getDatabaseConfigFilePath());
    std::vector<std::vector<std::string>> readData = exec.readData(tablename,
            columnnames, condition);

    if(readData.size() == 2 && readData.at(1).size() == 1)
    {
        return std::string(readData.at(1).at(0));

    } else
    {
        return "";
    }
}
unsigned int DiagnosticTroubleCode::getIdFromStringDB(std::string tablename,
        std::vector<std::string> columnnames, std::string condition)
{
    DBExecuter exec(Configuration::getInstance()->getDatabaseConfigFilePath());
    std::vector<std::vector<std::string>> readData = exec.readData(tablename,
            columnnames, condition);
    if(readData.size() >= 2 && readData.at(1).size() == 1)
    {
        return std::stoi(readData.at(1).at(0));
    } else
    {
        return -1;
    }
}

unsigned int DiagnosticTroubleCode::idsFromHexValue(unsigned int hexvalue,
        unsigned int id_position)
{
    unsigned int bitmask = 0xF << (id_position * (HEX_LENGTH));
    if(id_position <= 1)
    {
        bitmask |= 0xF;
        id_position = 0;
    }
    return ((hexvalue & bitmask) >> (id_position * (HEX_LENGTH)));
}

// GETTER

bool DiagnosticTroubleCode::isValidlyConstructed()
{
    return valid_construction_;
}

bool DiagnosticTroubleCode::alreadyInDatabase(DBExecuter* dbexecuter)
{
    std::string condition = "`ID_CodeClass` = " + std::to_string(code_class_ID_)
            + " AND `ID_Source` = " + std::to_string(source_class_ID_)
            + " AND `ID_Fault` = " + std::to_string(fault_ID_);

    std::cout << assembly_table_.at(assembly_area_) << " - " << condition
            << std::endl;

    std::vector<std::vector<std::string>> readData = dbexecuter->readData(
            assembly_table_.at(assembly_area_),
            std::vector<std::string> { "*" }, condition);

    return readData.size() >= 2;
}

void DiagnosticTroubleCode::addToDatabase(DBExecuter* dbexecuter)
{
    std::vector<std::string> columns { "ID", "ID_CodeClass", "ID_Source",
            "ID_Fault", "Description" };

    unsigned int id = ((((code_class_ID_) << (3 * HEX_LENGTH))
            | (source_class_ID_ << (2 * HEX_LENGTH))) | fault_ID_);

    std::vector<std::vector<std::string> > data { { std::to_string(id),
            std::to_string(code_class_ID_), std::to_string(source_class_ID_),
            std::to_string(fault_ID_), description_ } };

    dbexecuter->insertData(assembly_table_.at(assembly_area_), columns, data);
}

void DiagnosticTroubleCode::removeFromDatabase(DBExecuter* dbexecuter)
{
    std::vector<std::string> columns { "ID" };

    unsigned int id = ((((code_class_ID_) << (3 * HEX_LENGTH))
            | (source_class_ID_ << (2 * HEX_LENGTH))) | fault_ID_);

    std::vector<std::string> data { std::to_string(id) };

    dbexecuter->deleteData(assembly_table_.at(assembly_area_), columns, data);
}

std::string DiagnosticTroubleCode::getCodeClass()
{
    return code_class_;
}

std::string DiagnosticTroubleCode::getSourceClass()
{
    return source_class_;
}

std::string DiagnosticTroubleCode::getDescription()
{
    return description_;
}

unsigned int DiagnosticTroubleCode::getCodeClassID()
{
    return code_class_ID_;
}

unsigned int DiagnosticTroubleCode::getSourceClassID()
{
    return source_class_ID_;
}

unsigned int DiagnosticTroubleCode::getFaultID()
{
    return fault_ID_;
}

void DiagnosticTroubleCode::fromElmHexValue(int hexvalue)
{
    unsigned int byte1 = idsFromHexValue(hexvalue, 3);
    assembly_area_ = byte1 >> HEX_LENGTH / 2;
    code_class_ID_ = byte1 & 0x3;
    source_class_ID_ = idsFromHexValue(hexvalue, 2);
    fault_ID_ = idsFromHexValue(hexvalue, 1);

    valid_construction_ = true;
}

unsigned int DiagnosticTroubleCode::toElmHexValue()
{
    return (((((assembly_area_ << HEX_LENGTH / 2) | code_class_ID_)
            << (3 * HEX_LENGTH)) | (source_class_ID_ << (2 * HEX_LENGTH)))
            | fault_ID_);
}

void DiagnosticTroubleCode::setAssemblyID(unsigned int id)
{
    if(id < 4)
    {
        assembly_area_ = id;
    }
}

std::string DiagnosticTroubleCode::getAssemblyName()
{
    if(assembly_table_.find(assembly_area_) != assembly_table_.end())
    {
        return assembly_table_.at(assembly_area_);
    }
    return "UNKNOWN";
}

std::string DiagnosticTroubleCode::getTableName()
{
    return getAssemblyName();
}

unsigned int DiagnosticTroubleCode::getAssemblyAreaID()
{
    return assembly_area_;
}

std::string DiagnosticTroubleCode::toStringForView()
{
    std::stringstream ret;
    if(assembly_area_ != 3)
    {
        ret << assembly_table_.at(assembly_area_).substr(0, 1);
    } else
    {
        ret << "U";
    }
    ret << std::hex << code_class_ID_ << source_class_ID_
            << (fault_ID_ < 16 ? "0" : "") << fault_ID_ << std::dec;

    ret << "\t" << description_;

    return ret.str();
}

