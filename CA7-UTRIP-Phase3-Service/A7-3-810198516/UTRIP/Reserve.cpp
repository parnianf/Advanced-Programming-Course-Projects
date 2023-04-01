#include"Reserve.hpp"
#include"StructsAndDefines.hpp"
#include"Rating.hpp"
#include<string>
#include<vector>
#include<iostream>
#include<iomanip>
using namespace std;

typedef std::map<std::string,Rating> Ratings;
typedef vector<Room*> Rooms;


Reserve::Reserve(string hotelId_,Rooms rooms,RoomType roomType_,Duration duration_,double cost_){
    hotelId = hotelId_;
    roomType = roomType_;
    duration = duration_;
    bookedRooms = rooms;
    quantity = rooms.size();
    int days = duration.checkOut - duration.checkIn + 1;
    cost = quantity * cost_ * (double)days;
}