/*****************************************************************************
 *
 *  Linux Pro Staff
 *
 *  NOMEFILE:
 *      Database.cpp
 *
 *  DESCRIZIONE:
 *      incapsula MySQL Connector/C++ (implementazione).
 *
 *  COMPILATORE:
 *      g++ 9.1.1
 *
 *
 *****************************************************************************/

#include "Terminal.h"
#include "Database.h"

using namespace std;

bool Database::execute(const string sStatement, bool bDisplay)
{
    if (bDisplay)
    {
        Terminal::displayStatement(sStatement);
    }
    
    return _pStatement->execute(sStatement);
}

sql::ResultSet* Database::executeQuery(const std::string sQuery,
                                       bool bDisplay)
{
        if (_pRS != nullptr)
        {
            delete _pRS;
            _pRS = nullptr;
        }

        _pRS = _pStatement->executeQuery(sQuery);

        if (bDisplay)
        {
            Terminal::displayStatement(sQuery);
        }

        return _pRS;
}

long Database::queryHasRecords(const string sQuery, bool bDisplay)
{
    if (bDisplay)
    {
        Terminal::displayStatement(sQuery);
    }

    sql::ResultSet* pRS = _pStatement->executeQuery(sQuery);
    long nCount         = 0;

    while (pRS->next())
    {
        ++nCount;
    }
    delete pRS;

    if (bDisplay)
    {
        Terminal::displayCount(nCount);
    }

    return nCount;
}

long Database::executeCountQuery(const string sQuery, bool bDisplay)
{
    if (bDisplay)
    {
        Terminal::displayStatement(sQuery);
    }

    sql::ResultSet* pRS = _pStatement->executeQuery(sQuery);
    pRS->next();                        // ci muoviamo in ResultSet
    long nCount = pRS->getUInt64(1);    // recuperiamo il primo e unico record 
    delete pRS;
    
    if (bDisplay)
    {
        Terminal::displayCount(nCount);
    }

    return nCount;
}

void Database::deleteResultSet()  // riduce il consumo di memoria
{ 
    if (_pRS != nullptr) 
    {
        delete _pRS;
        _pRS = nullptr;
    }
}

//***************************************************************************
