#ifndef INVALIDCHANNEL_H
#define INVALIDCHANNEL_H "INVALIDCHANNEL_H"
#include <exception>

class InvalidChannel : public std::exception
{
public:
    const char *what();
};

#endif