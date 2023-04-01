#include"Hotel.hpp"
#include<string>
#include"Reserve.hpp"
#include"Room.hpp"
#include"User.hpp"
#include"StructsAndDefines.hpp"
#include<vector>
#include<iostream>
#include<iomanip>
#include<algorithm>

using namespace std;

Hotel::Hotel(struct HotelInfo hotelInfo_,struct Place place_,Rooms rooms_,vector<RoomInfo> roomsInfo_){
    hotelInfo = hotelInfo_;
    place = place_;
    rooms = rooms_;
    roomsInfo = roomsInfo_;
}

bool Hotel::isCityTheSame(string city_){
    return (place.city == city_);
}

void Hotel::setPreviousRatings(Rating rating){
    ratings["File"] = rating;
}

bool Hotel::isStarTheSame(string star_){
    return (hotelInfo.star == star_);
}
bool Hotel::isPriceInRange(double minAvPrice,double maxAvPrice){
    if((getAveragePrice() >= minAvPrice) && (getAveragePrice() <= maxAvPrice)){
        return true;
    }
    return false;
}



bool Hotel::haveRoom(RoomType type,Duration dur,int quantity){
    for(int i=0;i<roomsInfo.size();i++){
        if(roomsInfo[i].type == type){
            if(roomsInfo[i].quantity < quantity){
                return false;
            }
        }
    }
    return true;
}


double Hotel::getPersonalRating(string username,Rating weight){
    if(ratings.find(username) != ratings.end())
        return ratings[username].getOverallRating();
    Rating ave = ratings["File"] * weight;
    return (ave.getTotalSum())/(weight.getTotalSum());
}

void Hotel::showComments(){
    for(int i = comments.size() -1 ; i >= 0 ; i--){
        cout<<comments[i].name<<": "<<comments[i].comment<<endl;
    }
}

void Hotel::addComment(Comment newComment){
    comments.push_back(newComment);
}

bool Hotel::isEqual(string id){
    return ( id == hotelInfo.uniqueId);
}
bool Hotel::isFull(RoomType type,Duration dur,int quantity){
    Rooms typeRooms = getRoomsInType(type);
    int emptyRoomNumber = typeRooms.size();
    for(int i=0;i<typeRooms.size() ; i++){
        if(!typeRooms[i]->isEmpty(dur) ){
            emptyRoomNumber--;
        }
    }
    if(emptyRoomNumber < quantity){
        return true;
    }
    return false;
}

string Hotel::getId(){
    return hotelInfo.uniqueId;
}
void Hotel::showInShort(){
    cout<<hotelInfo.uniqueId<<" "<<hotelInfo.name<<" "
    <<hotelInfo.star<<" "<<place.city<<" "<<rooms.size()
    <<" "<<fixed<<setprecision(2)<<getAveragePrice()<<" "<<endl;
}
void Hotel::showComplete(){
    cout<<hotelInfo.uniqueId<<endl<<hotelInfo.name<<endl;
    cout<<SHOW_STAR<<hotelInfo.star<<endl;
    cout<<SHOW_OVERVIEW<<hotelInfo.overview<<endl;
    cout<<SHOW_AMENITIES<<hotelInfo.amenities<<endl;
    cout<<SHOW_CITY<<place.city<<endl;
    cout<<SHOW_LATITUDE<<fixed<<setprecision(2)<<stod(place.latitude.c_str())<<endl;
    cout<<SHOW_LONGITUDE<<fixed<<setprecision(2)<<stod(place.longitude.c_str())<<endl;
    cout<<SHOW_ROOMS;
    for(int i=0;i<roomsInfo.size();i++){
        cout<<roomsInfo[i].quantity;
        if(i<roomsInfo.size()-1){
            cout<<" ";
        }
    }
    cout<<endl;
    cout<<SHOW_PRICE;
    for(int i=0;i<roomsInfo.size();i++){
        cout<<fixed<<setprecision(0)<<roomsInfo[i].price;
        if(i<roomsInfo.size()-1){
            cout<<" ";
        }
    }
    cout<<endl;
}

double Hotel::getTotalCost(RoomType type,int quantity,Duration dur){
    for(int i=0;i<roomsInfo.size();i++){
        if(roomsInfo[i].type == type){
            int duration = dur.checkOut - dur.checkOut + 1;
            return(roomsInfo[i].price * quantity * duration);
        }
    }
}

Reserve* Hotel::bookRooms(string hotelId,RoomType roomType,int quantity,Duration duration){
    Rooms typeRooms = getRoomsInType(roomType);
    Rooms selectedRooms;
    int bookedRoomsNum = 0;
    for(int i=0 ; i < typeRooms.size() ; i++){
        if(typeRooms[i]->isEmpty(duration)){
            typeRooms[i]->addReservation(duration);
            selectedRooms.push_back(typeRooms[i]);
            bookedRoomsNum++;
        }
        if(bookedRoomsNum == quantity)
            break;
    }
    Reserve* newReservation = new Reserve(hotelId,selectedRooms,roomType,duration,getRoomPrice(roomType));
    reservations.push_back(newReservation);
    return newReservation;
}

void Hotel::deleteReservation(string clientUsername,int resId){
    Reserve* res = findReservation(clientUsername,resId);
    reservations.erase(remove(reservations.begin(), reservations.end(), res), reservations.end());
}

void Hotel::addRating(Rating newRating,string username){
    ratings[username] = newRating;
}

void Hotel::showRating(){
    if(ratings.size() == 0){
        cout<<NO_RATING<<endl;
        return;
    }
    Rating avRating = ratings["File"];
    avRating.showHotelRatings();
}

double Hotel::getRoomPrice(RoomType type){
    for(int i=0;i<roomsInfo.size();i++){
        if(type == roomsInfo[i].type){
            return roomsInfo[i].price;
        }
    }
}

Rooms Hotel::getRoomsInType(RoomType type){
    Rooms typeRooms;
    for(int i=0;i<rooms.size();i++){
        if(type == rooms[i]->getType()){
            typeRooms.push_back(rooms[i]);
        }
    }
    return typeRooms;
}

Reserve* Hotel::findReservation(string clientUsername,int resId){
    for(int i=0;i<reservations.size();i++){
        if(reservations[i]->isEqual(clientUsername,resId)){
            return reservations[i];
        }
    }
}
double Hotel::getAveragePrice(){
    double sum =0,num = 0;
    for(int i=0;i<roomsInfo.size();i++){
        if(roomsInfo[i].price != 0){
            sum+=roomsInfo[i].price;
            num++;
        }
    }
    if(num == 0){
        return 0;
    }
    return(sum/num);
}
