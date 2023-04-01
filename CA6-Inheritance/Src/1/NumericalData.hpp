#ifndef NUMERICALDATA_H
#define NUMERICALDATA_H "NUMERICALDATA_H"

#include "Data.hpp"
#include <string>

class NumericalData : public Data
{

public:
    NumericalData(std::string key_, int value_);
    void print(int id);

private:
    int value;
};
#endif