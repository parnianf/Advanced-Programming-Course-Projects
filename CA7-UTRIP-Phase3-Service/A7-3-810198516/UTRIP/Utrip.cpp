#include "Utrip.hpp"
#include"User.hpp"
#include"StructsAndDefines.hpp"
#include"Filter.hpp"
#include"Functions.hpp"
#include<iostream>
#include<algorithm>
#include<sstream>
#include<numeric>
#include<iomanip>
using namespace std;


Utrip::Utrip(string hotelFilePath){
    setInitialFileData(cvsReader.readHotelData(hotelFilePath));
}

vector<Hotel*> Utrip::getStarFilteredHotels(string id){
    return findUserById(id)->getfilteredHotels(hotels);
}

void Utrip::applyFilter(FilterType filterType, Arguments data){
    findUserById(data[ID])->applyFilter(filterType,data);
}

void Utrip::deleteFilters(string id){
    if(findUserById(id)){
        findUserById(id)->deleteFilters();
        cout<<SUCCESSFUL<<endl;
    }
}

bool Utrip::isLoggedIn(){
    if(loggedinUsers.size() != 0)
        return true;
    return false;
}
void Utrip::setInitialFileData(vector<Hotel*> initialHotels ){
    hotels = initialHotels;
}

bool Utrip::isEmailUnique(std::string email){
    for(int i=0 ; i < users.size() ; i++){
        if(users[i]->getEmail() == email){
            return false;
        }
    }
    return true;
}

bool Utrip::isUsernameUnique(string username){
    for(int i=0 ; i < users.size() ; i++){
        if(users[i]->getUsername() == username){
            return false;
        }
    }
    return true;
}

void Utrip::setCurrentUser(string email,string password,string id){
    for(int i=0 ; i < users.size() ; i++){
        if(users[i]->doesExist(email,password)){
            loggedinUsers[id] = users[i];
            cout<<SUCCESSFUL<<endl;
            return;
        }
    }
}

void Utrip::logoutUser(string id){
    deleteFilters(id);
    loggedinUsers.erase(id);
    for(auto it : loggedinUsers){
        cout<<it.first<<endl;
    }
}

User* Utrip::findUserById(string id){
    for(auto user : loggedinUsers){
        if(user.first == id){
            return user.second;
        }
    }
    return NULL;
}

bool Utrip::isUserValid(string email,string password){
    unsigned long int hashedPassword = hash<string>()(password);
    for(int i=0;i<users.size();i++){
        if(users[i]->doesExist(email,to_string(hashedPassword))){
            return true;
        }
    }
    return false;
}

void Utrip::login(Arguments info){
    unsigned long int hashedPassword = hash<string>()(info[PASSWORD]);
    Sort sortHotels;
    setCurrentUser(info[EMAIL],to_string(hashedPassword),info[ID]);
    for(auto it : loggedinUsers){
        cout<<it.first<<endl;
    }
    hotels = sortHotels.sortInOrder(hotels,ID,ASCENDING);
    return;
}

void Utrip::purchase(operation op,double amount,string id){
    findUserById(id)->purchase(op,amount);
    cout<<SUCCESSFUL<<endl;
}

void Utrip::signup(Arguments information){
    Sort sortHotels;
    unsigned long int hashedPassword = hash<string>()(information[PASSWORD]);
    User* newUser = new User(information[USERNAME],to_string(hashedPassword),information[EMAIL]);
    hotels = sortHotels.sortInOrder(hotels,ID,ASCENDING);
    users.push_back(newUser);
}

Hotel* Utrip::findHotelById(string id){
    for(int i=0;i<hotels.size();i++){
        if(hotels[i]->isEqual(id)){
            return hotels[i];
        }
    }
    return NULL;
}