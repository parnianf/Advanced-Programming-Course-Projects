#include"Hotel.hpp"
#include<string>
#include"Reserve.hpp"
#include"Room.hpp"
#include"User.hpp"
#include"StructsAndDefines.hpp"
#include<vector>
#include<iostream>
#include<iomanip>
#include<algorithm>

using namespace std;

Hotel::Hotel(struct HotelInfo hotelInfo_,struct Place place_,Rooms rooms_,vector<RoomInfo> roomsInfo_){
    hotelInfo = hotelInfo_;
    place = place_;
    rooms = rooms_;
    roomsInfo = roomsInfo_;
}

bool Hotel::isStarTheSame(string star_){
    return (hotelInfo.star == star_);
}


bool Hotel::isEqual(string id){
    return ( id == hotelInfo.uniqueId);
}

string Hotel::getId(){
    return hotelInfo.uniqueId;
}
