/*****************************************************************************
 *
 *  Linux Pro Staff
 *
 *  NOMEFILE:
 *      Terminal.h
 *
 *  DESCRIZIONE:
 *      Alcune semplici operazioni di colorazione e modifica dei caratteri nel terminale
 *
 *  COMPILATORE:
 *      g++ 9.1.1
 *
 *
 *****************************************************************************/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "StrStrmBuf.h"
#include "Terminal.h"

void Terminal::waitForUserInput()
{
    struct termios  oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    cout << RED << "\n\n\nPremi un tasto per continuare..." << RESET;
    getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    clearScreen();
}

void Terminal::displayCount(const long nCount)
{
    cout << GREEN  << "===== Numero di record trovati: " 
         << YELLOW << utility::commaSeparate(nCount)
         << GREEN  << " =====\n"
         << RESET;
}

void Terminal::displayStatement(const string& s)
{
    cout << GREEN  << "===== " 
         << VIOLET << "Sto eseguendo: " 
         << YELLOW << s 
         << GREEN  << " =====\n"
         << RESET;
}
void Terminal::displayLabel(const string& sLabel, const string& sContent)
{
    cout << GREEN    << "\n===== " 
         << VIOLET   << sLabel << ": ";

    if (!sContent.empty())
    {
        cout << BLUE<< sContent;
    }

    cout << GREEN  << " =====\n"
         << RESET;
}

