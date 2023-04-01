#include"Sort.hpp"
#include"User.hpp"
#include<algorithm>
#include<iostream>

using namespace std;

vector<Hotel*> Sort::sortInOrder(vector<Hotel*> hotels,std::string property,std::string order_){

    Order order = order_ == ASCENDING ? AscendingOrd : DescendingOrd;
    if(property == ID)
        return sortById(hotels,order);
}


vector<Hotel*> Sort::sortById(vector<Hotel*> hotels,Order order){
    sort(hotels.begin(),hotels.end(),[order](Hotel* hotel1,Hotel* hotel2){ 
        if(order == DescendingOrd)
            return hotel1->getId() > hotel2->getId();
        if(order == AscendingOrd)
            return hotel1->getId() < hotel2->getId(); });
    return hotels;
}

