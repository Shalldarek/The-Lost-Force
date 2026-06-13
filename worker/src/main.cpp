#include <iostream>
#include "../include/DatabaseManager.h"
#include <limits>

int main() {
    DatabaseManager dm("language_galaxy.db");

    if(dm.createTable()) {
        std::cout << "The database was succesfully created!" << std::endl;
        dm.createTriggers();
    } else {
        std::cerr << "Something went wrong while creating the database" << std::endl;
    }

    bool run = true;

    while (run) {
        std::cout << "\n=== LANGUAGE GALAXY ===\n";
        std::cout << "1. Add a new hero\n";
        std::cout << "2. Display heroes\n";
        std::cout << "3. Delete hero\n";
        std::cout << "4. Add studs\n";
        std::cout << "5. End app\n";
        std::cout << "Choose an option: ";

        int option;

        if (!(std::cin >> option)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "[ERROR]: Enter a valid option!\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (option) {

            case 1: {
                std::string image;
                std::string name;
                std::string rank;
                std::string language;
                std::string dialect;
                int studs_count;
                int virtual_studs_count;

                std::cout << "Enter character's image path: ";
                std::getline(std::cin, image);

                std::cout << "Enter character's name: ";
                std::getline(std::cin, name);

                std::cout << "Enter character's rank: ";
                std::getline(std::cin, rank);

                std::cout << "Enter represented language: ";
                std::getline(std::cin, language);

                std::cout << "Enter represented dialects: ";
                std::getline(std::cin, dialect);

                std::cout << "Enter studs count (1 stud = A1, 4 studs = B2...): ";
                std::cin >> studs_count;

                std::cout << "Enter virtual studs count: ";
                std::cin >> virtual_studs_count;

                dm.addRecord(image, name, rank, language, dialect, studs_count, virtual_studs_count);

                break;
            }

            case 2:
                dm.displayRecords();
                break;
            case 3:
                int id;
                std::cout << "Enter character's ID who you wanna delete: ";
                std::cin >> id; 
                dm.removeRecord(id);
                break;
            case 4:
                int character_id, studs;
                std::cout << "Enter character's ID: ";
                std::cin >> character_id;
                std::cout << "Enter the amount of studs: ";
                std::cin >> studs;
                dm.addStuds(character_id, studs);
                break;
            case 5:
                run = false;
                std::cout << "May the force be with you!" << std::endl;
                break;
        }
    }

    return 0;
}