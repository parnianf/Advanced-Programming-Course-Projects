#include "InvalidId.hpp"

#define INVALID_ID "Invalid id.\n"
const char *InvalidId::what() const throw()
{
    return INVALID_ID;
};