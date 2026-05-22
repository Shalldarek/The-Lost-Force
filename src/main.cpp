#include <iostream>
#include <string>
#include <limits> 
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "../include/Sith.h"
#include "../include/Jedi.h"
#include "Controller.h"

int main() {
    Controller* controller = new Controller();
    bool keep_cycle = true;
    std::string option_i;

    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection *con = driver->connect("tcp://127.0.0.1:3306", "Venca Srubar", "kylo_ren2005");
        con->setSchema("language_galaxy");

        while(keep_cycle) {
            std::cout << "\n*************** Database Controller ***************" << std::endl;
            std::cout << "Pick an option by it's number:" << std::endl;
            std::cout << "1. Print all records" << std::endl;
            std::cout << "2. Print one record (by ID)" << std::endl;
            std::cout << "3. Add a new character" << std::endl;
            std::cout << "4. Update a character" << std::endl;
            std::cout << "5. Remove a character" << std::endl;
            std::cout << "6. Remove ALL characters" << std::endl;
            std::cout << "7. Update character rank" << std::endl;
            std::cout << "8. Set goal" << std::endl;
            std::cout << "9. Complete goal" << std::endl;
            std::cout << "0. EXIT PROGRAM" << std::endl;
            std::cout << "***************************************************" << std::endl;
            std::cout << "> ";
            
            std::cin >> option_i;

            if (option_i == "1") {
                controller->printAllCharacters(con);
            } 
            else if (option_i == "2") {
                int studs;
                std::cout << "Enter the number of character's studs: ";
                std::cin >> studs;
                controller->printCharacter(con, studs);
            } 
            else if (option_i == "3") {
                int id;
                std::string name, side, language;
                std::cout << "Enter ID: "; std::cin >> id;
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                
                std::cout << "Enter the character name: "; std::getline(std::cin, name);
                std::cout << "Enter the character force side (Jedi / Sith / Bounty Hunter): "; std::getline(std::cin, side);
                std::cout << "Enter the language: "; std::getline(std::cin, language);
                
                controller->addCharacter(con, id, name, side, language);
            } 
            else if (option_i == "4") {
                int id;
                std::string name, side, language, dialect;
                std::cout << "Enter character ID: "; std::cin >> id;
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                std::cout << "New name: "; std::getline(std::cin, name);
                std::cout << "New force side: "; std::getline(std::cin, side);
                std::cout << "New language: "; std::getline(std::cin, language);
                std::cout << "New dialect: "; std::getline(std::cin, dialect);
                
                controller->updateCharacter(con, id, name, side, language, dialect);
            } 
            else if (option_i == "5") {
                int id;
                std::cout << "Enter the ID for deletation: ";
                std::cin >> id;
                controller->removeCharacter(con, id);
            } 
            else if (option_i == "6") {
                std::string confirm;
                std::cout << "Do you really wanna delete all records? (write yes if so): ";
                std::cin >> confirm;
                if (confirm == "yes") {
                    controller->removeAllCharacters(con);
                }
            } 
            else if (option_i == "7") {
                int id;
                std::cout << "Enter ID: ";
                std::cin >> id;
                controller->updateCharacterRank(con, id);
            } 
            else if (option_i == "8") {
                int id;
                std::string goal;
                std::cout << "Enter ID: "; std::cin >> id;
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                std::cout << "Enter a new goal: "; std::getline(std::cin, goal);
                controller->setGoal(con, id, goal);
            } 
            else if (option_i == "9") {
                int id;
                std::cout << "Enter ID: ";
                std::cin >> id;
                controller->completeGoal(con, id);
            } 
            else if (option_i == "0") {
                std::cout << "End of the program!" << std::endl;
                keep_cycle = false; 
            } 
            else {
                std::cout << "No suitable command - try it again!." << std::endl;
            }
        } 

        delete controller;
        delete con;

    } catch (sql::SQLException &e) {
        std::cout << "# ERR: SQL error!" << std::endl;
        std::cout << "# ERR: " << e.what() << std::endl;
        std::cout << " (MySQL error code: " << e.getErrorCode() << ")" << std::endl;
    }

    return 0;
}