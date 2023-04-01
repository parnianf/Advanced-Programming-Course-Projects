#include "Observer.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "DuplicateName.hpp"
#include "InvalidChannel.hpp"
#include "SameName.hpp"
using namespace std;

#define ADD_CHANNEL "add_channel"
#define TELL "tell"
#define ADD_BOT "add_bot"
#define ECHO "echo"
#define LOGGER "logger"
#define FRED "fred"
#define LIBRARIAN "librarian"

void Observer::addChannel()
{
    string name;
    cin >> name;
    if (channels.size() != 0)
    {
        if (findChannelByName(name))
        {
            throw DuplicateName();
        }
    }
    Channel *channel = new Channel(name);
    channels.push_back(channel);
}

void Observer::tellChannel()
{
    string channelName, message;
    cin >> channelName;
    if (!findChannelByName(channelName))
    {
        throw InvalidChannel();
    }
    getline(cin, message);
    message = message.substr(1);
    Channel *channel = findChannelByName(channelName);
    channel->setMessage(message);
}

void Observer::addEcho()
{
    string srcChannelName, dstChannelName;
    cin >> srcChannelName >> dstChannelName;
    if (srcChannelName == dstChannelName)
    {
        throw SameName();
    }
    if ((!findChannelByName(srcChannelName)) || (!findChannelByName(dstChannelName)))
    {
        throw InvalidChannel();
    }
    Channel *srcChannel = findChannelByName(srcChannelName);
    Channel *dstChannel = findChannelByName(dstChannelName);
    Echo *echo = new Echo(srcChannel, dstChannel);
    srcChannel->setRegisteredRobots(echo);
}

void Observer::addLogger()
{
    string fileName;
    cin >> fileName;
    Logger *logger = new Logger(fileName, channels);
    for (int i = 0; i < channels.size(); i++)
    {
        channels[i]->setRegisteredRobots(logger);
    }
}

void Observer::addFred()
{
    string channelName;
    cin >> channelName;
    if (!findChannelByName(channelName))
    {
        throw(InvalidChannel());
    }
    Channel *channel = findChannelByName(channelName);
    Fred *fred = new Fred(channel);
    channel->setRegisteredRobots(fred);
}
void Observer::addLibrarian()
{
    string channelName;
    cin >> channelName;
    if (!findChannelByName(channelName))
    {
        throw InvalidChannel();
    }
    Channel *channel = findChannelByName(channelName);
    Librarian *librarian = new Librarian(channel);
    channel->setRegisteredRobots(librarian);
}

void Observer::processCommand()
{

    string command;
    while (cin >> command)
    {
        if (command == ADD_CHANNEL)
        {
            try
            {
                addChannel();
            }
            catch (DuplicateName &ex)
            {
                cerr << ex.what();
            }
        }
        else if (command == TELL)
        {
            try
            {
                tellChannel();
            }
            catch (InvalidChannel &ex)
            {
                cerr << ex.what();
            }
        }
        else if (command == ADD_BOT)
        {
            string type;
            cin >> type;
            if (type == ECHO)
            {
                try
                {
                    addEcho();
                }
                catch (SameName &ex)
                {
                    cerr << ex.what();
                }
                catch (InvalidChannel &ex)
                {
                    cerr << ex.what();
                }
            }

            if (type == LOGGER)
            {
                addLogger();
            }

            if (type == FRED)
            {
                try
                {
                    addFred();
                }
                catch (InvalidChannel &ex)
                {
                    cerr << ex.what();
                }
            }
            if (type == LIBRARIAN)
            {
                try
                {
                    addLibrarian();
                }
                catch (InvalidChannel &ex)
                {
                    cerr << ex.what();
                }
            }
        }
    }
}

Channel *Observer::findChannelByName(string name)
{
    for (int i = 0; i < channels.size(); i++)
    {
        if (channels[i]->getName() == name)
        {
            return channels[i];
        }
    }
    return NULL;
}
