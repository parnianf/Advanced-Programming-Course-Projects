#ifndef RESERVE_H
#define RESERVE_H "RESERVE_H"

#include<string>
#include<vector>
#include<map>
#include"StructsAndDefines.hpp"
#include"Room.hpp"

typedef std::map<std::string,Rating> Ratings;
typedef std::vector<Room*> Rooms;


class Reserve{
public:

    Reserve(std::string hotelId_,Rooms rooms,RoomType roomType_,Duration duration_,double cost_);
    
private:

    int id,quantity;
    std::string hotelId,clientUsername;
    struct Duration duration;
    double cost;
    RoomType roomType;
    Rooms bookedRooms;
};

#endif
