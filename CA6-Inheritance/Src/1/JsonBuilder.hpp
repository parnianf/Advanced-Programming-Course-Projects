#ifndef JSONBUILDER_H
#define JSONBUILDER_H "JSONBUILDER_H"


#include <string>
#include <vector>
#include "Data.hpp"
#include "StringData.hpp"
#include "NumericalData.hpp"
#include "Object.hpp"
#include "Array.hpp"
#include "InvalidId.hpp"
#include "DuplicateKey.hpp"
#include "UndefinedType.hpp"

class JsonBuilder{
public:

    JsonBuilder();
    void addStringToObject(int parentId,std::string key, std::string value);
    void addIntegerToObject(int parentId, std::string key, int value);
    int addContainerToObject(int parentId, std::string key, std::string type);    
    void addStringToArray(int parentId, std::string value);
    void addIntegerToArray(int parentId, int value);
    int addContainerToArray(int parentId, std::string type);
    void print(int id);

private:

    Object* findObjById(int id);
    Array* findArrById(int id);
    int getNewId();

    std::vector<Object*> objects;
    std::vector<Array*> arrays;
};


#endif