#include"Rating.hpp"
#include<vector>
#include"StructsAndDefines.hpp"
#include"Functions.hpp"
#include<algorithm>
#include<numeric>
#include<iostream>
#include<iomanip>
#include<ctime>
#include<random>
using namespace std;

Rating::Rating(double location_,double cleanliness_,double staff_,double facilities_,double valueForMoney_,double overallRating_){
    location = location_;
    cleanliness = cleanliness_;
    staff = staff_;
    facilities = facilities_;
    valueForMoney = valueForMoney_;
    overallRating = overallRating_;
}