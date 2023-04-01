#include "UndefinedType.hpp"

const char *UndefinedType::what() const throw()
{
    return "Undefined type.\n";
}