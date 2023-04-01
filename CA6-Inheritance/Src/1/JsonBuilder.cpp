#include "JsonBuilder.hpp"
#include <sstream>
#include <iostream>

using namespace std;

#define OBJECT "object"
#define ARRAY "array"

JsonBuilder::JsonBuilder()
{
    Object *firstObject = new Object(0, "parent");
    objects.push_back(firstObject);
}

void JsonBuilder::addStringToObject(int parentId, string key, std::string value)
{
    if (!findObjById(parentId))
    {
        throw InvalidId();
    }
    Object *object = findObjById(parentId);
    if (object->isKeyDuplicate(key))
    {
        throw DuplicateKey();
    }
    StringData *stringData = new StringData(key, value);
    object->addData(stringData);
}

void JsonBuilder::addIntegerToObject(int parentId, string key, int value)
{
    if (!findObjById(parentId))
    {
        throw InvalidId();
    }
    Object *object = findObjById(parentId);
    if (object->isKeyDuplicate(key))
    {
        throw DuplicateKey();
    }
    NumericalData *numericalData = new NumericalData(key, value);
    object->addData(numericalData);
}

int JsonBuilder::addContainerToObject(int parentId, string key, string type)
{
    if (!findObjById(parentId))
    {
        cout << "kk" << endl;
        throw InvalidId();
    }
    stringstream name;
    int newId = getNewId();
    name << "\"" << key << "\""
         << ": ";
    Object *parentObj = findObjById(parentId);
    if (parentObj->isKeyDuplicate(key))
    {
        throw DuplicateKey();
    }
    if (type == OBJECT)
    {

        Object *newObj = new Object(newId, name.str());
        parentObj->addData(newObj);
        objects.push_back(newObj);
        return newId;
    }
    else if (type == ARRAY)
    {
        Array *newArr = new Array(newId, name.str());
        parentObj->addData(newArr);
        arrays.push_back(newArr);
        return newId;
    }
    else
    {
        throw UndefinedType();
    }
}

void JsonBuilder::addStringToArray(int parentId, string value)
{
    if (!(findArrById(parentId)))
    {
        throw InvalidId();
    }
    Array *parentArray = findArrById(parentId);
    StringData *stringDataArr = new StringData("", value);
    parentArray->addData(stringDataArr);
}

void JsonBuilder::addIntegerToArray(int parentId, int value)
{
    if (!(findArrById(parentId)))
    {
        throw InvalidId();
    }
    Array *parentArray = findArrById(parentId);
    NumericalData *numericalDataArr = new NumericalData("", value);
    parentArray->addData(numericalDataArr);
}

int JsonBuilder::addContainerToArray(int parentId, string type)
{
    if (!(findArrById(parentId)))
    {
        throw InvalidId();
    }
    int newId = getNewId();
    if (type == OBJECT)
    {
        Array *parentArray = findArrById(parentId);
        Object *newObj = new Object(newId, "");
        parentArray->addData(newObj);
        objects.push_back(newObj);
    }
    if (type == ARRAY)
    {
        Array *parentArray = findArrById(parentId);
        Array *newArr = new Array(newId, "");
        parentArray->addData(newArr);
        arrays.push_back(newArr);
    }
    return newId;
}

void JsonBuilder::print(int id)
{
    if (!((findArrById(id)) || (findObjById(id))))
    {
        throw InvalidId();
    }
    Object *object = findObjById(id);
    string key;
    if (object != NULL)
    {
        object->print(id);
        cout << endl;
        return;
    }
    Array *array = findArrById(id);
    if (array != NULL)
    {
        array->print(id);
        cout << endl;
        return;
    }
}

Object *JsonBuilder::findObjById(int id)
{
    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i]->getId() == id)
        {
            return objects[i];
        }
    }
    return NULL;
}
Array *JsonBuilder::findArrById(int id)
{
    for (int i = 0; i < arrays.size(); i++)
    {
        if (arrays[i]->getId() == id)
        {
            return arrays[i];
        }
    }
    return NULL;
}
int JsonBuilder::getNewId()
{
    static int id = 0;
    id++;
    return id;
}