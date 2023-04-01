#ifndef SAMENAME_H
#define SAMENAME_H "SAMENAME_H"

#include <exception>

#define SAMENAMEERROR "Source and destination cannot be the same channel\n"

class SameName : public std::exception
{
public:
    const char *what();
};

#endif