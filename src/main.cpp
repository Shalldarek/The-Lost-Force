#include <iostream>
#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "../include/Sith.h"
#include "../include/Jedi.h"
using namespace std;

int main() {
    try {
        Sith* darth_vader = new Sith(1, "Darth Vader", "German", "Austrian German", 99);
        Sith* kylo_ren = new Sith(2, "Kylo Ren", "Spanish", "Colombian / Mexican", 65);
        darth_vader->addStuds(3); 
        kylo_ren->addStuds(4);

        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();
        
        con = driver->connect("tcp://127.0.0.1:3306", "Venca Srubar", "kylo_ren2005");
        
        con->setSchema("language_galaxy");

        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("INSERT INTO characters (id, force_side, character_name, language, dialect, studs, anger_level) VALUES (?, ?, ?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE studs = ?, anger_level = ?");
        
        pstmt->setInt(1, 2); 
        pstmt->setString(2, "Sith"); 
        pstmt->setString(3, kylo_ren->getCharacterName());
        pstmt->setString(4, kylo_ren->getLanguage());
        pstmt->setString(5, kylo_ren->getDialect());
        pstmt->setInt(6, kylo_ren->getStuds());
        pstmt->setInt(7, kylo_ren->getAngerLevel());   
        pstmt->setInt(8, kylo_ren->getStuds());
        pstmt->setInt(9, kylo_ren->getAngerLevel());

        pstmt->executeUpdate();
        
        cout << "May the force be with you! " << kylo_ren->getCharacterName() << " was succesfully added into the database with " << kylo_ren->getStuds() << " studs." << endl;

        delete pstmt;
        delete con;
        delete darth_vader;
        delete kylo_ren;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQL error!" << endl;
        cout << "# ERR: " << e.what() << endl;
        cout << " (MySQL error code: " << e.getErrorCode() << ")" << endl;
    }

    return 0;
}