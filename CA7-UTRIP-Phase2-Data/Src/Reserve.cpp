#include"Reserve.hpp"
#include"StructsAndDefines.hpp"
#include"Rating.hpp"
#include<string>
#include<vector>
#include<iostream>
#include<iomanip>
using namespace std;

typedef std::map<std::string,Rating> Ratings;
typedef vector<Room*> Rooms;


Reserve::Reserve(string hotelId_,Rooms rooms,RoomType roomType_,Duration duration_,double cost_){
    hotelId = hotelId_;
    roomType = roomType_;
    duration = duration_;
    bookedRooms = rooms;
    quantity = rooms.size();
    int days = duration.checkOut - duration.checkIn + 1;
    cost = quantity * cost_ * (double)days;
}


void Reserve::setId(int id_){
    id = id_;
}


int Reserve::getId(){ return id; }

vector<double> Reserve::getRoomsCost(){
    vector<double> costs;
    double eachRoomCost = cost/(quantity * (duration.checkOut - duration.checkIn + 1));
    for(int i=0;i<bookedRooms.size();i++){
        costs.push_back(eachRoomCost);
    }
    return costs;
}



double Reserve::getCost() { return cost; }

bool Reserve::isEqual(std::string username,int id_){
    if((clientUsername == username) && (id == id_)){
        return true;
    }
    return false;
}



void Reserve::showInfo(){
    cout<<ID<<": "<<id<<" "<<HOTEL<<": "<<hotelId<<" "<<ROOM<<": "<<getType(roomType)<<" "<<QUANTITY<<": "<<quantity;
    cout<<" "<<COST<<": "<<fixed<<setprecision(0)<<cost<<" "<<CHECK_IN<<" "<<duration.checkIn<<" "<<CHECK_OUT<<" "<<duration.checkOut;
}

void Reserve::showRoomsId(){
    for(int i=0;i<bookedRooms.size();i++){
        cout<<bookedRooms[i]->getId()<<" ";
    }
    cout<<endl;
}
string Reserve::getHotelId(){return hotelId; }
RoomType Reserve::getType(){return roomType; }

void Reserve::setClientUsername(std::string username){
    clientUsername = username;
}

void Reserve::deleteRoomsReservation(){
    for(int i=0;i<bookedRooms.size();i++){
        bookedRooms[i]->deleteDuration(duration);
    }
}
string Reserve::getType(RoomType type){
    string roomType;
    switch (type)
    {
    case 0:
        return STANDARD_ROOM;
    case 1:
        return DELUXE_ROOM;
    case 2:
        return LUXURY_ROOM;
    case 3:
        return PREMIUM_ROOM;
    break;
    }
}