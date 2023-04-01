#include "Utrip.hpp"
#include"Room.hpp"
#include"User.hpp"
#include"StructsAndDefines.hpp"
#include"Filter.hpp"
#include"Functions.hpp"
#include"Errors.hpp"
#include<iostream>
#include<algorithm>
#include<sstream>

using namespace std;



Utrip::Utrip(string filePath){
    hotels = cvsReader.readData(filePath);
    currentUser = NULL;
}
void Utrip::applyFilter(FilterType filterType, Arguments data){
    currentUser->applyFilter(filterType,data);
}
void Utrip::deleteFilters(){
    if(currentUser){
        currentUser->deleteFilters();
        cout<<SUCCESSFUL<<endl;
    }
}
bool Utrip::isLoggedIn(){
    if(currentUser != NULL)
        return true;
    return false;
}
void Utrip::addUser(User* newUser){
    users.push_back(newUser);
}

bool Utrip::isUnique(Arguments arg){
    string email = arg[EMAIL] , username = arg[USERNAME];
    for(int i=0 ; i < users.size() ; i++){
        if(users[i]->isEqual(username,email)){
            throw BadRequest();
        }
    }
    return true;

}
void Utrip::setCurrentUser(string email,string password){
    for(int i=0;i<users.size();i++){
        if(users[i]->doesExist(email,password)){
            currentUser = users[i];
        }
    }
}
void Utrip::setCurrentUser(User* newUser){
    currentUser = newUser;
}
void Utrip::logoutUser(){
    currentUser = NULL;
}
bool Utrip::isUserValid(string email,string password){
    for(int i=0;i<users.size();i++){
        if(users[i]->doesExist(email,password)){
            return true;
        }
    }
    return false;
}

void Utrip::showHotelsInShort(){
    if(!currentUser->hasFilter()){
        showAbstractHotelInfo(hotels);
    }
    else{
        vector<Hotel*> filteredHotels = currentUser->getfilteredHotels(hotels);
        if(filteredHotels.size() == 0){
            cout<<EMPTY<<endl;
            return;
        }
        showAbstractHotelInfo(filteredHotels);
    }
}

void Utrip::showHotelInfo(string uniqueId){
    Hotel* hotel = findHotelById(uniqueId);
        if(hotel){
            hotel->showComplete();
        }
        else{
            throw NotFound();
        }
}

void Utrip::login(Arguments info){
    unsigned long int hashedPassword = hash<string>()(info[PASSWORD]);
    if(isUserValid(info[EMAIL],to_string(hashedPassword))){
        deleteFilters();
        setCurrentUser(info[EMAIL],to_string(hashedPassword));
        cout<<SUCCESSFUL<<endl;
        return;
    }
    throw BadRequest();
}


void Utrip::reserve(string hotelId,RoomType roomType,int quantity,Duration duration){
    Reserve* reservation = bookReservation(hotelId,roomType,quantity,duration);
    if(!reservation){
        return;
    }
    currentUser->addReservation(reservation);
    currentUser->purchase(sub,reservation->getCost());
}
void Utrip::purchase(operation op,double amount){
    if(amount <= 0){
        throw BadRequest();
        return;
    }
    currentUser->purchase(op,amount);
    cout<<SUCCESSFUL<<endl;
}

void Utrip::signup(Arguments information){
    deleteFilters();
    unsigned long int hashedPassword = hash<string>()(information[PASSWORD]);
    User* newUser = new User(information[USERNAME],to_string(hashedPassword),information[EMAIL]);
    currentUser = newUser;
    users.push_back(newUser);
}


void Utrip::showBankStatement(int count){
    currentUser->showBankStatement(count);
}

void Utrip::showReservations(){
    currentUser->showReservationInfo();
}

void Utrip::deleteReservation(Arguments arg){
    int reservationId = stoi(arg[ID].c_str());
    Hotel* hotel = findHotelById(currentUser->getReservedHotelId(reservationId));
    currentUser->deleteReservation(reservationId);
    hotel->deleteReservation(currentUser->getUsername(),reservationId);
}

void Utrip::addComment(string hotelId,string comment){
    if(!findHotelById(hotelId)){
            throw NotFound();
            return;
        }
        Comment cm;
        cm.name = currentUser->getUsername();
        cm.comment = comment;
        Hotel* hotel = findHotelById(hotelId);
        hotel->addComment(cm);
}

void Utrip::showComments(string hotelId){
    Hotel* hotel = findHotelById(hotelId);
    hotel->showComments();
}
void Utrip::showRating(Arguments arg){
    Hotel* hotel = findHotelById(arg[HOTEL]);
    hotel->showRating();
}

bool Utrip::isRatingValid(Arguments arg){
    for(auto it : arg){
        if(it.first != HOTEL){
            if( (stod(it.second.c_str()) > 5) || (stod(it.second.c_str()) < 1) ) {
                throw BadRequest();
                return false;
            }
        }
    }
    return true;
}

void Utrip::addRating(Arguments arg){
    if(!isRatingValid(arg)){
        return;       
    }
    RatingCritera rating(stod(arg[LOCATION].c_str()),stod(arg[CLEANLINESS].c_str()),stod(arg[STAFF].c_str()),
                        stod(arg[FACILITIES].c_str()),stod(arg[VALUE_FOR_MONEY].c_str()),stod(arg[OVERALL_RATING].c_str()));
    Hotel* hotel = findHotelById(arg[HOTEL]);
    hotel->addRating(rating,currentUser->getUsername());
}
    
void Utrip::showAbstractHotelInfo(vector<Hotel*> hotels_){
    sort(hotels_.begin(),hotels_.end(),comparator);
    for(int i=0;i<hotels_.size();i++){
        hotels_[i]->showInShort();
    }
}

Reserve* Utrip::bookReservation(string hotelId,RoomType roomType,int quantity,Duration duration){
    if(canReserve(hotelId,roomType,quantity,duration)){
        Hotel* hotel = findHotelById(hotelId);
        Reserve* reservation = hotel->bookRooms(hotelId,roomType,quantity,duration);
        return reservation;
    }
    return NULL;
}

bool Utrip::canReserve(string hotelId,RoomType roomType,int quantity,Duration duration){
    if(!findHotelById(hotelId)){
        throw NotFound();
        return false;
    }
    Hotel* hotel = findHotelById(hotelId);
    if((!hotel->haveRoom(roomType,duration,quantity)) ||
        (hotel->isFull(roomType,duration,quantity))){
        throw NotEnoughRoom();
        return false;
    }
    if(!currentUser->hasEnoughMoney(hotel->getTotalCost(roomType,quantity,duration))){
        throw NotEnoughCredit();
        return false;
    }
    return true;
}

Hotel* Utrip::findHotelById(string id){
    for(int i=0;i<hotels.size();i++){
        if(hotels[i]->isEqual(id)){
            return hotels[i];
        }
    }
    throw NotFound();
    return NULL;
}