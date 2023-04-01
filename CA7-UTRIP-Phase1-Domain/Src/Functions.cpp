#include"Functions.hpp"
#include<string>
#include"StructsAndDefines.hpp"
#include"Hotel.hpp"
#include"Errors.hpp"
using namespace std;

double add(double a,double b){return  a+b; }
double sub(double a,double b){return a-b; }

RoomType getType(string type){
    if(type == STANDARD_ROOM){
        return Standard;
    }
    else if(type == DELUXE_ROOM){
        return Deluxe;
    }
    else if(type == LUXURY_ROOM){
        return Luxury;
    }
    else if(type == PREMIUM_ROOM){
        return Premium;
    }
    else throw NotFound();
}



bool comparator(Hotel* hotelA,Hotel* hotelB){
    return (hotelA->getId() < hotelB->getId());
}


FilterType getFilterType(string type){
    if(type == "cityFilter"){
        return CityF;
    }
    if(type == "starFilter"){
        return StarF;
    }
    if(type == "priceFilter"){
        return PriceF;
    }
    if(type == "roomFilter"){
        return RoomF;
    }
}




