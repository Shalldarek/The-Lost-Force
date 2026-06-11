#include "../include/DatabaseManager.h"
#include <iostream>
#include <fstream>

DatabaseManager::DatabaseManager(const std::string& name) : name(name) {
    db = nullptr;

    int rc = sqlite3_open(name.c_str(), &db);
    
    if (rc != SQLITE_OK) {
        std::cerr << "Error while opening the database: " << sqlite3_errmsg(db) << "\n";
        db = nullptr; 
    } else {
        std::cout << "Database '" << name << "' was successfully opened.\n";
        if (!createTable()) {
            std::cerr << "Warning: Could not create table\n";
        }
    }
}

DatabaseManager::~DatabaseManager() {
    if(db) {
        sqlite3_close(db);
        std::cout << "The connection with database was closed" << std::endl;
    }
}

bool DatabaseManager::createTable() {
    std::string sql = "CREATE TABLE IF NOT EXISTS heroes("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "name TEXT NOT NULL, "
                  "rank TEXT NOT NULL, "
                  "language TEXT NOT NULL,"
                  "dialects TEXT,"
                  "stud_count INTEGER DEFAULT 0,"
                  "virtual_studs_count INTEGER DEFAULT 0);";

    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error while creating the table: " << errMsg << "\n";
        sqlite3_free(errMsg); 
        return false;
    }
    
    std::cout << "Table 'heroes' created successfully (or already exists)\n";
    return true;
}