#ifndef DATA_H
#define DATA_H "DATA_H"

#include <string>

class Data
{
public:
    virtual void print(int id) = 0;
    std::string getKey();

protected:
    void printTab();
    std::string key;
    static int tab;
};

#endif