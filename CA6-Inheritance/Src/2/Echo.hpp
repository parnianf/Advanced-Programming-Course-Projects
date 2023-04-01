#ifndef ECHO_H
#define ECHO_H "ECHO_H"
#include "Robot.hpp"
#include "Channel.hpp"
#include <vector>
class Echo : public Robot
{
public:
    Echo(Channel *srcChannel_, Channel *dstChannel_);
    void update(std::string message);

private:
    Channel *srcChannel;
    Channel *dstChannel;
};

#endif