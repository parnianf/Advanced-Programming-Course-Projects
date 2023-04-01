#ifndef LIBRARIAN_H
#define LIBRARIAN_H "LIBRARIAN_H"

#include "Robot.hpp"
#include "Channel.hpp"

class Librarian : public Robot
{
public:
    void update(std::string message);
    Librarian(Channel *channel_);

private:
    Channel *channel;
    int messageNumbers;
};

#endif