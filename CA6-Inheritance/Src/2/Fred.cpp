#include "Fred.hpp"

#include <iostream>
using namespace std;
#define HI "Hi"
#define HELLO "Hello"
Fred::Fred(Channel *channel_)
{
    channel = channel_;
}

void Fred::update(string message)
{
    if (message == HI)
    {
        channel->setMessage(HELLO);
    }
}