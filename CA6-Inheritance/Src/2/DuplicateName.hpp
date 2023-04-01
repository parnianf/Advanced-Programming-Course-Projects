#ifndef DUPLICATE_NAME
#define DUPLICATE_NAME "DUPLICATE_NAME"
#include<exception>

class DuplicateName : public std::exception{

public:
    const char* what();
};


#endif