#ifndef STRINGDATA_H
#define STRINGDATA_H "STRINGDATA_H"

#include <string>
#include "Data.hpp"

class StringData : public Data
{
public:
    StringData(std::string key_, std::string value_);
    void print(int id);

private:
    std::string value;
};

#endif