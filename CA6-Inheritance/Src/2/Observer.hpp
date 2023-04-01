#ifndef OBSERVER_H
#define OBSERVER_H "OBSERVER_H"
#include "Channel.hpp"
#include "Robot.hpp"
#include "Fred.hpp"
#include "Logger.hpp"
#include "Echo.hpp"
#include "Librarian.hpp"
#include <vector>
#include <string>

class Observer
{
public:
    void processCommand();
    void tellChannel();
    void addChannel();
    void addEcho();
    void addLogger();
    void addFred();
    void addLibrarian();

private:
    Channel *findChannelByName(std::string name);
    std::vector<Channel *> channels;
};

#endif