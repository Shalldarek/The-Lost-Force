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
        bool addRecord(std::string name, std::string rank, std::string language, std::string dialect, int studs_count, int virtual_studs_count);
        void displayRecords();
};