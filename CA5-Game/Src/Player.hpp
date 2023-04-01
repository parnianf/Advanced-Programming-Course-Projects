#ifndef PLAYER_H
#define PLAYER_H "PLAYER_H"

#include"rsdl.hpp"

class Player{
public: 

Player();
int getHearts();
int getMoney();
void decreaseHealth(int health_);
void increaseMoney(int money_);
void decreaseMoney(int money_);
void draw(Window* window);

private:
int health;
int money;
};
#endif
