#include <iostream>
#include "../include/DatabaseManager.h"

int main() {
    DatabaseManager dm("language_galaxy.db");

    if(dm.createTable()) {
        std::cout << "The database was succesfully created!" << std::endl;
    } else {
        std::cerr << "Something went wrong while creating the database" << std::endl;
    }

    return 0;
}