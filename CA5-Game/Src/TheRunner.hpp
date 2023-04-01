#ifndef THERUNNER_H
#define THERUNNER_H "THERUNNER_H"

#include "rsdl.hpp"
#include "Enemy.hpp"

class TheRunner : public Enemy
{
public:
    TheRunner();
    void draw(Window *window);

};
#endif
