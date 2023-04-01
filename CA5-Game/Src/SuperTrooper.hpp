#ifndef SUPERTROOPPER_H
#define SUPERTROOPPER_H "SUPERTROOPPER_H"

#include "Enemy.hpp"
#include "rsdl.hpp"

class SuperTrooper : public Enemy
{
public:
    SuperTrooper();
    void draw(Window *window);
};
#endif