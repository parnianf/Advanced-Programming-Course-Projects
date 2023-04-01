#include "Echo.hpp"
#include <string>
#include <iostream>
using namespace std;

Echo::Echo(Channel *srcChannel_, Channel *dstChannel_)
{
    srcChannel = srcChannel_;
    dstChannel = dstChannel_;
}

void Echo::update(string message)
{

    dstChannel->setMessage(message);
}