#include"StructsAndDefines.hpp"


bool Duration::operator==(const Duration& d){
    return ((checkIn == d.checkIn) && (checkOut == d.checkOut));
}
