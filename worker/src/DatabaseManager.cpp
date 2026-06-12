#include "../include/DatabaseManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>

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
                  "dialect TEXT,"
                  "studs_count INTEGER DEFAULT 0,"
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

bool DatabaseManager::addRecord(std::string name, std::string rank, std::string language, std::string dialect, int studs_count, int virtual_studs_count) {
    std::string sql = "INSERT INTO heroes (name, rank, language, dialect, studs_count, virtual_studs_count) VALUES (?, ?, ?, ?, ?, ?);";
    
    sqlite3_stmt* stmt; 

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error while executing the command: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, rank.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, language.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, dialect.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, studs_count);
    sqlite3_bind_int(stmt, 6, virtual_studs_count);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error while saving data: " << sqlite3_errmsg(db) << "\n";
    } else {
        std::cout << "May the force be with you! Heroe saved!.\n";
    }

    sqlite3_finalize(stmt);
    
    return true;
}

void DatabaseManager::displayRecords() {
    std::string sql = "SELECT * FROM heroes;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error while reading data: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    std::cout << "\n--- Heroes ---\n";

    std::cout << std::left 
        << std::setw(5)  << "ID"
        << std::setw(20) << "Name"
        << std::setw(15) << "Rank"
        << std::setw(15) << "Language"
        << std::setw(15) << "Dialect"
        << std::setw(10) << "Studs"
        << std::setw(10) << "Virtual"
        << "\n";
    std::cout << std::string(90, '-') << "\n";

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* rank   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* language = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const char* dialect  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        const char* studs_count = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        const char* virtual_studs_count = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

        std::cout << std::left
            << std::setw(5)  << id
            << std::setw(20) << (name ? name : "N/A")
            << std::setw(15) << (rank ? rank : "N/A")
            << std::setw(15) << (language ? language : "N/A")
            << std::setw(15) << (dialect ? dialect : "N/A")
            << std::setw(10) << (studs_count ? studs_count : "0")
            << std::setw(10) << (virtual_studs_count ? virtual_studs_count : "0")
            << "\n";
    }

    std::cout << std::string(90, '-') << "\n";
    sqlite3_finalize(stmt);
}