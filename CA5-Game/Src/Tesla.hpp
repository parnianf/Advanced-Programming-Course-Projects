#ifndef TESLA_H
#define TESLA_H "TESLA_H"
#include"rsdl.hpp"
#include"Tower.hpp"

class Tesla : public Tower{
public:
    Tesla(int level,Point point);
    virtual void damageEnemy();
    virtual void upgradeTower();
    void draw(Window* window);
};
#endif