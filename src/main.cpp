#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "../include/Sith.h"
#include "../include/Jedi.h"
#include "Controller.h"
using namespace std;

int main(int argc, char* argv[]) {
    Controller* controller = new Controller();

    try {
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "Venca Srubar", "kylo_ren2005");
        con->setSchema("language_galaxy");

        if (argc > 1) {
            std::string action = argv[1];

            if (action == "print_all") {
                controller->printAllCharacters(con);
            } else if (action == "print_one") {
                if (argc > 2) { 
                    int id = std::stoi(argv[2]); 
                    controller->printCharacter(con, id);
                }
            } else if (action == "remove_one") {
                if (argc > 2) { 
                    int id = std::stoi(argv[2]); 
                    controller->removeCharacter(con, id);
                }
            } else if (action == "remove_all") { 
                controller->removeAllCharacters(con);
            } else if (action == "update") {
                if (argc >= 7) { 
                    int id = std::stoi(argv[2]);
                    std::string name = argv[3];
                    std::string side = argv[4];
                    std::string language = argv[5];
                    std::string dialect = argv[6];
                    controller->updateCharacter(con, id, name, side, language, dialect);
                } else {
                    std::cout << "ERROR: Wrong amount of arguments!" << std::endl;
                }
            } else if (action == "add") {
                if (argc >= 6) { 
                    int id = std::stoi(argv[2]);
                    std::string name = argv[3];
                    std::string side = argv[4];
                    std::string language = argv[5];
                    controller->addCharacter(con, id, name, side, language);
                } else {
                    std::cout << "ERROR: Wrong amount of arguments!" << std::endl;
                }
            } else if (action == "update_rank") {
                if (argc >= 3) { 
                    int id = std::stoi(argv[2]);
                    controller->updateCharacterRank(con, id);
                } else {
                    std::cout << "ERROR: Wrong amount of arguments!" << std::endl;
                }
            }
            
        } else {
            cout << "No suitable command for controller." << endl;
        }

        delete controller;
        delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQL error!" << endl;
        cout << "# ERR: " << e.what() << endl;
        cout << " (MySQL error code: " << e.getErrorCode() << ")" << endl;
    }

    return 0;
}