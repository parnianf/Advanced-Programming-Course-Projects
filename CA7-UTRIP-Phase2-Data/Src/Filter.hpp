#ifndef FILTER_H
#define FILTER_H "FILTER_H"

#include"Hotel.hpp"
#include"User.hpp"
#include<vector>
#include<string>
class Hotel;

class Filter{
public:
    virtual std::vector<Hotel*> applyFilter(std::vector<Hotel*> hotels) = 0;
};

class CityCriterion : public Filter{
public:
    CityCriterion(std::string city_);
    virtual std::vector<Hotel*> applyFilter(std::vector<Hotel*> hotels);
private:
    std::string city;
};

class StarCriterion : public Filter{
public:
    StarCriterion(std::string minStar_,std::string maxStar_);
    std::vector<Hotel*> applyFilter(std::vector<Hotel*> hotels);
private:
    std::string minStar;
    std::string maxStar;
};

class PriceCriterion : public Filter{
public:
    PriceCriterion(std::string minPrice_,std::string maxPrice_);
    std::vector<Hotel*> applyFilter(std::vector<Hotel*> hotels);
private:
    std::string minPrice;
    std::string maxPrice;

};

class RoomCriterion : public Filter{
public:
    RoomCriterion(RoomType type_,int quantity_,Duration duration_);
    std::vector<Hotel*> applyFilter(std::vector<Hotel*> hotels);
private:
    RoomType type;
    int quantity;
    Duration duration;

};

class DefaultPriceCriterion : public Filter{
public:
    DefaultPriceCriterion(double standardDeviation_,double sampleAverage_);
    std::vector<Hotel*> applyFilter(std::vector<Hotel*> hotels);
private:
    double standardDeviation,sampleAverage;
};




#endif