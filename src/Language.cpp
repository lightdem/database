/*****************************************************************************
 *
 *  Linux Pro Staff
 *
 *  NOMEFILE:
 *      Language.cpp
 *
 *  DESCRIZIONE:
 *      Classe oggetto per l'accesso a ResultSet. (implementazione)
 *
 *  COMPILATORE:
 *      g++ 9.1.1
 *
 *
 *****************************************************************************/

#include <cppconn/resultset.h>
#include "StrStrmBuf.h"
#include "Terminal.h"
#include "Language.h"

void Language::display()
{
    utility::StrStrmBuf ssb;
    ssb.rpad(_sField1, 30);
    long double ld = _nField2;
    string s = std::to_string(ld);
    if (ld == 100.0)
    {
        s = s.substr(0, 5);
    }
    else if (ld < 10.0)
    {
        s = s.substr(0, 3);
    }
    else
    {
        s = s.substr(0, 4);
    }
    ssb.lpad(s, 6);
    ssb << std::endl;
    Terminal::writeYellow(ssb);
}

long Language::display(sql::ResultSet *pRS, bool bDisplay)
{
    long nCount = 0;
    while (pRS->next())
    {
        Language* pLanguage = new Language(pRS->getString(1),
                                           pRS->getDouble(2));
        pLanguage->display();
        delete pLanguage;                           
        ++nCount;
    }

    if (bDisplay)
    {
        Terminal::displayCount(nCount);
    }
    return nCount;
}