#include "InvalidChannel.hpp"

#define ERROR "Channel does not exist\n"

const char *InvalidChannel::what()
{
    return ERROR;
}