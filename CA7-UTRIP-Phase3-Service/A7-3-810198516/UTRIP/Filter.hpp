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


class StarCriterion : public Filter{
public:
    StarCriterion(std::string minStar_,std::string maxStar_);
    std::vector<Hotel*> applyFilter(std::vector<Hotel*> hotels);
private:
    std::string minStar;
    std::string maxStar;
};



#endif