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
#include<numeric>
#include<cmath>

using namespace std;

User::User(string username_,string password_,string email_){
    username = username_;
    password = password_;
    email = email_;
    wallet.amount = 0;
    wallet.bankStatement.push_back(0);
    reservationId = 0;
    isPriceFilterOn = true;
}

Rating User::estimateWeight(){
    Rating weight;
    vector<double> deltas;
    weight.setRandomly();

    for(int k=0;k<1000;k++){

        deltas = getAllDelta(weight);
        weight -= deltas;
        weight.clampFields();
    }
    return weight;
}

vector<double> User::getAllDelta(Rating weight){
    vector<double> deltas;
    for(int i = 0 ; i < 5 ; i++){
        deltas.push_back(getDelta(weight,i));
    }
    return deltas;
}

void User::showEstimatedWeight(){
    if(!doesHaveSufficientRating())
        throw InsufficientRating();
    getWeight().show();
}

double User::getDelta(Rating w,int i){
    double di = 0;
    for(auto rate : ratings){
        di += rate.second.getPartialDerivative(w,i);
    }
    return di;
}


Rating User::getWeight(){

    if(isManualWeightOn())
        return getManualWeight();
    else
        return estimateWeight();
}

bool User::doesHaveSufficientRating(){
    if(ratings.size() < 5)
        return false;
    return true;
}

Rating User::getManualWeight(){return ratings["ManualWeight"];}

string User::getReservedHotelId(int resId){
    Reserve* res = findReservationById(resId);
    if(res == NULL){
        throw NotFound();
    }
    return (res->getHotelId());
}

string User::getUsername(){
    return username;
}

bool User::doesExist(string email_,string password_){
    if((email == email_) && (password == password_))
        return true;
    return false;
}

void User::setManualWeight(Rating manualWeight_){
    ratings["ManualWeight"]= manualWeight_;
}

bool User::isManualWeightOn(){
    if(ratings.find("ManualWeight") != ratings.end())
        return true;
    return false;
}


void User::deactivateManualWeight(){
    if(ratings.find("ManualWeight") != ratings.end())
        ratings.erase("ManualWeight");
}


void User::showManualWeight() {
    if(!isManualWeightOn()){ 
        cout<<ACTIVE<<" "<<FALSE_<<endl;
        return;
    }
    Rating manualWeight = ratings["ManualWeight"];
    cout<< ACTIVE<<" "<<TRUE_<<" ";
    manualWeight.show();
}

void User::addRating(string hotelName,Rating rating){
    ratings[hotelName] = rating;
}

double User::getAverageBookedRoomsPrices(){
    vector<double> roomsCost;
    double sampleAverage = 0,standardDeviation = 0;
    for(int i=0;i<reservations.size();i++){
        vector<double> costs = reservations[i]->getRoomsCost();
        roomsCost.insert(roomsCost.end(),costs.begin(),costs.end());
    }   
    sampleAverage = accumulate(roomsCost.begin(),roomsCost.end(),sampleAverage) / roomsCost.size();
    return sampleAverage;
}

double User::getStandardDeviation(){
    vector<double> roomsCost;
    double sampleAverage = 0,standardDeviation = 0;
    for(int i=0;i<reservations.size();i++){
        vector<double> costs = reservations[i]->getRoomsCost();
        roomsCost.insert(roomsCost.end(),costs.begin(),costs.end());
    }   
    sampleAverage = accumulate(roomsCost.begin(),roomsCost.end(),sampleAverage) / roomsCost.size();
    vector<double> averagePrices(roomsCost.size(),sampleAverage);
    transform(roomsCost.begin(),roomsCost.end(),averagePrices.begin(),averagePrices.begin(),calculatePwrtwo);
    standardDeviation = sqrtl(accumulate(averagePrices.begin(),averagePrices.end(),standardDeviation) / (roomsCost.size()-1));
    return standardDeviation;
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

void User::turnOnorOffDefPriceFilter(bool active){
    isPriceFilterOn = active;
    if(!active){
        if(filters.find(DefaultPriceF) != filters.end())
            filters.erase(filters.find(DefaultPriceF)); 
    }
}

void User::purchase(operation op,double amount_){
    wallet.amount = op(wallet.amount,amount_);
    wallet.bankStatement.push_back(wallet.amount);
}

bool User::hasDefaultPriceFilter(){
    if(filters.find(DefaultPriceF) != filters.end())
        return true;
    return false;
}

void User::showBankStatement(int count){
    int range = wallet.bankStatement.size() - count;
    if(range<0)
        range = 0;
    for(int i = wallet.bankStatement.size()-1 ; i >= range ; i--){
        cout<<fixed<<setprecision(0)<<wallet.bankStatement[i]<<endl;
    }
}

bool User::hasPriceFilter(){
    if(filters.find(PriceF) == filters.end())
        return false;
    return true;
}

void User::applyDefaultPriceFilter(){
    if(!canApplyDefPrice())
        return;
    DefaultPriceCriterion* price = new DefaultPriceCriterion(getStandardDeviation(),getAverageBookedRoomsPrices());
    filters[DefaultPriceF] = price;
}

bool User::canApplyDefPrice(){
    if(hasPriceFilter())
        return false;
    if(reservations.size() < 10)
        return false;
    if(!isPriceFilterOn)
        return false;
    return true;
    
}

void User::applyFilter(FilterType type,Arguments data){

    switch(type){
        case CityF:{
            CityCriterion* city = new CityCriterion(data[CITY]);
            filters[CityF] = city;
        break;
        }
        case StarF:{
            StarCriterion* star = new StarCriterion(data[MIN_STAR],data[MAX_STAR]);
            filters[StarF] = star;
        break;
        }
        case PriceF:{   
            PriceCriterion* price = new PriceCriterion(data[MIN_PRICE],data[MAX_PRICE]);
            filters[PriceF] = price;
            if(filters.find(DefaultPriceF) != filters.end())
                filters.erase(filters.find(DefaultPriceF)); 
        break;
        }
        case RoomF:{
            Duration duration;
            duration.checkIn = stoi(data[CHECK_IN].c_str());
            duration.checkOut = stoi(data[CHECK_OUT].c_str()); 
            RoomCriterion* room = new RoomCriterion(getType(data[TYPE]),stoi(data[QUANTITY].c_str()),duration);
            filters[RoomF] = room;
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
    if(!hasEnoughMoney(reservedRooms->getCost()))
        throw NotEnoughCredit();
    reservationId++;
    reservedRooms->setId(reservationId);
    reservedRooms->setClientUsername(username);
    reservations.push_back(reservedRooms);
    reservedRooms->showRoomsId();
}

void User::deleteReservation(int resId){
    if(!findReservationById(resId))
        throw NotFound();
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

