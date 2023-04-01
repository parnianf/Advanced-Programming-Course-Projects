#include"Filter.hpp"
#include"Errors.hpp"
#include<string>
#include<vector>
#include<iostream>
using namespace std;


CityCriterion::CityCriterion(string city_){ 
    city = city_;
}
vector<Hotel*> CityCriterion::applyFilter(vector<Hotel*> hotels){
    vector<Hotel*> filteredHotels;
    for(int i=0;i<hotels.size();i++){
        if(hotels[i]->isCityTheSame(city)){
            filteredHotels.push_back(hotels[i]);
        }
    }
    return filteredHotels;
}


StarCriterion::StarCriterion(string minStar_,string maxStar_){
    if(stoi(minStar_.c_str()) > stoi(maxStar_.c_str())){
        throw BadRequest();
    }
    if((stoi(minStar_.c_str()) > 5) || (stoi(minStar_.c_str()) < 1) || (stoi(maxStar_.c_str())>5) || (stoi(maxStar_.c_str())<1)){
        throw BadRequest();
    }
    minStar = minStar_;
    maxStar = maxStar_;
}

vector<Hotel*> StarCriterion::applyFilter(vector<Hotel*> hotels){
    vector<Hotel*> filteredHotels;
    for(int i=0;i<hotels.size();i++){
        for(int j = stoi(minStar.c_str()) ; j <= stoi(maxStar.c_str()) ; j++){
            if(hotels[i]->isStarTheSame(to_string(j))){
                filteredHotels.push_back(hotels[i]);
            }
        }
    }
    return filteredHotels;
}


PriceCriterion::PriceCriterion(string minPrice_,string maxPrice_){
    if(stoi(minPrice_.c_str()) > stoi(maxPrice_.c_str())){
        throw BadRequest();
    }
    if((stoi(minPrice_.c_str()) < 0) ||(stoi(maxPrice_.c_str()) < 0)){
        throw BadRequest();
    }
    minPrice = minPrice_;
    maxPrice = maxPrice_;
}

vector<Hotel*> PriceCriterion::applyFilter(vector<Hotel*> hotels){
    vector<Hotel*> filteredHotels;
    for(int i=0;i<hotels.size();i++){
        if(hotels[i]->isPriceInRange(stod(minPrice),stod(maxPrice))){
            filteredHotels.push_back(hotels[i]);
        }
    }
    return filteredHotels;
}

RoomCriterion::RoomCriterion(RoomType type_,int quantity_,Duration duration_){
    if(duration_.checkIn > duration_.checkOut){
        throw BadRequest();
    }
    if((duration_.checkIn > 30) || (duration_.checkOut < 1) || (duration_.checkIn > 30) || (duration_.checkIn <1)){
        throw BadRequest();
    }
    type = type_;
    quantity = quantity_;
    duration = duration_;
}
vector<Hotel*> RoomCriterion::applyFilter(vector<Hotel*> hotels){
    vector<Hotel*> filteredHotels;
    for(int i=0;i<hotels.size();i++){
        if((!hotels[i]->haveRoom(type,duration,quantity)) || hotels[i]->isFull(type,duration,quantity)){
            continue;
        }
        filteredHotels.push_back(hotels[i]);
    }
    return filteredHotels;
}

