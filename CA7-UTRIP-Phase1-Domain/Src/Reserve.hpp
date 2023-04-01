#ifndef RESERVE_H
#define RESERVE_H "RESERVE_H"

#include<string>
#include<vector>
#include<map>
#include"StructsAndDefines.hpp"
#include"Room.hpp"

typedef std::map<std::string,RatingCritera> Ratings;
typedef std::vector<Room*> Rooms;


class Reserve{
public:

    Reserve(std::string hotelId_,Rooms rooms,RoomType roomType_,Duration duration_,double cost_);
    void setId(int id_);
    int getId();
    double getCost();
    bool isEqual(std::string username,int id_);
    void showInfo();
    void showRoomsId();
    std::string getHotelId();
    RoomType getType();
    void setClientUsername(std::string username);
    void deleteRoomsReservation();


private:
    std::string getType(RoomType type);
    int id,quantity;
    std::string hotelId,clientUsername;
    struct Duration duration;
    double cost;
    RoomType roomType;
    Rooms bookedRooms;
};

#endif
