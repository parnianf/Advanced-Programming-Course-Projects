#include"Utrip.hpp"
#include"CVSReader.hpp"
#include"handlers.hpp"
#include "../server/server.hpp"
#include<iostream>


using namespace std;


int main(int argc, char *argv[]){
    try {

        Server server(8080);
        Utrip utrip(argv[1]);

        server.get("/home", new ShowHotels(&utrip));
        server.get("/hotelDetails", new ShowHotelDetals(&utrip));
        server.get("/showWallet", new ShowWallet(&utrip));
        server.get("/logout", new Logout(&utrip));
        server.get("/login", new ShowPage("loginForm.html"));
        server.get("/", new ShowPage("signup.html"));
        server.get("/repeatedEmail", new ShowPage("repeatedEmail.html"));
        server.get("/repeatedUsername", new ShowPage("repeatedUsername.html"));
        server.get("/passwordError", new ShowPage("passwordError.html"));
        server.get("/starRangeError", new ShowPage("starRangeError.html"));
        server.get("/loginError", new ShowPage("loginError.html"));
        server.get("/permissionDeniedError", new ShowPage("permissionDeniedError.html"));
        server.get("/showSuccessInSignup", new ShowPage("showSuccessInSignup.html"));
        server.get("/showSuccessInDeposit", new ShowPage("showSuccessInDeposit.html"));
        
        server.post("/", new ShowPage("signup.html"));
        server.post("/login", new ShowPage("loginForm.html"));
        server.post("/home", new ShowHotels(&utrip));
        server.post("/showWallet", new ShowWallet(&utrip));
        server.post("/deposit", new Deposit(&utrip));
        server.post("/logout", new Logout(&utrip));
        server.post("/createAccount", new CreateAccount(&utrip));
        server.post("/applyStarFilter",new ApplyStarFilter(&utrip));
        server.post("/loginUser", new LoginUser(&utrip));

        server.run();
    } catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
}
