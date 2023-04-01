#include"ConsoleHandler.hpp"
#include<iostream>
#include"StructsAndDefines.hpp"
#include"Errors.hpp"
using namespace std;



ConsoleHandler::ConsoleHandler(Utrip* utrip_){
    utrip = utrip_;
    isLoggedIn = false;
}

void ConsoleHandler::processCommand(){
    string command,commandType,line;
    while(getline(cin,line)){
        stringstream data(line);
        getline(data,commandType,' ');
        updateLogin();
        try{
            if(commandType == POST){
                parsePostOrders(data);
            }
            else if(commandType == GET){
                parseGetOrders(data);
            }
            else if(commandType == DELETE){
                parseDeleteOreders(data);
            }
            else{
                throw BadRequest();
            }
        }
        catch(PermissionDenied& ex){
            cout<<ex.what();
        }
        catch(BadRequest& ex){
            cout<<ex.what();
        }
        catch(NotFound& ex){
            cout<<ex.what();
        }
        catch(NotEnoughCredit& ex){
            cout<<ex.what();
        }
        catch(NotEnoughRoom & ex){
            cout<<ex.what();
        }
    }
}


void ConsoleHandler::updateLogin(){
    if(utrip->isLoggedIn()){
        isLoggedIn =true;
        return;
    }
    isLoggedIn = false;
}

void ConsoleHandler::parseDeleteOreders(stringstream& data){
    string line,command,questionMark;
    getline(data,command,' ');
    int qMark = data.str().find('?');
    if(qMark != string::npos)
        getline(data,questionMark,' '); 
    if(!isLoggedIn)
        throw PermissionDenied();
    if(command == RESERVES)
        deleteReservation(data);
    else if(command == FILTERS)
        utrip->deleteFilters();
    else 
        throw NotFound();

}

void ConsoleHandler::deleteReservation(stringstream& data){
    int qmark = data.str().find("?");
    if(qmark == string::npos){
        throw BadRequest();
    }
    vector<string> argType {ID};
    Arguments arguments = parseInput(data,argType);
    if(isValid(arguments)){
        utrip->deleteReservation(arguments);
        cout<<SUCCESSFUL<<endl;
    }
    
}
void ConsoleHandler::parsePostOrders(stringstream& data){
    string line,command,questionMark;
    getline(data,command,' ');
    int qMark = data.str().find('?');
    if(qMark != string::npos)
        getline(data,questionMark,' '); 
    if(command == SIGNUP){
        signup(data);
        return;
    }
    else if(command == LOGIN){
        login(data);
        return;
    }
    if(!isLoggedIn)
        throw PermissionDenied();
    if(!isInOrder(command,data))
        return;
    if(command == LOGOUT)
        logout();
    else if(command == WALLET)
        addMoney(data);
    else if(command == RESERVES)
        reserve(data);
    else if(command == COMMENTS)
        postComment(data);
    else if(command == FILTERS)
        postFilter(data);
    else if(command == RATINGS)
        postRating(data);
    else 
        throw NotFound();
    
}

void ConsoleHandler::logout(){
    if(isLoggedIn){
        utrip->logoutUser();
        cout<<SUCCESSFUL<<endl;
    }
} 

void ConsoleHandler::parseGetOrders(stringstream& data){
    string line,command,questionMark;
    getline(data,command,' ');
    if(!isInOrder(command,data))
        return;
    int qMark = data.str().find('?');
    if(qMark != string::npos)
        getline(data,questionMark,' '); 
    if(!isLoggedIn)
        throw PermissionDenied();
    if(command == WALLET)
        showWallet(data);
    else if(command == HOTELS)
        showHotels(data,qMark);
    else if(command == RESERVES)
        utrip->showReservations();
    else if(command == COMMENTS)
        showComments(data);
    else if(command == RATINGS)
        getRating(data);
    else 
        throw NotFound();
    
}

bool ConsoleHandler::isInOrder(string command,stringstream& data){
    if((command == WALLET) || (command == RATINGS) || (command == COMMENTS)||(command == FILTERS)){
        int qmark = data.str().find("?");
        if(qmark == string::npos){
            throw BadRequest();
        }
    }
    return true;
}


void ConsoleHandler::getRating(stringstream& data){
    Arguments arguments = parseInput(data,getGetArgumentTypes(RATINGS));
    if(isValid(arguments)){
        utrip->showRating(arguments);
    }
}
void ConsoleHandler::postRating(stringstream& data){
    Arguments arguments = parseInput(data,getPostArgumentTypes(RATINGS));
    if(isValid(arguments)){
        utrip->addRating(arguments);
        cout<<SUCCESSFUL<<endl;
    }
}

void ConsoleHandler::postFilter(stringstream& info){
    string word,type,filter;
    getline(info,type);
    stringstream data(type),ss(type);
    getline(ss,word,' ');
    if(word == CITY)
        filter = "cityFilter";
    else if((word == MIN_STAR) || (word == MAX_STAR))
        filter = "starFilter";
    else if((word == MIN_PRICE) || (word == MAX_PRICE))
        filter = "priceFilter";
    else if((word == TYPE) ||  (word == QUANTITY) || (word == CHECK_IN) || (word == CHECK_OUT))
        filter = "roomFilter";
    else throw BadRequest();
    applyFilterInType(data,filter);
}

void ConsoleHandler::applyFilterInType(stringstream& data,string type){
    Arguments arguments = parseInput(data,getPostArgumentTypes(type));
    if(isValid(arguments)){
        utrip->applyFilter(getFilterType(type),arguments);
        cout<<SUCCESSFUL<<endl;
    }
}

void ConsoleHandler::showComments(stringstream& data){
    Arguments arguments = parseInput(data,getGetArgumentTypes(COMMENTS));
    if(isValid(arguments)){
        utrip->showComments(arguments[HOTEL]);
    }
}

