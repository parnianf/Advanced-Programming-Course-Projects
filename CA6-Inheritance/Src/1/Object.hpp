#ifndef OBJECT_H
#define OBJECT_H "OBJECT_H"

#include"Data.hpp"
#include<string>
#include<vector>

class Object : public Data{
public:


    Object(int id_,std::string name);
    void print(int id_);
    void setKey(std::string title);
    void addData(Data* newData);
    std::vector<Data*> getData();
    int getId();
    std::string getKey(){
        return key;
    }
    bool isKeyDuplicate(std::string key_);

private:
    int id;
    std::vector<Data*> objData;
};

#endif
