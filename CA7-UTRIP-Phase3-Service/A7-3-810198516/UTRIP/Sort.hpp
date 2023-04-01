#ifndef SORT_H
#define SORT_H "SORT_H"


#include<vector>
#include<string>
#include"Hotel.hpp"
#include"User.hpp"
#include"StructsAndDefines.hpp"

class Sort{
public:

    std::vector<Hotel*> sortInOrder(std::vector<Hotel*> hotels,std::string property,std::string order);

private:

    std::vector<Hotel*> sortById(std::vector<Hotel*> hotels , Order order);

};


#endif