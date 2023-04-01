#include "StringData.hpp"

#include <iostream>
using namespace std;

StringData::StringData(string key_, string value_)
{
    key = key_;
    value = value_;
}
void StringData::print(int id)
{
    if (key != "")
    {
        cout << "\"" << key << "\""
             << ": ";
    }
    cout << "\"" << value << "\"";
}