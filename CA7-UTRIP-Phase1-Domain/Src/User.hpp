#ifndef USER_H
#define USER_H "USER_H"


#include<string>
#include<vector>
#include<map>
#include"Reserve.hpp"
#include"StructsAndDefines.hpp"
#include"Hotel.hpp"
#include"Filter.hpp"

class User{
public:
    User(std::string username_,std::string password_,std::string email_);
    std::string getReservedHotelId(int resId);
    std::string getUsername();
    bool doesExist(std::string email_,std::string password_);
    bool hasFilter();
    void showReservationInfo();
    void deleteFilters();
    bool hasEnoughMoney(double cost);
    bool isEqual(std::string username,std::string email);
    void purchase(operation op,double amount_);
    void showBankStatement(int count);
    void applyFilter(FilterType type,Arguments data);
    std::vector<Hotel*> getfilteredHotels(std::vector<Hotel*> hotels);
    void addReservation(Reserve* reservedRooms);
    void deleteReservation(int resId);
    Reserve* findReservationById(int id);

private:

    std::string username;
    std::string password;
    std::string email;
    int reservationId;
    struct Wallet wallet;
    std::vector<Reserve*> reservations;
    std::map<FilterType,Filter*> filters;
};

#endif