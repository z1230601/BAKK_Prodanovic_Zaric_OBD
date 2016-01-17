#include "DBExecuter.h"
#include <boost/algorithm/string/join.hpp>
#include <iostream>

DBExecuter::DBExecuter()
{
    //TODO: Mayba so:
//	database_ = new DBRepresenter(DBConfigurator::getInstance->getDefaultDatabaseConfigurationFilePath());
    std::cout<< "Please do not use this constructor!!!\n";
}

DBExecuter::DBExecuter(std::string configuration)
{
    database_ = new DBRepresenter(configuration);
    tablenames_.push_back("Powertrain");
    tablenames_.push_back("Chassis");
    tablenames_.push_back("Network");
    tablenames_.push_back("Body");
}

DBExecuter::DBExecuter(DBRepresenter* representer)
{
    database_ = representer;
    tablenames_.push_back("Powertrain");
    tablenames_.push_back("Chassis");
    tablenames_.push_back("Network");
    tablenames_.push_back("Body");
}

DBExecuter::~DBExecuter()
{
    delete database_;
}

DBRepresenter* DBExecuter::getDatabase()
{
    return database_;
}
void DBExecuter::setDatabase(DBRepresenter* database)
{
    database_ = database;
}
SQLTable DBExecuter::readData(std::string table,
        std::vector<std::string> columns, std::string condition)
{
    database_->connectToDatabase();
    std::string columns_as_string_ = boost::algorithm::join(columns, ", ");
    std::string query = "SELECT " + columns_as_string_ + " FROM " + table
            + " WHERE " + condition;
    SQLTable ret = database_->executeSQLStatement(query);
    database_->closeConnection();
    return ret;
}

bool DBExecuter::insertData(std::string table, std::vector<std::string> columns,
        SQLTable data)
{
    try
    {
        database_->connectToDatabase();
        std::string columns_as_string_ = boost::algorithm::join(columns, ", ");
        std::string data_values_ = getValuesFromInput(data);
        std::string query = "INSERT INTO " + table + " (" + columns_as_string_
                + ") VALUES " + data_values_;
        database_->executeSQLStatement(query);
        database_->closeConnection();
        return true;
    } catch (sql::SQLException &err)
    {
        std::cout << "Caught exception: " << err.what() << std::endl;
        return false;
    }
    return true;
}

void DBExecuter::deleteData(std::string table, std::vector<std::string> columns,
        std::vector<std::string> condition)
{
    database_->connectToDatabase();
    std::string columns_as_string_ = boost::algorithm::join(columns, ", ");
    std::string conditions_as_string_ = boost::algorithm::join(condition, ", ");

    std::string statement = "DELETE FROM " + table + " WHERE ("
            + columns_as_string_ + ") = (" + conditions_as_string_ + ")";
    database_->executeSQLStatement(statement);
    database_->closeConnection();
}

std::string DBExecuter::getValuesFromInput(SQLTable data)
{
    std::string ret = "";

    for(unsigned int i = 0; i < data.size(); i++)
    {
        ret += "('";
        ret += boost::algorithm::join(data.at(i), "','");
        ret += "'),";
    }

    ret = ret.substr(0, ret.size() - 1);

    return ret;
}

std::vector<std::string> DBExecuter::getTablenames() const
{
    std::cout << "Enter Db Exectuor\n";
    std::cout << "Table name are: " + tablenames_.size() << "long\n";
    return tablenames_;
}

