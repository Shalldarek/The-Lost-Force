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
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        driver = sql::mysql::get_mysql_driver_instance();
        
        con = driver->connect("tcp://127.0.0.1:3306", "Venca Srubar", "kylo_ren2005");
        
        con->setSchema("language_galaxy");

        /*sql::PreparedStatement *pstmt;

        pstmt->executeUpdate();*/
        
        delete con;
        //delete pstmt;
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQL error!" << endl;
        cout << "# ERR: " << e.what() << endl;
        cout << " (MySQL error code: " << e.getErrorCode() << ")" << endl;
    }

    return 0;
}