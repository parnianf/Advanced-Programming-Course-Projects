#include "Array.hpp"

#include <iostream>
using namespace std;

Array::Array(int id_, string name)
{
    id = id_;
    key = name;
}
void Array::print(int id_)
{
    tab++;
    if (id_ != id)
    {
        cout << key;
    }
    cout << '[';
    if (arrData.size() != 0)
    {
        cout << endl;
    }
    for (int i = 0; i < arrData.size(); i++)
    {
        printTab();
        arrData[i]->print(id);
        if (i < arrData.size() - 1)
        {
            cout << ',' << endl;
        }
        else
        {
            cout << endl;
        }
    }
    tab--;
    if (arrData.size() != 0)
    {
        printTab();
    }
    cout << ']';
}
int Array::getId()
{
    return id;
}

void Array::addData(Data *newData)
{
    arrData.push_back(newData);
}