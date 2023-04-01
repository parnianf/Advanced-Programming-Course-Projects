#include"handlers.hpp"
#include<vector>
#include<sstream>
#include "../server/server.hpp"
#include "../utils/request.hpp"
#include "../utils/response.hpp"
#include"Functions.hpp"


using namespace std;


Response *ShowHotels::callback(Request *req)
{   
    if(!utrip->isLoggedIn())
        return Response::redirect("/permissionDeniedError");
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    vector<Hotel*> allHotels = utrip->getStarFilteredHotels(req->getSessionId());
    stringstream body;
    body
        << "<html>" << endl
        << "    <head><title>Home</title>" << endl
        << "    </head>" << endl
        << "    <body>" << endl
        << "<style>"<<endl
        <<"	    h1 {text-align: center;}"<<endl
        << "</style>"<<endl

        << "	    <h1 style='background-color: #008080'> UTRIP  </h1>"<<endl

        << "<style>"<<endl
        << "h1 {" <<endl
	    << "		font-size: 50px;" <<endl
		<< "}" <<endl
		<< "p {" <<endl
	    << "		font-size: 38px;" <<endl
		<< "}	"<<endl
        << "p.one {"<<endl
		<< "	    border-style: solid;"<<endl
		<< "	    border-color: #C71585;"<<endl
		<< "	}"<<endl
        << "</style>"<<endl
        << "<p class='one'>Home</p>"<<endl

        << "<div>"<<endl
        << "<a href='/logout'>Logout</a>"<<endl
        << "    <a href='/showWallet'>    Wallet</a>"<<endl
        << "<form action='/applyStarFilter' method='post'>"<<endl 
        << "<h3>Star Range: </h3>"<<endl
        << "<label for='startStarRange'>From</label>"<<endl
        << "<select name = 'startStarRange'>"<<endl
        << "<option value = '1'>1</option>"<<endl
        << "<option value = '2'>2</option>"<<endl
        << "<option value = '3'>3</option>"<<endl
        << "<option value = '4'>4</option>"<<endl
        << "<option value = '5'>5</option>"<<endl
        <<"</select>"<<endl
        << "<label for = 'EndStarRange'>To</label>"<<endl
        << "<select name = 'EndStarRange'>"<<endl
        << "<option value = '1'>1</option>"<<endl
        << "<option value = '2'>2</option>"<<endl
        << "<option value = '3'>3</option>"<<endl
        << "<option value = '4'>4</option>"<<endl
        << "<option value = '5'>5</option>"<<endl
        << "</select>"<<endl
        << "<input type='submit' value='Submit'>" <<endl
        << "</div>"<<endl
        << "            <table border=1>" << endl
        << "                <tr>" << endl
        << "                    <th>Property Name</th>" << endl
        << "                    <th>Hotel Star Rating</th>" << endl
        << "                    <th>City</th>" << endl
        << "                    <th>Image</th>" << endl
        << "                    <th>&nbsp;</th>" << endl
        << "                </tr>" << endl;

    for (int i = 0; i < allHotels.size(); i++)
    {
        HotelInfo hotelInfo = allHotels[i]->getHotelInfo();
        body
            << "                    <tr>" << endl
            << "                        <td>" << hotelInfo.name << "</td>" << endl
            << "                        <td>" << hotelInfo.star << "</td>" << endl
            << "                        <td>" << allHotels[i]->getCity() << "</td>" << endl
            << "                        <td>" << " <img src = "<<hotelInfo.imageUrl << " width = '200px' height = '200px'></td>" << endl
            << "                        <td><a href='hotelDetails?id=" << hotelInfo.uniqueId << "'>Check Details</a></td>" << endl
            << "                    </tr>" << endl;
    }
  res->setBody(body.str());
  return res;
}


Response *ShowHotelDetals::callback(Request *req)
{   
    if(!utrip->isLoggedIn())
        return Response::redirect("/permissionDeniedError");
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    Hotel* hotel = utrip->findHotelById(req->getQueryParam("id"));
    stringstream body;
    HotelInfo hotelInfo = hotel->getHotelInfo();

    body
        << "<html>" << endl
        << "    <head><title>" << hotelInfo.name << " Detail</title>" << endl
        << "    </head>" << endl
        << "    <body>" << endl
        << "<style>"<<endl
        <<"	    h1 {text-align: center;}"<<endl
        << "</style>"<<endl

        << "	    <h1 style='background-color: #008080 '> UTRIP  </h1>"<<endl

        << "<style>"<<endl
        << "h1 {" <<endl
	    << "		font-size: 50px;" <<endl
		<< "}" <<endl
		<< "p.one {" <<endl
	    << "		font-size: 38px;" <<endl
		<< "}	"<<endl
        << "p.one {"<<endl
		<< "	    border-style: solid;"<<endl
		<< "	    border-color: #C71585;"<<endl
		<< "	}"<<endl
        << "</style>"<<endl
        << "<p class='one'>"<<hotelInfo.name<<" Details</p>"<<endl


        << "<a href='/home'>Home</a>"<<endl
        << "<a href='/logout'>Logout</a>"<<endl
        << "<p> <b>Image:</b></br>"<<endl
        << " <img src = "<<hotelInfo.imageUrl << " width = '500px' height = '500px'>" << endl
        << "</br> <b>property name: </b>" <<hotelInfo.name<<endl
        << "</br> <b>hotel overview: </b>" << hotelInfo.overview <<endl
        << "</br> <b>property amenities: </b>" << hotelInfo.amenities <<endl
        << "</br> <b>hotel star rating: </b>" << hotelInfo.star <<endl
        << "</br> <b>city:</b>" << hotel->getCity() <<endl
        << "</p><b>rooms: </b>" <<endl

        << "            <table border=1>" << endl
        << "                <tr>" << endl
        << "                    <th>Type</th>" << endl
        << "                    <th>Quantity</th>" << endl
        << "                    <th>price</th>" << endl
        << "                </tr>" << endl;
    vector<RoomInfo> roomsInfo = hotel->getRoomsInfo();
    for (int i = 0; i < roomsInfo.size(); i++)
    {
        body
            << "                    <tr>" << endl
            << "                        <td>" << getRoomTypeName(roomsInfo[i].type) << "</td>" << endl
            << "                        <td>" << roomsInfo[i].quantity << "</td>" << endl
            << "                        <td>" << roomsInfo[i].price << "</td>" << endl
            << "                    </tr>" << endl;
    }
    body
        << "</head>"<<endl
        << "</html>"<<endl;
    res->setBody(body.str());
    return res;
}


