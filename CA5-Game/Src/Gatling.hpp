#ifndef GATLING_H
#define GATLING_H "GATLING_H"

#include "rsdl.hpp"
#include "Tower.hpp"
class Gatling : public Tower
{
public:
    Gatling(int level, Point point);
    void damageEnemy();
    void upgradeTower();
    void draw(Window *window);
};

#endif