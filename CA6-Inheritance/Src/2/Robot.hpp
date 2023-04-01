#ifndef ROBOT_H
#define ROBOT_H "ROBOT_H"

#include <string>

class Robot
{
public:
    virtual void update(std::string message) = 0;
};

#endif