#ifndef HOTEL_H
#define HOTEL_H "HOTEL_H"

#include<string>
#include<vector>
#include<map>
#include"Reserve.hpp"
#include"StructsAndDefines.hpp"
#include"Room.hpp"
typedef std::map<std::string,RatingCritera> Ratings;


class Hotel{
public:

    Hotel(struct HotelInfo hotelInfo_,struct Place place_,Rooms rooms_,std::vector<RoomInfo> roomsInfo_);
    bool isCityTheSame(std::string city_);
    bool isStarTheSame(std::string star_);
    bool isPriceInRange(double minAvPrice,double maxAvPrice);
    bool haveRoom(RoomType type,Duration dur,int quantity);
    void showComments();
    void addComment(Comment newComment);
    bool isEqual(std::string id);
    bool isFull(RoomType type,Duration dur,int quantity);
    std::string getId();
    void showInShort();
    void showComplete();
    double getTotalCost(RoomType type,int quantity,Duration dur);
    Reserve* bookRooms(std::string hotelId,RoomType roomType,int quantity,Duration duration);
    void deleteReservation(std::string clientUsername,int resId);
    void addRating(RatingCritera newRating,std::string username);
    void showRating();
    RatingCritera getAverageRating();

private:

    double getRoomPrice(RoomType type);
    Rooms getRoomsInType(RoomType type);
    Reserve* findReservation(std::string clientUsername,int resId);
    double getAveragePrice();

    struct HotelInfo hotelInfo;
    struct Place place;
    std::vector<RoomInfo> roomsInfo;
    std::vector<Comment> comments;
    Ratings ratings;
    std::vector<Reserve*> reservations;
    Rooms rooms;
};

#endif
