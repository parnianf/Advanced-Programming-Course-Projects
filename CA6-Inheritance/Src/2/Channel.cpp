#include "Channel.hpp"
#include <iostream>
#include <string>
using namespace std;

Channel::Channel(string name_)
{
    name = name_;
}
string Channel::getName()
{
    return name;
}
void Channel::setMessage(string message_)
{
    notify(message_);
}

void Channel::notify(string message)
{
    for (int i = 0; i < robots.size(); i++)
    {
        robots[i]->update(message);
    }
}

void Channel::setRegisteredRobots(Robot *newRobot)
{
    robots.push_back(newRobot);
}