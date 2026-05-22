#include <iostream>
#include "../include/Controller.h"


void Controller::printAllCharacters(sql::Connection* con) {
    try {
        sql::PreparedStatement *pstmt = con->prepareStatement("SELECT id, character_name, force_side, language, dialect, current_goal FROM characters");
        sql::ResultSet *res = pstmt->executeQuery();

        std::cout << "--- CHARACTER LIST ---" << std::endl;
        while (res->next()) {
            std::cout << "ID: " << res->getInt("id") 
                 << " | Name: " << res->getString("character_name") 
                 << " | Side: " << res->getString("force_side")
                 << " | Language: " << res->getString("language") 
                 << " | Dialect: " << res->getString("dialect") 
                 << " | Goal: " << res->getString("current_goal") << std::endl;
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
            std::cout << "The data about the character " << name << " were succesfully updated!" << std::endl;
        } else {
            std::cout << "ERROR: The character with the ID " << id << " doesn't exist in the database!" << std::endl;
        }

        delete pstmt;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR UPDATE: " << e.what() << std::endl;
    }
}

void Controller::removeAllCharacters(sql::Connection* con) {
    try{
        sql::PreparedStatement *pstmt = con->prepareStatement("TRUNCATE TABLE characters;");

        std::cout << "All records from this table were deleted" << std::endl;

        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cout << "# ERR TRUNCATE: " << e.what() << std::endl;
    }
    
}

void Controller::updateCharacterRank(sql::Connection* con, int id) {
    try {
        sql::PreparedStatement *pstmtSelect = con->prepareStatement("SELECT virtual_studs, force_side FROM characters WHERE id = ?");
        pstmtSelect->setInt(1, id);
        sql::ResultSet *res = pstmtSelect->executeQuery();

        if (res->next()) {
            int studs = res->getInt("virtual_studs");
            std::string side = res->getString("force_side");
            std::string newRank = "Unknown";

            if (side == "Jedi") {
                if (studs >= 500) newRank = "Grand Master";
                else if (studs >= 300) newRank = "Jedi Master";
                else if (studs >= 150) newRank = "Jedi Knight";
                else if (studs >= 50) newRank = "Padawan";
                else newRank = "Youngling";
            } 

            else if (side == "Sith") {
                if (studs >= 500) newRank = "Dark Lord";
                else if (studs >= 300) newRank = "Sith Lord";
                else if (studs >= 150) newRank = "Sith Warrior";
                else if (studs >= 50) newRank = "Apprentice";
                else newRank = "Acolyte";
            }

            else if (side == "Bounty Hunter") {
                if (studs >= 500) newRank = "Mandalorian Legend";
                else if (studs >= 300) newRank = "Elite Hunter";
                else if (studs >= 150) newRank = "Assassin";
                else if (studs >= 50) newRank = "Mercenary";
                else newRank = "Rookie";
            }

            sql::PreparedStatement *pstmtUpdate = con->prepareStatement("UPDATE characters SET char_rank = ? WHERE id = ?");
            pstmtUpdate->setString(1, newRank);
            pstmtUpdate->setInt(2, id);
            pstmtUpdate->executeUpdate();

            std::cout << "Hodnost aktualizována na: " << newRank << std::endl;
            delete pstmtUpdate;
        }

        delete res;
        delete pstmtSelect;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR UPDATE RANK: " << e.what() << std::endl;
    }
}

void Controller::setGoal(sql::Connection* con, int id, std::string goal) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "UPDATE characters SET current_goal = ? WHERE id = ?"
        );

        pstmt->setString(1, goal);
        pstmt->setInt(2, id);

        int rows_affected = pstmt->executeUpdate();
        
        if (rows_affected > 0) {
            std::cout << "The data about the character were succesfully updated!" << std::endl;
        } else {
            std::cout << "ERROR: The character with the ID " << id << " doesn't exist in the database!" << std::endl;
        }

        delete pstmt;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR UPDATE: " << e.what() << std::endl;
    }
}

void Controller::completeGoal(sql::Connection* con, int id) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE characters SET virtual_studs = virtual_studs + 5, current_goal = 'No goal set' WHERE id = ?");

        pstmt->setInt(1, id);

        int rows_affected = pstmt->executeUpdate();
        
        if (rows_affected > 0) {
            std::cout << "The data about the character were succesfully updated!" << std::endl;
        } else {
            std::cout << "ERROR: The character with the ID " << id << " doesn't exist in the database!" << std::endl;
        }
        
        delete pstmt;
    } catch (sql::SQLException &e) {
        std::cout << "# ERR UPDATE: " << e.what() << std::endl;
    }
}