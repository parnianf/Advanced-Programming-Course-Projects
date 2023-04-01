#ifndef RATING_H
#define RATING_H "RATING_H"

#include"StructsAndDefines.hpp"
#include<vector>

class Rating{

public:
    Rating();
    Rating(double location_,double cleanliness_,double staff_,double facilities_,double valueForMoney_,double overallRating_);
    
private:
    double location;
    double cleanliness;
    double staff;
    double facilities;
    double valueForMoney;
    double overallRating;
};

#endif
