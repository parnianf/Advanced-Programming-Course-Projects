#ifndef INVALIDID_H
#define INVALIDID_H "INVALIDID_H"

#include <string>
#include <vector>
#include <exception>

class InvalidId : public std::exception
{
public:
    virtual const char *what() const throw();
};

#endif