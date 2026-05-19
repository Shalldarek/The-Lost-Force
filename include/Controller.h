#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

class Controller {
    public:
        void printAllCharacters(sql::Connection* con);
        void printCharacter(sql::Connection* con, int studs);
        void addCharacter(sql::Connection* con, int id, std::string name, std::string side, std::string language);
        void removeCharacter(sql::Connection* con, int id);
        void updateCharacter(sql::Connection* con, int id, std::string name, std::string side, std::string language, std::string dialect);
};