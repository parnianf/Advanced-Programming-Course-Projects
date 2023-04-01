#ifndef CHANNEL_H
#define CHANNEL_H "CHANNEL_H"
#include <vector>
#include <string>
#include "Robot.hpp"

class Channel
{
public:
    Channel(std::string name_);
    std::string getName();
    void setMessage(std::string message_);
    void notify(std::string message);
    void setRegisteredRobots(Robot *newRobot);

private:
    std::string name;
    std::vector<Robot *> robots;
};

#endif