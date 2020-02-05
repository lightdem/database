/*****************************************************************************
 *
 *  Linux Pro Staff
 *
 *  NOMEFILE:
 *      StrStrmBuf.h
 *
 *  DESCRIZIONE:
 *      Classe utility per la manipolazione delle stringhe simil-java. (implementazione)
 *
 *  COMPILATORE:
 *      g++ 9.1.1
 *
 *
 *****************************************************************************/
#include <locale>			// per formatDateTime()
#include <cstring>			// per strlen() in formatDateTime()
#include "StrStrmBuf.h"

namespace utility	{

using std::string;
using std::ostream;

/*****************************************************************************
 *
 *  class StrStrmBuf : public std::stringstream
 *
 *  	classe per la manipolazione delle stringhe simil-java
 *
 *  	l'operatore const char*() permette a questa classe di essere passata
 *  	a std::cout e std::cerr
 *
 *****************************************************************************/
/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::operator=(StrStrmBuf& rhs)
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::operator=(StrStrmBuf& rhs)
{
	if (&rhs != this)
	{
		str(rhs.str());
	}
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::putch(char ch, size_t nCount);
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::putch(char ch, size_t nCount)
{
	for (size_t i = 0; i < nCount; i++)
	{
		put(ch);
	}
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::putstr(const string& str)
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::putstr(const string& str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		put(str[i]);
	}
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf funzioni di tabulazione
 *
 *****************************************************************************/
size_t utf8_strlen(const string& s)	// grazie a www.zedwood.com per questa funzione
{
    size_t c = 0, i = 0, ix = s.length(), q;
    for (q = 0; i < ix; i++, q++)
    {
        c = static_cast<unsigned char>(s[i]);
        if      (c >= 0 && c <= 127)   i += 0;	// char singolo byte
        else if ((c & 0xE0) == 0xC0)   i += 1;  // char doppio byte
        else if ((c & 0xF0) == 0xE0)   i += 2;  // char triplo byte
        else if ((c & 0xF8) == 0xF0)   i += 3;  // char quadruplo byte
        else return 0;  //utf8 invalido
    }

    return q;
}

/*****************************************************************************/

StrStrmBuf& StrStrmBuf::lpad(const string& s, size_t nWidth, char ch)
{
	size_t nLen = utf8_strlen(s);
	if (nLen < nWidth)
	{
		putch(ch, nWidth - nLen);
		*this << s;
	}
	else
	{
		*this << s.substr(0, nWidth);
	}
	
	return *this;
}

StrStrmBuf& StrStrmBuf::rpad(const string& s, size_t nWidth, char ch)
{
	size_t nLen = utf8_strlen(s);
	if (nLen < nWidth)
	{
		*this << s;
		putch(ch, nWidth - nLen);
	}
	else
	{
		*this << s.substr(0, nWidth);
	}
	
	return *this;
}

StrStrmBuf& StrStrmBuf::center(const string& s, size_t nWidth, char ch)
{
	size_t nLen = utf8_strlen(s);
	size_t nRight = (nWidth - nLen) / 2;
	if (nLen < nWidth)
	{
		putch(ch, nWidth - nLen - nRight);
		*this << s;
		putch(ch, nRight);
	}
	else
	{
		*this << s.substr(0, nWidth);
	}
	
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::ltrim();
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::ltrim()
{
	str(utility::ltrim(str()));
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::rtrim();
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::rtrim()
{
	str(utility::rtrim(str()));
	return *this;
}

/*****************************************************************************
 *
 *  StrStrmBuf& StrStrmBuf::trim();
 *
 *****************************************************************************/
StrStrmBuf& StrStrmBuf::trim()
{
	str(utility::trim(str()));
	return *this;
}


/*****************************************************************************
 *
 * string toHHMMSS(long nTime)
 *
 * 		congerte un numerico di tipo long in ore, minuti e secondi (HH:MM:SS)
 *
 *****************************************************************************/
string toHHMMSS(long nTime)
{
	StrStrmBuf	ssb;
	long 		nTimeTmp = nTime / HOUR;	// recupera le ore

	if (nTimeTmp < TEN) ssb.put('0');		// scrive le ore
	ssb << nTimeTmp << ':';
	nTime %= HOUR;							// rimuove le ore

	nTimeTmp = nTime / SIXTY;				// recupera i minuti
	if (nTimeTmp < TEN) ssb.put('0');		// scrive i minuti
	ssb << nTimeTmp << ':';

	nTime %= SIXTY;							// recupera i secondi
	if (nTime < TEN) ssb.put('0');			// scrive i secondi
	ssb << nTime;
	return ssb.str();
}

/*****************************************************************************
 *
 * string commaSeparate(long n)
 *
 * 		aggiunge virgole a un long usando le potenze 10^3
 *
 *****************************************************************************/
string commaSeparate(long n)
{
	bool		bFoundFactor(false);
	StrStrmBuf	ssb;
	long		nTmp;

	nTmp = n / QUINTILLION;							// prende i quintilioni
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * QUINTILLION;					// rimuove i quintilioni
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// scrive i quintilioni
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// scrive i quintilioni
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}
	
	nTmp = n / QUADRILLION;							// prende i quadrilioni
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * QUADRILLION;					// rimuove i quadrilioni
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// scrive i quadrilioni
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// scrive i quadrilioni
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}
	
	nTmp = n / TRILLION;							// prende i trilioni
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * TRILLION;						// rimuove i trilioni
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// scrive i trilioni
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// scrive i trilioni
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}

	nTmp = n / BILLION;								// prende i bilioni
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * BILLION;						// rimuove i bilioni
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// scrive i bilioni
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// scrive i bilioni
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}

	nTmp = n / MILLION;								// prende i bilioni
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * MILLION;						// rimuove i bilioni
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// scruve i bilioni
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// scrive i bilioni
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}

