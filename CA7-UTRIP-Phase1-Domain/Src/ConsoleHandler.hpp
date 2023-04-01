#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H "CONSOLEHANDLER_H"


#include<string>
#include<vector>
#include<sstream>
#include"StructsAndDefines.hpp"
#include"Utrip.hpp"
#include"Errors.hpp"

class ConsoleHandler{
    public:

        ConsoleHandler(Utrip* utrip_);
        void processCommand();

    private:

        void updateLogin();
        void parseDeleteOreders(std::stringstream& data);
        void deleteReservation(std::stringstream& data);
        void parsePostOrders(std::stringstream& data);
        void parseGetOrders(std::stringstream& data);
        void getRating(std::stringstream& data);
        void logout();
        void postRating(std::stringstream& data);
        void postFilter(std::stringstream& info);
        void applyFilterInType(std::stringstream& data,std::string type);
        void showComments(std::stringstream& data);
        void showWallet(std::stringstream& data);
        void postComment(std::stringstream& data);
        void showHotels(std::stringstream& data,int& qMark);
        void signup(std::stringstream& data);
        void login(std::stringstream& data);
        void reserve(std::stringstream& data);
        void addMoney(std::stringstream& data);
        std::vector<std::string> getPostArgumentTypes(std::string command);
        std::vector<std::string> getGetArgumentTypes(std::string command);
        Arguments parseInput(std::stringstream& data,std::vector<std::string> types);
        bool isInOrder(std::string command,std::stringstream& data);
        bool isValid(Arguments info);
        Utrip* utrip;
        bool isLoggedIn;
};


#endif