#ifndef LOGGER_H
#define LOGGER_H "LOGGER_H"
#include <vector>
#include <string>
#include <fstream>
#include "Channel.hpp"
#include "Robot.hpp"

class Logger : public Robot
{
public:
    Logger(std::string fileName, std::vector<Channel *> channels_);
    void update(std::string message);

private:
    std::fstream outputFile;
    std::vector<Channel *> channels;
    std::vector<std::string> messages;
    std::string fileName;
};

#endif