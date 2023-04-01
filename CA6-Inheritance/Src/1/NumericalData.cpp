#include "NumericalData.hpp"

#include <iostream>
using namespace std;

NumericalData::NumericalData(string key_, int value_)
{
    key = key_;
    value = value_;
}
void NumericalData::print(int id)
{
    if (key != "")
    {
        cout << "\"" << key << "\""<< ": ";
    }
    cout << value;
}