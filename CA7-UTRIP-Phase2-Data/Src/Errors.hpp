#ifndef ERRORS_H
#define ERRORS_H "ERRORS_H"

#include<exception>


class BadRequest : public std::exception{

public:
    const char* what() const noexcept override;
};

class NotFound : public std::exception{

public:
    const char* what() const noexcept override;
};

class PermissionDenied : public std::exception{

public:
    const char* what() const noexcept override;
};

class NotEnoughRoom : public std::exception{

public:
    const char* what() const noexcept override;
};

class NotEnoughCredit : public std::exception{

public:
    const char* what() const noexcept override;
};

class InsufficientRating : public std::exception{
public:
    const char* what() const noexcept override;
};



#endif