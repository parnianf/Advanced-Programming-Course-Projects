#ifndef UTRIP_H
#define UTRIP_H "UTRIP_H"


#include"StructsAndDefines.hpp"
#include"Hotel.hpp"
#include"User.hpp"
#include"Functions.hpp"
#include"CVSReader.hpp"
#include"Sort.hpp"
#include<string>
#include<vector>
#include<map>


class Utrip{
public:

    Utrip(std::string hotelFilePath);
    std::vector<Hotel*> getAllHotels(){return hotels; }
    void applyFilter(FilterType filterType, Arguments data);
    void deleteFilters(std::string id);
    bool isLoggedIn();
    bool isEmailUnique(std::string email);
    bool isUsernameUnique(std::string email);
    std::vector<Hotel*> getStarFilteredHotels(std::string id);
    void setCurrentUser(std::string email,std::string password,std::string id);
    void logoutUser(std::string id);
    User* findUserById(std::string id);
    bool isUserValid(std::string email,std::string password);
    void login(Arguments info);
    void purchase(operation op,double amount,std::string id);
    void signup(Arguments information);
    void setInitialFileData(std::vector<Hotel*> initialHotels);     
    Hotel* findHotelById(std::string id);

private:

    std::vector<Hotel*> hotels;
    std::map<std::string,User*> loggedinUsers;
    std::vector<User*>users;
    CVSReader cvsReader;
};




#endif