#include"CVSReader.hpp"
#include<iostream>
#include"Room.hpp"

using namespace std;

vector<Hotel*> CVSReader::readHotelData(string filePath){
    string word, line;
    vector<Hotel*> hotels;
    ifstream inputFile(filePath);
    if (!inputFile)
        cout << "could not open the file" << endl;
    stringstream fileInfo;
    fileInfo << inputFile.rdbuf();
    getline(fileInfo, line);
    while (getline(fileInfo, line)){
        stringstream lineInfo(line);
        vector<string> information;
        while (getline(lineInfo, word,',')){
            information.push_back(word);
        }
        hotels.push_back(parseHotelInfo(information));
    }
    return hotels;
}


map<string,Rating> CVSReader::readRatingData(string filePath){

    string word, line;
    map<string,Rating> hotelRatings;
    ifstream ratingFile(filePath);
    if (!ratingFile)
        cout << "could not open the file" << endl;
    stringstream fileInfo;
    fileInfo << ratingFile.rdbuf();
    getline(fileInfo, line);
    while (getline(fileInfo, line)){
        stringstream lineInfo(line);
        vector<string> information;
        while (getline(lineInfo, word,',')){
            information.push_back(word);
        }
        hotelRatings[information[0]] = Rating(stod(information[1].c_str()),stod(information[2].c_str()),stod(information[3].c_str()),stod(information[4].c_str()),stod(information[5].c_str()),stod(information[6].c_str()));
    }
    return hotelRatings;
}


Hotel* CVSReader::parseHotelInfo(vector<string> information){
    struct HotelInfo hotelInfo;
    hotelInfo.uniqueId = information[0];
    hotelInfo.name = information[1];
    hotelInfo.star = information[2];
    hotelInfo.overview = information[3];
    hotelInfo.amenities = information[4];
    struct Place place;
    place.city = information[5];
    place.latitude = information[6];
    place.longitude = information[7];
    hotelInfo.imageUrl = information[8];
    Rooms rooms = getHotelRooms(information);
    vector<RoomInfo> roomsInfo = getRoomsInfo(information);
    Hotel* newHotel = new Hotel(hotelInfo,place,rooms,roomsInfo);
    return newHotel;
}

vector<RoomInfo> CVSReader::getRoomsInfo(vector<string> information){
    vector<RoomInfo> roomsInfo;
    for(int i=13;i<17;i++){
        RoomInfo roomInfo;
        int quantity = stoi(information[i-4].c_str());
        roomInfo.quantity = quantity;
        roomInfo.price = stod(information[i].c_str());
        switch(i-13){
            case Standard:
                roomInfo.type = Standard;
                break;
            case Deluxe:
                roomInfo.type = Deluxe;
                break;
            case Luxury:
                roomInfo.type = Luxury;
                break;
            case Premium:
                roomInfo.type = Premium;
                break;
        }
        roomsInfo.push_back(roomInfo);
    }
    return roomsInfo;
}

Rooms CVSReader::getHotelRooms(vector<string> information){
    char charId[] = {STANDARD_ROOM_ID,DELUXE_ROOM_ID,LUXURY_ROOM_ID,PREMIUM_ROOM_ID};
    Rooms rooms;
    for(int i=0;i<4;i++){   
        int number = stoi(information[i+9].c_str());
        for(int j=0; j < number ;j++){
            stringstream idString;
            idString<<charId[i]<<j+1;
            if(i+9 == 9){
                Room* newRoom = new Room(idString.str(),Standard);
                rooms.push_back(newRoom);
            }
            else if(i+9 == 10){
                Room* newRoom = new Room(idString.str(),Deluxe);
                rooms.push_back(newRoom);
            }
            else if(i+9 == 11){
                Room* newRoom = new Room(idString.str(),Luxury);
                rooms.push_back(newRoom);
            }
            else if(i+9 == 12){
                Room* newRoom = new Room(idString.str(),Premium);
                rooms.push_back(newRoom);
            }
        }
    }
    return rooms;
}