Response *ShowWallet::callback(Request *req)
{  
    if(!utrip->isLoggedIn())
        return Response::redirect("/permissionDeniedError");
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    User* user = utrip->findUserById(req->getSessionId());
    stringstream body;
    struct Wallet wallet = user->getWallet();
    body
        << "<html>" << endl
        << "    <head><title>Bank Statement</title>" << endl
        << "    </head>" << endl
        << "    <body>" << endl
        << "<style>"<<endl
        <<"	    h1 {text-align: center;}"<<endl
        << "</style>"<<endl

        << "	    <h1 style='background-color: #008080 '> UTRIP  </h1>"<<endl

        << "<style>"<<endl
        << "h1 {" <<endl
	    << "		font-size: 50px;" <<endl
		<< "}" <<endl
		<< "p {" <<endl
	    << "		font-size: 38px;" <<endl
		<< "}	"<<endl
        << "p.one {"<<endl
		<< "	    border-style: solid;"<<endl
		<< "	    border-color: #C71585;"<<endl
		<< "	}"<<endl
        << "</style>"<<endl
        << "<p class='one'>Wallet</p>"<<endl

        << "<a href='/home'>Home</a>"<<endl
        << "<a href='/logout'>Logout</a>"<<endl
        << "</br> <h2>Your Credit: </h2>" <<wallet.amount<<endl
        
        <<"<form action='deposit' method='POST'>" <<endl
        <<"<div class='container'>" <<endl
            <<"<h2>Deposit:</h2>"<< endl
            <<"<h3>Please Enter The Amount Of Money You Want To Deposit.</h3>" <<endl
            <<"<hr>" <<endl

            <<"<label for='amount'><b>Amount($)</b></label><br/>" <<endl
            <<"<input type='text' placeholder='Enter Amount' name='amount' required><br/>" <<endl

            << "    <input type='submit' value='Charge'/>" << endl
            <<"<hr>" <<endl

        << "</div>" <<endl
        << "</form>" <<endl

        << "</head>"<<endl
        << "</html>"<<endl;
    res->setBody(body.str());
    return res;
    
}


Response *Deposit::callback(Request *req)
{  
    if(!utrip->isLoggedIn())
        return Response::redirect("/permissionDeniedError");
    utrip->purchase(add,stod(req->getBodyParam("amount")),req->getSessionId());
    return Response::redirect("/showSuccessInDeposit");

}


Response *Logout::callback(Request *req)
{  
    if(!utrip->isLoggedIn())
        return Response::redirect("/permissionDeniedError");
    utrip->logoutUser(req->getSessionId());
    return Response::redirect("/login");
}


Response *LoginUser::callback(Request *req)
{  
    Arguments args;
    Response *res = new Response;
    args[PASSWORD] = req->getBodyParam("password");
    args[EMAIL] = req->getBodyParam("email");
    args[ID] = req->getSessionId();
    if(!utrip->isUserValid(req->getBodyParam("email"),req->getBodyParam("password"))){
        return Response::redirect("/loginError");
    }
    utrip->login(args);
    res = Response::redirect("/home");
    res->setSessionId(req->getSessionId());
    return res;
}


Response *CreateAccount::callback(Request *req)
{ 
    Arguments args;
    Response *res = new Response;
    if(req->getBodyParam("password") != req->getBodyParam("password-repeat")){
        return Response::redirect("/passwordError");
    }
    args[PASSWORD] = req->getBodyParam("password");
    args[USERNAME] = req->getBodyParam("username");
    args[EMAIL] = req->getBodyParam("email");
    args[ID] = req->getBodyParam("username");
    if(!utrip->isEmailUnique(req->getBodyParam("email"))){
        return Response::redirect("/repeatedUsername");
    }
    if(!utrip->isUsernameUnique(req->getBodyParam("username"))){
        return Response::redirect("/repeatedEmail");
    }
    utrip->signup(args);
    res = Response::redirect("/showSuccessInSignup");
    res->setSessionId(req->getBodyParam("username"));
    return res;
}


Response *ApplyStarFilter::callback(Request *req)
{  
    if(!utrip->isLoggedIn())
        return Response::redirect("/permissionDeniedError");
    if(stoi(req->getBodyParam("startStarRange")) > stoi(req->getBodyParam("EndStarRange")))
        return Response::redirect("/starRangeError");
    Arguments data;
    data[MIN_STAR] = req->getBodyParam("startStarRange");
    data[MAX_STAR] = req->getBodyParam("EndStarRange");
    data[ID] = req->getSessionId();
    utrip->applyFilter(StarF,data);
    return Response::redirect("/home");
    
}

