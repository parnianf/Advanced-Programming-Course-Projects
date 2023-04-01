#include"StructsAndDefines.hpp"


bool Duration::operator==(const Duration& d){
    return ((checkIn == d.checkIn) && (checkOut == d.checkOut));
}

RatingCritera::RatingCritera(double location_,double cleanliness_,double staff_,double facilities_,double valueForMoney_,double overallRating_){
    location = location_;
    cleanliness = cleanliness_;
    staff = staff_;
    facilities = facilities_;
    valueForMoney = valueForMoney_;
    overallRating = overallRating_;
}
RatingCritera::RatingCritera(){
    
}