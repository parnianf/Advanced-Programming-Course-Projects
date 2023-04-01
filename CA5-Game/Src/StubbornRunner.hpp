#ifndef STUBBORNRUNNER_H
#define STUBBORNRUNNER_H "STUBBORNRUNNER_H"

#include "Enemy.hpp"
#include "rsdl.hpp"

class StubbornRunner : public Enemy
{
public:
    StubbornRunner();
    void draw(Window *window);
};

#endif
