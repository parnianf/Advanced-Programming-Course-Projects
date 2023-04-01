#ifndef ERRORS_H
#define ERRORS_H "ERRORS_H"

#include<exception>


class BadRequest : public std::exception{

public:
    const char* what();
};

class NotFound : public std::exception{

public:
    const char* what();
};

class PermissionDenied : public std::exception{

public:
    const char* what();
};

class NotEnoughRoom : public std::exception{

public:
    const char* what();
};

class NotEnoughCredit : public std::exception{

public:
    const char* what();
};



#endif