/*****************************************************************************
 *
 *  Linux Pro Staff
 *
 *  NOMEFILE:
 *      Database.h
 *
 *  DESCRIZIONE:
 *      incapsula MySQL Connector/C++ (interfaccia).
 *
 *  COMPILATORE:
 *      g++ 9.1.1
 *
 *
 *****************************************************************************/
#ifndef DATABASE_H_ //********************************************************
#define DATABASE_H_ //********************************************************

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>  // gestisce sql::SQLException; used dai client

class Database
{
private:
    sql::Driver*     _pDriver;
    sql::Connection* _pConnection;
    sql::Statement*  _pStatement;
    sql::ResultSet*  _pRS;

public:
    Database(std::string sUser,      // constructor
             std::string sPassword,
             std::string sSchema  = "world",
             std::string sAddress = "tcp://127.0.0.1:3306") : _pRS(nullptr)
    {
        _pDriver = get_driver_instance();
        _pConnection = _pDriver->connect(sAddress, sUser, sPassword);
        _pConnection->setSchema(sSchema);
        _pStatement = _pConnection->createStatement();
    }
    ~Database()                     // destructor
    {
        if (_pRS != nullptr) delete _pRS;
        delete _pStatement;
        delete _pConnection;
    }
    sql::ResultSet* executeQuery(const std::string sStatement,
                                 bool bDisplay = true);
    long queryHasRecords(const std::string sQuery,   bool bDisplay = true);
    bool execute(const std::string sStatement,       bool bDisplay = true);
    long executeCountQuery(const std::string sQuery, bool bDisplay = true);
    void deleteResultSet();  // may reduce memory usage 
 };

#endif //*************************** DATABASE_H *****************************