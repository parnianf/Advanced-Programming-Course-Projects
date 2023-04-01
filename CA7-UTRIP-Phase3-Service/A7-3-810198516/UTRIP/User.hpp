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
    std::string getUsername();
    std::string getEmail() { return email; }
    bool doesExist(std::string email_,std::string password_);
    bool isEqual(std::string username,std::string email);
    void deleteFilters();
    void purchase(operation op,double amount_);
    void applyFilter(FilterType type,Arguments data);
    std::vector<Hotel*> getfilteredHotels(std::vector<Hotel*> hotels);
    struct Wallet getWallet() {return wallet; }
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