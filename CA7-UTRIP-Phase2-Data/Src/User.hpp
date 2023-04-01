#ifndef USER_H
#define USER_H "USER_H"


#include<string>
#include<vector>
#include<map>
#include"Reserve.hpp"
#include"StructsAndDefines.hpp"
#include"Hotel.hpp"
#include"Filter.hpp"

class Hotel;
class Filter;

class User{
public:

    User(std::string username_,std::string password_,std::string email_);
    std::string getReservedHotelId(int resId);
    std::string getUsername();
    bool doesExist(std::string email_,std::string password_);
    bool hasFilter();
    bool hasEnoughMoney(double cost);
    bool isEqual(std::string username,std::string email);
    bool hasPriceFilter();
    bool canApplyDefPrice();
    bool hasDefaultPriceFilter();
    bool isManualWeightOn();
    bool doesHaveSufficientRating();
    void showReservationInfo();
    void deleteFilters();
    void purchase(operation op,double amount_);
    void showBankStatement(int count);
    void applyFilter(FilterType type,Arguments data);
    void addReservation(Reserve* reservedRooms);
    void deleteReservation(int resId);
    void applyDefaultPriceFilter();
    void turnOnorOffDefPriceFilter(bool active);
    void setManualWeight(Rating manualWeight);
    void showManualWeight();
    void addRating(std::string hotelName,Rating rating);
    void deactivateManualWeight();
    void showEstimatedWeight();
    double getDelta(Rating w,int i);
    double getStandardDeviation();
    double getAverageBookedRoomsPrices();
    std::vector<Hotel*> getfilteredHotels(std::vector<Hotel*> hotels);
    std::vector<double> getAllDelta(Rating weight);
    Reserve* findReservationById(int id);
    Rating getManualWeight();
    Ratings getRatings() { return ratings; }
    Rating estimateWeight();
    Rating getWeight();

private:

    std::string username;
    std::string password;
    std::string email;
    int reservationId;
    struct Wallet wallet;
    std::vector<Reserve*> reservations;
    std::map<FilterType,Filter*> filters;
    bool isPriceFilterOn;
    Ratings ratings; 
};

#endif