	nTmp = n / THOUSAND;							// prende le migliaia
	if (nTmp || bFoundFactor)
	{
		n -= nTmp * THOUSAND;						// rimuove le migliaia
		if (!bFoundFactor)
		{
			ssb << nTmp << ',';						// scrive le migliaia
		}
		else
		{
			if (nTmp < HUNDRED) ssb.put('0');		// scrive le migliaia
			if (nTmp < TEN)  ssb.put('0');
			ssb << nTmp << ',';
		}
		bFoundFactor = true;
	}

	if (!bFoundFactor)
	{
		ssb << n;									// scrive le unità
	}
	else
	{
		if (n < HUNDRED) ssb.put('0');				// scrive le unità
		if (n < TEN)  ssb.put('0');
		ssb << n;
	}
	return ssb.str();
}

/*****************************************************************************
 *
 * runczioni per il trim delle string:
 *
 *****************************************************************************/
string ltrim(const string& s)
{
	if (s.empty()) return std::string();

	size_t nBegin = s.find_first_not_of(" \t\n", 0);
	// if we don't find whitespace, return empty string
	if (nBegin == string::npos) return string();

	return s.substr(nBegin);
}

string rtrim(const string& s)
{
	if (s.empty()) return string();

	size_t nEnd = s.find_last_not_of(" \t\n");
	// if we don't find whitespace, return empty string
	if (nEnd == string::npos) return string();

	return s.substr(0, nEnd + 1);
}

string trim(const string& s)
{
	if (s.empty()) return string();

	size_t nBegin = s.find_first_not_of(" \t\n", 0);
	// if we don't find whitespace, return empty string
	if (nBegin == string::npos) return string();

	size_t nEnd = s.find_last_not_of(" \t\n");
	return s.substr(nBegin, nEnd - nBegin + 1);
}

/*****************************************************************************
 *
 *	std::string formatDateTime(time_t* t = NULL,
 *				   			   const char* fmt = utility::SHORT_DATETIME_FMT);
 *
 *****************************************************************************/
string formatDateTime(time_t* t, const char* fmt)
{
	using namespace std;
	tm*		tminfo;
	StrStrmBuf	ssb;
	time_t 		rawtm = time(t);
	tminfo = localtime(&rawtm);
	const time_put<char>& dtwriter = use_facet<time_put<char> >(ssb.getloc());
	if (dtwriter.put(ssb, ssb, ' ', tminfo, fmt, fmt + strlen(fmt)).failed())
	{
		return "";
	}
	return ssb.str();
}

// ***************************************************************************
}	// fine del namespace utility
// ***************************************************************************
