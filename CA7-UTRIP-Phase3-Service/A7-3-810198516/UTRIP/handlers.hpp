#ifndef HOTELSERVICE_H
#define HOTELSERVICE_H "HOTELSERVICE_H"


#include "../server/server.hpp"
#include "Utrip.hpp"
#include <iostream>

using namespace std;

class ShowHotels : public RequestHandler {
public:
	ShowHotels(Utrip* utrip_) : utrip(utrip_){}
	Response *callback(Request *);
private:
	Utrip* utrip;
};


class ShowHotelDetals : public RequestHandler {
public:
	ShowHotelDetals(Utrip* utrip_) : utrip(utrip_){}
	Response *callback(Request *);
private:
	Utrip* utrip;
};


class ShowWallet : public RequestHandler {
public:
	ShowWallet(Utrip* utrip_) : utrip(utrip_){}
	Response *callback(Request *);
private:
	Utrip* utrip;
};


class Deposit : public RequestHandler {
public:
	Deposit(Utrip* utrip_) : utrip(utrip_){}
	Response *callback(Request *);
private:
	Utrip* utrip;
};


class CreateAccount : public RequestHandler {
public:
	CreateAccount(Utrip* utrip_) : utrip(utrip_){}
	Response *callback(Request *);
private:
	Utrip* utrip;
};


class ApplyStarFilter : public RequestHandler {
public:
	ApplyStarFilter(Utrip* utrip_) : utrip(utrip_){}
	Response *callback(Request *);
private:
	Utrip* utrip;
};


class LoginUser : public RequestHandler {
public:
	LoginUser(Utrip* utrip_) : utrip(utrip_){}
	Response *callback(Request *);
private:
	Utrip* utrip;
};


class Logout : public RequestHandler {
public:
	Logout(Utrip* utrip_) : utrip(utrip_){}
	Response *callback(Request *);
private:
	Utrip* utrip;
};


#endif

