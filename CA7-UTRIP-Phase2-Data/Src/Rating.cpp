#include"Rating.hpp"
#include<vector>
#include"StructsAndDefines.hpp"
#include"Functions.hpp"
#include"Errors.hpp"
#include<algorithm>
#include<numeric>
#include<iostream>
#include<iomanip>
#include<ctime>
#include<random>
using namespace std;

Rating::Rating(double location_,double cleanliness_,double staff_,double facilities_,double valueForMoney_,double overallRating_){
    checkRatingsInRange(location_,cleanliness_,staff_,facilities_,valueForMoney_,overallRating_);
    location = location_;
    cleanliness = cleanliness_;
    staff = staff_;
    facilities = facilities_;
    valueForMoney = valueForMoney_;
    overallRating = overallRating_;
}
Rating::Rating(){
    
}

void Rating::checkRatingsInRange(double location_,double cleanliness_,double staff_,double facilities_,double valueForMoney_,double overallRating_){
    if( location_ > RATING_RANGE_TO || location_ < RATING_RANGE_FROM  || cleanliness_ <RATING_RANGE_FROM || cleanliness_ >RATING_RANGE_TO || staff_ <RATING_RANGE_FROM || staff_ >RATING_RANGE_TO ||
        facilities_ >RATING_RANGE_TO || facilities_ <RATING_RANGE_FROM || valueForMoney_ > RATING_RANGE_TO ||valueForMoney_ <RATING_RANGE_FROM ){
            throw BadRequest();
        }
}

Rating Rating::operator*(Rating rating){
    Rating rate;
    rate.location = location * rating.location;
    rate.cleanliness = cleanliness * rating.cleanliness;
    rate.staff = staff * rating.staff;
    rate.facilities = facilities * rating.facilities;
    rate.valueForMoney = valueForMoney * rating.valueForMoney;
    return rate;
    
}

double Rating::getTotalSum(){
    return (location + cleanliness + staff + facilities + valueForMoney);
}

void Rating::addEpsilon(double epsilon , int i){
    if(i==0) location+=epsilon;
    else if(i==RATING_RANGE_FROM) cleanliness+=epsilon;
    else if(i==2) staff+=epsilon;
    else if(i==3) facilities+=epsilon;
    else if(i==4) valueForMoney+=epsilon;
}

void Rating::setRandomly(){
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(1.0,5.0);

    location = distribution(generator);
    cleanliness = distribution(generator);
    staff = distribution(generator);
    facilities = distribution(generator);
    valueForMoney = distribution(generator);
    overallRating = 0;
}


void Rating::clampFields(){
    location = clamp(location,RATING_RANGE_FROM,RATING_RANGE_TO);
    cleanliness = clamp(cleanliness,RATING_RANGE_FROM,RATING_RANGE_TO); 
    staff = clamp(staff,RATING_RANGE_FROM,RATING_RANGE_TO);
    facilities = clamp(facilities,RATING_RANGE_FROM,RATING_RANGE_TO);
    valueForMoney = clamp(valueForMoney,RATING_RANGE_FROM,RATING_RANGE_TO);
}



double Rating::clamp(double num,double low,double high){
    if(num <= low) 
        return low;
    num = (num >= high) ? high : num;
    return num;
}

void Rating::show(){

    cout<<LOCATION<<" "<<truncate(location)<<" "<<
    CLEANLINESS<<" "<<truncate(cleanliness)<<" "<<STAFF<<" "
    <<truncate(staff)<<" "<<FACILITIES<<" "<<truncate(facilities)<<" "
    <<VALUE_FOR_MONEY<<" "<<truncate(valueForMoney)<<" "<<endl;
}
double Rating::getOverallRating(){ return overallRating; }

void Rating::showHotelRatings(){
    cout<<SHOW_LOCATION<<fixed<<setprecision(2)<<location<<endl;
    cout<<SHOW_CLEANLINESS<<fixed<<setprecision(2)<<cleanliness<<endl;
    cout<<SHOW_STAFF<<fixed<<setprecision(2)<<staff<<endl;
    cout<<SHOW_FACILITIES<<fixed<<setprecision(2)<<facilities<<endl;
    cout<<SHOW_VALUE_FOR_MONEY<<fixed<<setprecision(2)<<valueForMoney<<endl;
    cout<<SHOW_OVERAL_RATING<<fixed<<setprecision(2)<<overallRating<<endl;
}

Rating Rating::operator-=(vector<double> vec){
    location -= vec[0];
    cleanliness -= vec[1];
    staff -= vec[2];
    facilities -= vec[3];
    valueForMoney -= vec[4];
    return *this;
}

double Rating::estimateOverallRating(Rating weight){
    Rating average = weight * *this;
    return average.getTotalSum() / weight.getTotalSum();
}

double Rating::getError(Rating weight){
    return pow(estimateOverallRating(weight) - overallRating,2) ;
}

double Rating::getPartialDerivative(Rating weight,int i){
    Rating w = weight;
    double epsilon = 0.0001;
    w.addEpsilon(epsilon,i);
    return ((getError(w) - getError(weight))/epsilon);
}

