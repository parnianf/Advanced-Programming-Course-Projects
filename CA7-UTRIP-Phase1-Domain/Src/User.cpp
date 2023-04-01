#include"User.hpp"
#include"Filter.hpp"
#include"Reserve.hpp"
#include"Functions.hpp"
#include"Errors.hpp"
#include"StructsAndDefines.hpp"
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;



User::User(string username_,string password_,string email_){
    username = username_;
    password = password_;
    email = email_;
    wallet.amount = 0;
    wallet.bankStatement.push_back(0);
    reservationId = 0;
}
string User::getReservedHotelId(int resId){
    Reserve* res = findReservationById(resId);
    if(res == NULL){
        throw NotFound();
    }
    return (res->getHotelId());
}
string User::getUsername(){return username;}

bool User::doesExist(string email_,string password_){
    if((email == email_) && (password == password_))
        return true;
    return false;
}

bool User::isEqual(string username_,string email_){
    if( (username == username_) || (email == email_)){
        return true;
    }
    return false;
}

bool User::hasFilter() {
    if(filters.size() != 0){
        return true;
    }
    return false;
}
void User::showReservationInfo(){
    for(int i = reservations.size()-1 ; i >= 0 ; i--){
        reservations[i]->showInfo();
        cout<<endl;
    }

    if(reservations.size() == 0){
        cout<<EMPTY<<endl;
    }
}
void User::deleteFilters(){
    filters.clear();
}

bool User::hasEnoughMoney(double cost){
    if(wallet.amount < cost){
        return false;
    }
    return true;
}

void User::purchase(operation op,double amount_){
    wallet.amount = op(wallet.amount,amount_);
    wallet.bankStatement.push_back(wallet.amount);
}

void User::showBankStatement(int count){
    int range = wallet.bankStatement.size() - count;
    if(range<0)
        range = 0;
    for(int i = wallet.bankStatement.size()-1 ; i >= range ; i--){
        cout<<fixed<<setprecision(0)<<wallet.bankStatement[i]<<endl;
    }
}

void User::applyFilter(FilterType type,Arguments data){
    switch(type){
        case CityF:{
            CityCriterion* city = new CityCriterion(data[CITY]);
            filters[CityF] = city;
        break;
        }
        case StarF:{
            StarCriterion* star_ = new StarCriterion(data[MIN_STAR],data[MAX_STAR]);
            filters[StarF] = star_;
        break;
        }
        case PriceF:{   
            PriceCriterion* price_ = new PriceCriterion(data[MIN_PRICE],data[MAX_PRICE]);
            filters[PriceF] = price_;
        break;
        }
        case RoomF:{
            Duration duration;
            duration.checkIn = stoi(data[CHECK_IN].c_str());
            duration.checkOut = stoi(data[CHECK_OUT].c_str()); 
            RoomCriterion* room_ = new RoomCriterion(getType(data[TYPE]),stoi(data[QUANTITY].c_str()),duration);
            filters[RoomF] = room_;
        }
    }

}

vector<Hotel*> User::getfilteredHotels(vector<Hotel*> hotels){
    vector<Hotel*> h1 = hotels,h2;
    for(auto it : filters){
        h2 = it.second->applyFilter(h1);
        h1 = h2;
    }
    return h1;
}
void User::addReservation(Reserve* reservedRooms){
    if(!hasEnoughMoney(reservedRooms->getCost())){
        throw NotEnoughCredit();
        return;
    }
    reservationId++;
    reservedRooms->setId(reservationId);
    reservedRooms->setClientUsername(username);
    reservations.push_back(reservedRooms);
    reservedRooms->showRoomsId();
}

void User::deleteReservation(int resId){
    if(!findReservationById(resId)){
        throw NotFound();
        return;
    }
    Reserve* res = findReservationById(resId);
    purchase(add,(res->getCost())/(double)2);
    res->deleteRoomsReservation();
    reservations.erase(remove(reservations.begin(), reservations.end(), res), reservations.end());
}


Reserve* User::findReservationById(int id){
    for(int i=0 ; i<reservations.size();i++){
        if(reservations[i]->getId() == id){
            return reservations[i];
        }
    }
    return NULL;
}

