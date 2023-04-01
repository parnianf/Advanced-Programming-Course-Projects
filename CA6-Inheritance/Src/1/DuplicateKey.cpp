#include "DuplicateKey.hpp"

#define DUPLICATE_KEY "Duplicate key.\n"
const char *DuplicateKey::what() const throw()
{
    return DUPLICATE_KEY;
}