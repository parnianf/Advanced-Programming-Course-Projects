#include "Logger.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

Logger::Logger(string fileName_, vector<Channel *> channels_)
{
    fstream outputFile(fileName_);
    fileName = fileName_;
    channels = channels_;
}

void Logger::update(string message)
{
    outputFile.open(fileName, std::ios_base::app);
    if (outputFile.is_open())
    {
        outputFile << message << '\n';
        outputFile.close();
    }
}
