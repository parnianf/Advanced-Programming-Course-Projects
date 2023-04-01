#ifndef FUNCTIONS_H
#define FUNCTIONS_H "FUNCTIONS_H"
#include"StructsAndDefines.hpp"
#include"Hotel.hpp"
#include<string>

double add(double a,double b);
double sub(double a,double b);
RoomType getType(std::string type);
FilterType getFilterType(std::string type);
bool comparator(Hotel* hotelA,Hotel* hotelB);
double calculatePwrtwo(double p ,double q);
std::string truncate(double number);

#endif