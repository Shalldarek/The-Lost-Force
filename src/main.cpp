#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "../include/Sith.h"
using namespace std;

int main() {
    try {
        Sith* darth_vader = new Sith(1, "Darth Vader", "German", "Austrian German", 99);
        darth_vader->addStuds(3); 

        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();
        
        con = driver->connect("tcp://127.0.0.1:3306", "Venca Srubar", "kylo_ren2005");
        
        con->setSchema("language_galaxy");

        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("INSERT INTO characters (id, force_side, character_name, language, dialect, studs, anger_level) VALUES (?, ?, ?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE studs = ?, anger_level = ?");
        
        pstmt->setInt(1, 1); 
        pstmt->setString(2, "Sith"); 
        pstmt->setString(3, darth_vader->getCharacterName());
        pstmt->setString(4, darth_vader->getLanguage());
        pstmt->setString(5, darth_vader->getDialect());
        pstmt->setInt(6, darth_vader->getStuds());
        pstmt->setInt(7, darth_vader->getAngerLevel());
        
        pstmt->setInt(8, darth_vader->getStuds());
        pstmt->setInt(9, darth_vader->getAngerLevel());

        pstmt->executeUpdate();
        
        cout << "May the force be with you! " << darth_vader->getCharacterName() << " was succesfully added into the database with " << darth_vader->getStuds() << " studs." << endl;

        delete pstmt;
        delete con;
        delete darth_vader;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQL error!" << endl;
        cout << "# ERR: " << e.what() << endl;
        cout << " (MySQL error code: " << e.getErrorCode() << ")" << endl;
    }

    return 0;
}