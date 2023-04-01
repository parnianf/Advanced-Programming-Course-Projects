#ifndef RATING_H
#define RATING_H "RATING_H"

#include"StructsAndDefines.hpp"
#include<vector>

class Rating{

public:
    Rating();
    Rating(double location_,double cleanliness_,double staff_,double facilities_,double valueForMoney_,double overallRating_);
    void checkRatingsInRange(double location_,double cleanliness_,double staff_,double facilities_,double valueForMoney_,double overallRating_);
    double getTotalSum();
    void setRandomly();
    void clampFields();
    double clamp(double num,double low,double high);
    void addEpsilon(double epsilon , int i);
    Rating operator*(Rating rating);
    Rating operator-=(std::vector<double> vec);
    void show();
    double getOverallRating();
    void showHotelRatings();
    double estimateOverallRating(Rating weight);
    double getError(Rating weight);
    double getPartialDerivative(Rating weight,int i);
    
private:
    double location;
    double cleanliness;
    double staff;
    double facilities;
    double valueForMoney;
    double overallRating;
};

#endif
