/*****************************************************************************
 *
 *  Linux Pro Staff
 *
 *  NOMEFILE:
 *      Place.h
 *
 *  DESCRIZIONE:
 *      Classe oggetto per l'accesso a ResultSet. (interfaccia)
 *
 *  COMPILATORE:
 *      g++ 9.1.1
 *
 *
 *****************************************************************************/
#ifndef PLACE_  //************************************************************
#define PLACE_  //************************************************************

typedef sql::ResultSet* pRS;  		// qui ci basta la definizione

class Place
{
private:
    const std::string _sField1;
    const std::string _sField2;
    const std::string _sField3;
    const long        _nField4;

public:
    Place(std::string name,             // costruttore
          std::string capital, 
          std::string headOfState,
          long        population) : _sField1(name),
                                    _sField2(capital),
                                    _sField3(headOfState),
                                    _nField4(population)    {}
    ~Place() {}                         // distruttore
    void display();
    static long display(sql::ResultSet* pRS, bool bDisplayCount = true);
};

#endif //*************************** PLACE_H ********************************
