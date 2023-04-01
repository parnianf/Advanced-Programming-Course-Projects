#ifndef UTRIP_H
#define UTRIP_H "UTRIP_H"


#include"StructsAndDefines.hpp"
#include"Hotel.hpp"
#include"User.hpp"
#include"Reserve.hpp"
#include"Room.hpp"
#include"Functions.hpp"
#include"CVSReader.hpp"
#include"Sort.hpp"
#include<string>
#include<vector>


class Utrip{
public:

    Utrip(std::string hotelFilePath,std::string ratingFilePath);
    void applyFilter(FilterType filterType, Arguments data);
    void deleteFilters();
    bool isLoggedIn();
    void addUser(User* newUser);
    void setCurrentUser(std::string email,std::string password);
    void setCurrentUser(User* newUser);
    void logoutUser();
    bool isUnique(Arguments argument);
    bool isUserValid(std::string email,std::string password);
    void showHotelsInShort();
    void showHotelInfo(std::string uniqueId);
    void login(Arguments info);
    void reserve(std::string hotelId,RoomType roomType,int quantity,Duration duration);
    void purchase(operation op,double amount);
    void signup(Arguments information);
    void showBankStatement(int count);
    void showReservations();
    void turnDefPriceFilter(std::string active);
    void deleteReservation(Arguments arg);
    void addComment(std::string hotelId,std::string comment);
    void showComments(std::string hotelId);
    void showRating(Arguments arg);
    bool isRatingValid(Arguments arg);
    void addRating(Arguments arg);
    void updatePriceFilter();
    void sortHotels(Arguments args);  
    void setInitialFileData(std::vector<Hotel*> initialHotels , std::map<std::string,Rating> ratings);     
    void setManualWeights(Arguments arg);
    void showManualWeight();
    Rating estimateWeight(std::vector<Rating> rating);
    double getdi(Rating rating ,std::vector<double> weight, int i);
    double getError(Rating rating ,std::vector<double> weight, int i,double epsilon);
    void deactivateManualWeght();
    Rating getWeight();
    void showEstimatedWeight();

private:

    void showAbstractHotelInfo(std::vector<Hotel*> hotels_);
    Reserve* bookReservation(std::string hotelId,RoomType roomType,int quantity,Duration duration);
    bool canReserve(std::string hotelId,RoomType roomType,int quantity,Duration duration);
    Hotel* findHotelById(std::string id);

    std::vector<Hotel*> hotels;
    std::vector<User*> users;
    User* currentUser;
    bool didSortTheHotels;
    CVSReader cvsReader;
};




#endif