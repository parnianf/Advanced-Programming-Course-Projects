#include "Data.hpp"
#include <iostream>
using namespace std;

#define TAB "    "
void Data::printTab()
{
    for (int i = 0; i < tab; i++)
    {
        cout << TAB;
    }
}

string Data::getKey()
{
    return key;
}

int Data::tab = 0;
