#include"Filter.hpp"
#include<string>
#include<vector>
#include<iostream>
using namespace std;



StarCriterion::StarCriterion(string minStar_,string maxStar_){

    minStar = minStar_;
    maxStar = maxStar_;
}

vector<Hotel*> StarCriterion::applyFilter(vector<Hotel*> hotels){
    vector<Hotel*> filteredHotels;
    for(int i=0;i<hotels.size();i++){
        for(int j = stoi(minStar.c_str()) ; j <= stoi(maxStar.c_str()) ; j++){
            if(hotels[i]->isStarTheSame(to_string(j))){
                filteredHotels.push_back(hotels[i]);
            }
        }
    }
    return filteredHotels;
}
