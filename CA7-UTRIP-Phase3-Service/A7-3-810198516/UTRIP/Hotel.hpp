#ifndef HOTEL_H
#define HOTEL_H "HOTEL_H"

#include<string>
#include<vector>
#include<map>
#include"StructsAndDefines.hpp"
#include"Room.hpp"
#include"User.hpp"
typedef std::map<std::string,Rating> Ratings;

class User;

class Hotel{
public:

    Hotel(struct HotelInfo hotelInfo_,struct Place place_,Rooms rooms_,std::vector<RoomInfo> roomsInfo_);
    bool isStarTheSame(std::string star_);
    bool isEqual(std::string id);
    std::string getId();
    std::string getCity() {return place.city; }
    HotelInfo getHotelInfo(){return hotelInfo; }
    std::vector<RoomInfo> getRoomsInfo() {return roomsInfo; }

private:

    Rooms getRoomsInType(RoomType type);

    struct HotelInfo hotelInfo;
    struct Place place;
    std::vector<RoomInfo> roomsInfo;
    std::vector<Comment> comments;
    Ratings ratings;
    Rooms rooms;
};

#endif
