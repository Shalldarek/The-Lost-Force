#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

class Controller {
    public:
        void printAllCharacters(sql::Connection* con);
        void addCharacter(sql::Connection* con, int id, std::string name, std::string side, std::string language);
};