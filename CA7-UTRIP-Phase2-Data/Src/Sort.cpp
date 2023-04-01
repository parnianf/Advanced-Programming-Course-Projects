#include"Sort.hpp"
#include"User.hpp"
#include"Errors.hpp"
#include<algorithm>
#include<iostream>

using namespace std;

vector<Hotel*> Sort::sortInOrder(vector<Hotel*> hotels,std::string property,std::string order_,User* user,bool& didSortTheHotels){

    Order order = order_ == ASCENDING ? AscendingOrd : DescendingOrd;
    if(property == NAME)
        return sortByName(hotels,order);
    else if(property == ID)
        return sortById(hotels,order);
    else if(property == STAR_RATING)
        return sortByStar(hotels,order);
    else if(property == CITY)
        return sortByCity(hotels,order);
    else if(property == AVERAGE_ROOM_PRICE)
        return sortByAveragePrice(hotels,order);
    else if(property == STANDARD_ROOM_PRICE)
        return sortByRoomTypePrice(hotels,order,Standard);
    else if(property == DELUXE_ROOM_PRICE)
        return sortByRoomTypePrice(hotels,order,Deluxe);
    else if(property == LUXURY_ROOM_PRICE)
        return sortByRoomTypePrice(hotels,order,Luxury);
    else if(property == PREMIUM_ROOM_PRICE)
        return sortByRoomTypePrice(hotels,order,Premium);
    else if(property == RATING_PERSONAL)
        return sortByPersonalRating(hotels,order,user,didSortTheHotels);
    else throw BadRequest();
}


vector<Hotel*> Sort::sortByName(vector<Hotel*> hotels,Order order){

    sort(hotels.begin(),hotels.end(),[order](Hotel* hotel1,Hotel* hotel2){ 
        if(order == DescendingOrd)
            return hotel1->getHotelInfo().name > hotel2->getHotelInfo().name;
        if(order == AscendingOrd)
            return hotel1->getHotelInfo().name < hotel2->getHotelInfo().name;});
    return hotels;
}


vector<Hotel*> Sort::sortById(vector<Hotel*> hotels,Order order){
    sort(hotels.begin(),hotels.end(),[order](Hotel* hotel1,Hotel* hotel2){ 
        if(order == DescendingOrd)
            return hotel1->getId() > hotel2->getId();
        if(order == AscendingOrd)
            return hotel1->getId() < hotel2->getId(); });
    return hotels;
}


vector<Hotel*> Sort::sortByCity(vector<Hotel*> hotels,Order order){
    int i=0;
    sort(hotels.begin(),hotels.end(),[order](Hotel* hotel1,Hotel* hotel2){ 
        if(order == DescendingOrd){
            if(hotel1->getCity() == hotel2->getCity())
                return hotel1->getId() < hotel2->getId();
            return hotel1->getCity() > hotel2->getCity();
        }
        if(order == AscendingOrd){
            if(hotel1->getCity() == hotel2->getCity())
                return hotel1->getId() < hotel2->getId();
            return hotel1->getCity() < hotel2->getCity(); 
        } });
    return hotels;
}


vector<Hotel*> Sort::sortByAveragePrice(vector<Hotel*> hotels,Order order){
    sort(hotels.begin(),hotels.end(),[order](Hotel* hotel1,Hotel* hotel2){ 
        if(order == DescendingOrd){
            if(hotel1->getAveragePrice() == hotel2->getAveragePrice())
                return hotel1->getId() < hotel2->getId();
            return hotel1->getAveragePrice() > hotel2->getAveragePrice();
        }
        if(order == AscendingOrd){
            if(hotel1->getAveragePrice() == hotel2->getAveragePrice())
                return hotel1->getId() < hotel2->getId();
            return hotel1->getAveragePrice() < hotel2->getAveragePrice();
        } });
    return hotels;
}


vector<Hotel*> Sort::sortByPersonalRating(vector<Hotel*> hotels,Order order,User* user,bool& didSortTheHotels){
    if(!user->doesHaveSufficientRating() && !user->isManualWeightOn()){
        didSortTheHotels = false;
        return hotels;
    }
    Rating weight = user->getWeight();
    string username = user->getUsername();
    sort(hotels.begin(),hotels.end(),[order,username,weight](Hotel* hotel1,Hotel* hotel2){
    if(order == DescendingOrd){
        if(hotel1->getPersonalRating(username,weight) == hotel2->getPersonalRating(username,weight))
            return hotel1->getId() < hotel2->getId();
        return hotel1->getPersonalRating(username,weight) > hotel2->getPersonalRating(username,weight);
    }
    if(order == AscendingOrd){
        if(hotel1->getPersonalRating(username,weight) == hotel2->getPersonalRating(username,weight))
            return hotel1->getId() < hotel2->getId();
        return hotel1->getPersonalRating(username,weight) < hotel2->getPersonalRating(username,weight);
    } });
    return hotels;
}


vector<Hotel*> Sort::sortByStar(vector<Hotel*> hotels,Order order){
    sort(hotels.begin(),hotels.end(),[order](Hotel* hotel1,Hotel* hotel2){ 
        if(order == DescendingOrd){
            if(hotel1->getHotelInfo().star == hotel2->getHotelInfo().star)
                return hotel1->getId() < hotel2->getId();
            return hotel1->getHotelInfo().star > hotel2->getHotelInfo().star;
        }
        if(order == AscendingOrd){
            if(hotel1->getHotelInfo().star == hotel2->getHotelInfo().star)
                return hotel1->getId() < hotel2->getId();
            return hotel1->getHotelInfo().star < hotel2->getHotelInfo().star;
        } });
    return hotels;
}

vector<Hotel*> Sort::sortByRoomTypePrice(vector<Hotel*> hotels,Order order,RoomType roomType){

    sort(hotels.begin(),hotels.end(),[order,roomType](Hotel* hotel1,Hotel* hotel2){ 
        if(order == DescendingOrd){
            if(hotel1->getRoomPrice(roomType) == hotel2->getRoomPrice(roomType))
                return hotel1->getId() < hotel2->getId();
            return hotel1->getRoomPrice(roomType) > hotel2->getRoomPrice(roomType);
        }
        if(order == AscendingOrd){
            if(hotel1->getRoomPrice(roomType) == hotel2->getRoomPrice(roomType))
                return hotel1->getId() < hotel2->getId();
            return hotel1->getRoomPrice(roomType) < hotel2->getRoomPrice(roomType);
        } });
    return hotels;
}

