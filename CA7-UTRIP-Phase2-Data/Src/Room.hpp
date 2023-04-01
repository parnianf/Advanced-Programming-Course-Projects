#ifndef ROOM_H
#define ROOM_H "ROOM_H"

#include<string>
#include<vector>
#include"StructsAndDefines.hpp"


typedef double (*operation)(double,double);
typedef std::map<std::string,std::string> Arguments;



class Room{
public:

    Room(std::string roomId_,RoomType type_);
    bool isEmpty(Duration d);
    std::string getId();
    RoomType getType();
    void addReservation(Duration newResTime);
    void deleteDuration(Duration duration);

private:

    bool doesOverlap(Duration d1,Duration d2);
    RoomType type;
    std::string roomId;
    std::vector<Duration> reservationTimeTable;
};


#endif