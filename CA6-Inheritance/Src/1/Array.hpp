#ifndef ARRAY_H
#define ARRAY_H "ARRAY_H"


#include"Data.hpp"
#include<string>
#include<vector>
class Array : public Data{
public:


    Array(int id_,std::string name);
    void print(int id);
    int getId();
    void addData(Data* newData);

private:
    int id;
    std::vector<Data*> arrData;
};



#endif