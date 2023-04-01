#include "Object.hpp"

#include <iostream>
#include <sstream>
using namespace std;
#define DATA_SEPEARATOR ','

Object::Object(int id_, string name)
{
    id = id_;
    key = name;
}
void Object::print(int id_)
{
    tab++;
    if (id_ != id)
    {
        cout << key;
    }
    cout << '{';
    if (objData.size() != 0)
    {
        cout << endl;
    }
    for (int i = 0; i < objData.size(); i++)
    {
        printTab();
        objData[i]->print(id);
        if (i < objData.size() - 1)
        {
            cout << DATA_SEPEARATOR << endl;
        }
        else
        {
            cout << endl;
        }
    }
    tab--;
    if (objData.size() != 0)
    {
        printTab();
    }
    cout << '}';
}

bool Object::isKeyDuplicate(string key_)
{
    stringstream title;
    title << "\"" << key_ << "\""<< ": ";
    key_ = title.str();
    for (int i = 0; i < objData.size(); i++)
    {
        if (objData[i]->getKey() == key_)
        {
            return true;
        }
    }
    return false;
}

void Object::setKey(string title)
{
    key = title;
}
void Object::addData(Data *newData)
{
    objData.push_back(newData);
}
vector<Data *> Object::getData()
{
    return objData;
}

int Object::getId()
{
    return id;
}