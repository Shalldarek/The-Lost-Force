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

void Controller::printCharacter(sql::Connection* con, int studs) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT id, character_name, force_side, language, dialect FROM characters WHERE studs = ?");
        pstmt->setInt(1, studs);
        sql::ResultSet *res = pstmt->executeQuery();

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

void Controller::removeCharacter(sql::Connection* con, int id) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("DELETE FROM characters WHERE id = ?");

        pstmt->setInt(1, id);
        pstmt->executeUpdate();
        
        std::cout << "The row was deleted" << std::endl;

        delete pstmt;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR DELETE: " << e.what() << std::endl;
    }
}

void Controller::updateCharacter(sql::Connection* con, int id, std::string name, std::string side, std::string language, std::string dialect) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "UPDATE characters SET character_name = ?, force_side = ?, language = ?, dialect = ? WHERE id = ?"
        );

        pstmt->setString(1, name);
        pstmt->setString(2, side);
        pstmt->setString(3, language);
        pstmt->setString(4, dialect);
        pstmt->setInt(5, id);

        int rows_affected = pstmt->executeUpdate();
        
        if (rows_affected > 0) {
            std::cout << "Data postavy " << name << " byla uspesne upravena!" << std::endl;
        } else {
            std::cout << "Chyba: Postava s ID " << id << " v databazi neexistuje!" << std::endl;
        }

        delete pstmt;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR UPDATE: " << e.what() << std::endl;
    }
}