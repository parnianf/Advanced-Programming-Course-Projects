#ifndef CVSREADER_H
#define CVSREADER_H "CVSREADER_H"


#include"Hotel.hpp"
#include<string>
#include<vector>
#include"StructsAndDefines.hpp"
#include"Room.hpp"
#include<sstream>
#include<fstream>

class CVSReader{
public:

    std::vector<Hotel*> readHotelData(std::string filePath);

private:

    Hotel* parseHotelInfo(std::vector<std::string> information);
    std::vector<RoomInfo> getRoomsInfo(std::vector<std::string> information);
    Rooms getHotelRooms(std::vector<std::string> information);
};

#endif