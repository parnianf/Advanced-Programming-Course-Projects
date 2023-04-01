#include"Errors.hpp"
#include"StructsAndDefines.hpp"


const char* BadRequest::what() const noexcept {
    return BAD_REQUEST_ERROR; 
}


const char* NotFound::what() const noexcept  {
    return NOT_FOUND_ERROR;
}

const char* PermissionDenied::what() const noexcept  {
    return PERMISSION_DENIED_ERROR;
}


const char* NotEnoughRoom::what()const noexcept  {
    return NOT_ENOUGH_ROOM_ERROR;
}


const char* NotEnoughCredit::what()const noexcept {
    return NOT_ENOUGH_CREDIT_ERROR;
}


const char* InsufficientRating::what()const noexcept  {
    return INSUFFICIENT_RATING_ERROR;
}