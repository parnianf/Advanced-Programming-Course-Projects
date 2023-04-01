#include"Room.hpp"
#include"StructsAndDefines.hpp"
using namespace std;


Room::Room(string roomId_,RoomType type_){
    roomId = roomId_;
    type = type_;
}

bool Room::isEmpty(Duration d){
    for(int i=0;i<reservationTimeTable.size();i++){
        if(doesOverlap(reservationTimeTable[i],d)){
            return false;
        }
    }
    return true;
}

bool Room::doesOverlap(Duration d1,Duration d2){
    if( ((d1.checkIn >= d2.checkIn)  && (d1.checkIn <= d2.checkOut)) ||
        ((d2.checkIn >= d1.checkIn) && (d2.checkIn <= d1.checkOut))){
            return true;
    }
    return false;

}
string Room::getId(){return roomId; } 
RoomType Room::getType() { return type;}

void Room::addReservation(Duration newResTime){
    reservationTimeTable.push_back(newResTime);
}

void Room::deleteDuration(Duration duration){
    for(int i=0;i<reservationTimeTable.size();i++){
        if(reservationTimeTable[i] == duration){
            reservationTimeTable.erase(reservationTimeTable.begin()+i);
        }
    }
}