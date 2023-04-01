#ifndef SORT_H
#define SORT_H "SORT_H"


#include<vector>
#include<string>
#include"Hotel.hpp"
#include"User.hpp"
#include"StructsAndDefines.hpp"
class Sort{
public:

    std::vector<Hotel*> sortInOrder(std::vector<Hotel*> hotels,std::string property,std::string order,User* user,bool& didSortTheHotels);

private:

    std::vector<Hotel*> sortByName(std::vector<Hotel*> hotels , Order order); 
    std::vector<Hotel*> sortByStar(std::vector<Hotel*> hotels , Order order); 
    std::vector<Hotel*> sortById(std::vector<Hotel*> hotels , Order order);
    std::vector<Hotel*> sortByCity(std::vector<Hotel*> hotels , Order order);
    std::vector<Hotel*> sortByAveragePrice(std::vector<Hotel*> hotels , Order order);
    std::vector<Hotel*> sortByRoomTypePrice(std::vector<Hotel*> hotels , Order order,RoomType roomType);
    std::vector<Hotel*> sortByPersonalRating(std::vector<Hotel*> hotels , Order order,User* user,bool& didSortTheHotels);

};


#endif