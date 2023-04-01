#include"Errors.hpp"

#define BAD_REQUEST_ERROR "Bad Request\n"
#define NOT_FOUND_ERROR "Not Found\n"
#define PERMISSION_DENIED_ERROR "Permission Denied\n"
#define NOT_ENOUGH_ROOM_ERROR "Not Enough Room\n"
#define NOT_ENOUGH_CREDIT_ERROR "Not Enough Credit\n"



const char* BadRequest::what(){
    return BAD_REQUEST_ERROR;
}


const char* NotFound::what(){
    return NOT_FOUND_ERROR;
}

const char* PermissionDenied::what(){
    return PERMISSION_DENIED_ERROR;
}


const char* NotEnoughRoom::what(){
    return NOT_ENOUGH_ROOM_ERROR;
}


const char* NotEnoughCredit::what(){
    return NOT_ENOUGH_CREDIT_ERROR;
}