void ConsoleHandler::showWallet(stringstream& data){
    Arguments arguments = parseInput(data,getGetArgumentTypes(WALLET));
    if(isValid(arguments)){
        utrip->showBankStatement(stoi(arguments[COUNT].c_str()));
    }
}
void ConsoleHandler::postComment(stringstream& data){
   
    Arguments arguments = parseInput(data,getPostArgumentTypes(COMMENTS));
    if(isValid(arguments)){
        utrip->addComment(arguments[HOTEL],arguments[COMMENT]);
        cout<<SUCCESSFUL<<endl;
    }
}

void ConsoleHandler::showHotels(stringstream& data,int& qMark){
    int x = data.str().find(ID);
    int qmark = data.str().find("?");
    if(qmark != string::npos){
        if(x != string::npos){
        Arguments arguments = parseInput(data,getGetArgumentTypes(HOTELS));
            if(isValid(arguments)){
                utrip->showHotelInfo(arguments[ID]);
            }
            return;
        }
        throw BadRequest();
    }
    else {
        utrip->showHotelsInShort();
    }
}

void ConsoleHandler::signup(stringstream& data){
    if(isLoggedIn){
        throw BadRequest();
        return;
    }
    int qmark = data.str().find("?");
    if(qmark == string::npos){
        throw BadRequest();
    }
    Arguments arguments = parseInput(data,getPostArgumentTypes(SIGNUP));
    if(isValid(arguments)){
        if(utrip->isUnique(arguments)){
            utrip->signup(arguments);
            cout<<SUCCESSFUL<<endl;
        }
    }
}

void ConsoleHandler::login(stringstream& data){
    if(isLoggedIn){
        throw BadRequest();
        return;
    }
    int qmark = data.str().find("?");
    if(qmark == string::npos){
        throw BadRequest();
    }
    Arguments arguments = parseInput(data,getPostArgumentTypes(LOGIN));
    if(!isValid(arguments)){
        return;
    }
    utrip->login(arguments);
}

void ConsoleHandler::reserve(stringstream& data){
    int qmark = data.str().find("?");
    if(qmark == string::npos){
        throw BadRequest();
    }
    Arguments arguments = parseInput(data,getPostArgumentTypes(RESERVES));
    if(isValid(arguments)){
        struct Duration duration;
        duration.checkIn = stoi(arguments[CHECK_IN].c_str());
        duration.checkOut = stoi(arguments[CHECK_OUT].c_str());
        utrip->reserve(arguments[HOTEL],getType(arguments[TYPE]),stoi(arguments[QUANTITY].c_str()),duration);  
    }
}

void ConsoleHandler::addMoney(stringstream& data){
    Arguments arguments = parseInput(data,getPostArgumentTypes(WALLET));
    if(isValid(arguments)){
        if(stod(arguments[AMOUNT].c_str()) <= 0){
        throw BadRequest();
        }
        utrip->purchase(add,stod(arguments[AMOUNT].c_str()));
    }
}

vector<string> ConsoleHandler::getPostArgumentTypes(string command){
    if(command == SIGNUP){
        vector<string> arguments {EMAIL,PASSWORD,USERNAME};
        return arguments;
    }
    else if(command == LOGIN){
        vector<string> arguments {EMAIL,PASSWORD};
        return arguments;
    }
    else if(command == WALLET){
        vector<string> arguments { AMOUNT };
        return arguments;
    }
    else if(command == RESERVES){
        vector<string> arguments { HOTEL,TYPE,QUANTITY,CHECK_IN,CHECK_OUT };
        return arguments;
    }
    else if (command == COMMENTS){
        vector<string> arguments { HOTEL,COMMENT };
        return arguments;
    }
    else if (command == "cityFilter"){
        vector<string> arguments { CITY};
        return arguments;
    }
    else if(command == "starFilter"){
        vector<string> arguments { MIN_STAR,MAX_STAR};
        return arguments;
    }
    else if(command == "priceFilter"){
        vector<string> arguments { MIN_PRICE,MAX_PRICE};
        return arguments;
    }
    else if(command == "roomFilter"){
        vector<string> arguments { TYPE,QUANTITY,CHECK_IN,CHECK_OUT};
        return arguments;
    }
    else if(command == RATINGS){
        vector<string> arguments { HOTEL,LOCATION,CLEANLINESS,STAFF,FACILITIES,VALUE_FOR_MONEY,OVERALL_RATING};
        return arguments;
    }
}

vector<string> ConsoleHandler::getGetArgumentTypes(string command){
    if(command == WALLET){
        vector<string> arguments {COUNT};
        return arguments;
    }
    if(command == HOTELS){
        vector<string> arguments {ID};
        return arguments;
    }
    if(command == COMMENTS){
        vector<string> arguments {HOTEL};
        return arguments;
    }
    if(command == RATINGS){
        vector<string> arguments {HOTEL};
        return arguments;
    }
}

Arguments ConsoleHandler::parseInput(stringstream& data,vector<string> types){
    Arguments arguments;
    string type,arg="";
    int size = types.size();
    for(int i=0;i<types.size();i++){
        arguments[types[i]] = "";
    }
    for(int i = 0;i<size;i++){
        getline(data,type,' ');
        for(int j = 0 ; j < size ; j++){
            if(type == types[j]){
                if(type == CITY){
                    getline(data,arg);
                    arguments[type] = arg;
                    return arguments;
                }
                getline(data,arg,' ');
                arguments[type] = arg; 
            }
        }
    }

    return arguments;

}

bool ConsoleHandler::isValid(Arguments info){
    for(auto it : info){
        if(it.second == ""){
            throw BadRequest();
            return false;
        }
    }
    return true;
}