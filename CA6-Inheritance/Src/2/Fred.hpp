#ifndef FRED_H
#define FRED_H "FRED_H"

#include "Robot.hpp"
#include "Channel.hpp"
class Fred : public Robot
{
public:
    Fred(Channel *channel_);
    void update(std::string message);

private:
    Channel *channel;
};

#endif