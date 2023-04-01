#ifndef SCRAMBLE_H
#define SCRAMBLE_H "SCRAMBLE_H"

#include "Enemy.hpp"
#include "rsdl.hpp"

class Scramble : public Enemy
{
public:
    Scramble();
    void draw(Window *window);
};

#endif