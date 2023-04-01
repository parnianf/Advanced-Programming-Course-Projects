#include"User.hpp"
#include"Filter.hpp"
#include"Reserve.hpp"
#include"Functions.hpp"
#include"StructsAndDefines.hpp"
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>
#include<iomanip>
#include<numeric>
#include<cmath>

using namespace std;

User::User(string username_,string password_,string email_){
    username = username_;
    password = password_;
    email = email_;
    wallet.amount = 0;
    wallet.bankStatement.push_back(0);
    reservationId = 0;
    isPriceFilterOn = true;
}

string User::getUsername(){
    return username;
}

bool User::doesExist(string email_,string password_){
    if((email == email_) && (password == password_))
        return true;
    return false;
}


bool User::isEqual(string username_,string email_){
    if( (username == username_) || (email == email_)){
        return true;
    }
    return false;
}



void User::deleteFilters(){
    filters.clear();

}


void User::purchase(operation op,double amount_){
    wallet.amount = op(wallet.amount,amount_);
    wallet.bankStatement.push_back(wallet.amount);
}


void User::applyFilter(FilterType type,Arguments data){
    StarCriterion* star = new StarCriterion(data[MIN_STAR],data[MAX_STAR]);
    filters[StarF] = star;
}


vector<Hotel*> User::getfilteredHotels(vector<Hotel*> hotels){
    vector<Hotel*> h1 = hotels,h2;
    for(auto it : filters){
        h2 = it.second->applyFilter(h1);
        h1 = h2;
    }
    return h1;
}

