#pragma onca
#include <iostream>
#include <sqlite3.h>
#include <string>

class DatabaseManager {
    private:
        sqlite3* db;
        std::string name;
    public:
        DatabaseManager(const std::string& name);
        ~DatabaseManager();

        bool createTable();
};