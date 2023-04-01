#ifndef STRUCTS_H
#define STRUCTS_H "STRUCTS_H"

#include"Rating.hpp"
#include<string>
#include<vector>
#include<map>


enum RoomType { Standard = 0,Deluxe = 1, Luxury = 2, Premium = 3};
enum FilterType{ CityF , StarF , PriceF , RoomF ,DefaultPriceF };
enum Order{ AscendingOrd , DescendingOrd};

typedef double (*operation)(double,double);
typedef std::string (*sortComparator)(void);
typedef std::map<std::string,std::string> Arguments;


#define SUCCESSFUL "OK"
#define GET "GET"
#define POST "POST"
#define DELETE "DELETE"
#define FILTERS "filters"
#define PASSWORD "password"
#define EMAIL "email"
#define ID "id"
#define LOGIN "login"
#define SIGNUP "signup"
#define LOGOUT "logout"
#define WALLET "wallet"
#define RESERVES "reserves"
#define COMMENTS "comments"
#define RATINGS "ratings"
#define AMOUNT "amount"
#define USERNAME "username"
#define HOTELS "hotels"
#define HOTEL "hotel"
#define COUNT "count"
#define TYPE "type"
#define ORDER_ARGUMENTS_SEPERATOR '?'
#define ARGUMENTS_SEPERATOR ' '
#define QUANTITY "quantity"
#define COMMENT "comment"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define MIN_PRICE "min_price"
#define MAX_PRICE "max_price"
#define MIN_STAR "min_star"
#define MAX_STAR "max_star"
#define CITY "city"
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define OVERALL_RATING "overall_rating"
#define STANDARD_ROOM_ID 's'
#define DELUXE_ROOM_ID 'd'
#define LUXURY_ROOM_ID 'l'
#define PREMIUM_ROOM_ID 'p'
#define RATING_RANGE_FROM 1
#define RATING_RANGE_TO 5
#define STANDARD_ROOM "standard"
#define DELUXE_ROOM "deluxe"
#define LUXURY_ROOM "luxury"
#define PREMIUM_ROOM "premium"
#define SHOW_STAR "star: "
#define SHOW_OVERVIEW "overview: "
#define SHOW_AMENITIES "amenities: "
#define SHOW_CITY "city: "
#define SHOW_LATITUDE "latitude: "
#define SHOW_LONGITUDE "longitude: "
#define SHOW_ROOMS "#rooms: "
#define SHOW_PRICE "price: "
#define NO_RATING "No Rating"
#define SHOW_LOCATION "location: "
#define SHOW_CLEANLINESS "cleanliness: "
#define SHOW_STAFF "staff: "
#define SHOW_FACILITIES "facilities: "
#define SHOW_VALUE_FOR_MONEY "value_for_money: "
#define SHOW_OVERAL_RATING "overall_rating: "
#define ROOM "room"
#define COST "cost"
#define EMPTY "Empty"
#define ORDER "order"
#define PROPERTY "property"
#define ASCENDING "ascending"
#define TRUE_ "true"
#define FALSE_ "false"
#define DEFAULT_PRICE_FILTER_MESSAGE "* Results have been filtered by the default price filter."
#define ACTIVE "active"
#define STAR_RATING "star_rating"
#define NAME "name"
#define AVERAGE_ROOM_PRICE "average_room_price"
#define STANDARD_ROOM_PRICE "standard_room_price"
#define DELUXE_ROOM_PRICE "deluxe_room_price"
#define LUXURY_ROOM_PRICE "luxury_room_price"
#define PREMIUM_ROOM_PRICE "premium_room_price"
#define RATING_PERSONAL "rating_personal"
#define BAD_REQUEST_ERROR "Bad Request\n"
#define NOT_FOUND_ERROR "Not Found\n"
#define PERMISSION_DENIED_ERROR "Permission Denied\n"
#define NOT_ENOUGH_ROOM_ERROR "Not Enough Room\n"
#define NOT_ENOUGH_CREDIT_ERROR "Not Enough Credit\n"
#define INSUFFICIENT_RATING_ERROR "Insufficient Rating\n"
#define DEFAULT_PRICE_FILTER "default_price_filter"
#define SORT "sort"
#define MANUAL_WEIGHT "manual_weights"
#define ESTIMATED_WEIGHT "estimated_weights"

struct Wallet{
    double amount;
    std::vector<double> bankStatement;
};

struct Place{
    std::string city;
    std::string latitude;
    std::string longitude;
};

struct Comment{
    std::string name;
    std::string comment;
};
struct Duration{
    int checkIn;
    int checkOut;
    bool operator==(const Duration& dur);
};



struct HotelInfo{
    std::string uniqueId;
    std::string name;
    std::string star;
    std::string overview;
    std::string amenities;
    std::string imageUrl;
};


struct RoomInfo{

    RoomType type;
    int quantity;
    double price;

};



// struct Rating{
//     Rating();
//     Rating(double location_,double cleanliness_,double staff_,double facilities_,double valueForMoney_,double overallRating_);
//     Rating operator*(const Rating& rating);
//     double location;
//     double cleanliness;
//     double staff;
//     double facilities;
//     double valueForMoney;
//     double overallRating;
// };


#endif