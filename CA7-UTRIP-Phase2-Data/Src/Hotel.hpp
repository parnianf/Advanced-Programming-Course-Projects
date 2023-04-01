#ifndef HOTEL_H
#define HOTEL_H "HOTEL_H"

#include<string>
#include<vector>
#include<map>
#include"Reserve.hpp"
#include"StructsAndDefines.hpp"
#include"Room.hpp"
#include"User.hpp"
typedef std::map<std::string,Rating> Ratings;

class User;

class Hotel{
public:

    Hotel(struct HotelInfo hotelInfo_,struct Place place_,Rooms rooms_,std::vector<RoomInfo> roomsInfo_);
    bool isCityTheSame(std::string city_);
    bool isStarTheSame(std::string star_);
    bool isPriceInRange(double minAvPrice,double maxAvPrice);
    bool haveRoom(RoomType type,Duration dur,int quantity);
    bool isEqual(std::string id);
    bool isFull(RoomType type,Duration dur,int quantity);
    void showComments();
    void addComment(Comment newComment);
    void showInShort();
    void setPreviousRatings(Rating rating);
    void showComplete();
    void addRating(Rating newRating,std::string username);
    void deleteReservation(std::string clientUsername,int resId);
    void showRating();
    double getAveragePrice();
    double getTotalCost(RoomType type,int quantity,Duration dur);
    double getRoomPrice(RoomType type);
    double getPersonalRating(std::string username,Rating weight);
    std::string getId();
    std::string getCity() {return place.city; }
    Reserve* bookRooms(std::string hotelId,RoomType roomType,int quantity,Duration duration);
    HotelInfo getHotelInfo(){return hotelInfo; }

private:

    Rooms getRoomsInType(RoomType type);
    Reserve* findReservation(std::string clientUsername,int resId);

    struct HotelInfo hotelInfo;
    struct Place place;
    std::vector<RoomInfo> roomsInfo;
    std::vector<Comment> comments;
    Ratings ratings;
    std::vector<Reserve*> reservations;
    Rooms rooms;
};

#endif
