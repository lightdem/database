/*****************************************************************************
 *
 *  Linux Pro Staff
 *
 *  NOMEFILE:
 *      Language.h
 *
 *  DESCRIZIONE:
 *      Classe oggetto per l'accesso a ResultSet. (interfaccia)
 *
 *  COMPILATORE:
 *      g++ 9.1.1
 *
 *
 *****************************************************************************/
#ifndef LANGUAGE_H  //********************************************************
#define LANGUAGE_H  //********************************************************

typedef sql::ResultSet* pRS;    // qui ci basta la definizione

class Language
{
private:
    const std::string   _sField1;
    const long double   _nField2;

public:
    Language(std::string country,           // costruttore
             long double percent) : _sField1(country),
                                    _nField2(percent)    {}
    ~Language() {}                         // distruttore
    void display();
    static long display(sql::ResultSet* pRS, bool bDisplayCount = true);
};

#endif //************************* LANGUAGE_H *******************************
