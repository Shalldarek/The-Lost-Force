#include <iostream>
#include "../include/Controller.h"


void Controller::printAllCharacters(sql::Connection* con) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT id, character_name, force_side, language, dialect FROM characters");
        sql::ResultSet *res = pstmt->executeQuery();

        std::cout << "--- CHARACTER LIST ---" << std::endl;
        while (res->next()) {
            std::cout << "ID: " << res->getInt("id") 
                 << " | Name: " << res->getString("character_name") 
                 << " | Side: " << res->getString("force_side")
                 << " | Language: " << res->getString("language") 
                 << " | Dialect: " << res->getString("dialect") << std::endl;
        }

        delete res;
        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cout << "# ERR SELECT: " << e.what() << std::endl;
    }
}

void Controller::addCharacter(sql::Connection* con, int id, std::string name, std::string side, std::string language) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement(
            "INSERT INTO characters (id, character_name, force_side, language, studs) VALUES (?, ?, ?, ?, 0)"
        );
        
        pstmt->setInt(1, id);
        pstmt->setString(2, name);
        pstmt->setString(3, side);
        pstmt->setString(4, language);
        pstmt->executeUpdate(); 

        std::cout << "Character " << name << " was added!" << std::endl;

        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cout << "# ERR INSERT: " << e.what() << std::endl;
    }
}