CC=g++ -std=c++11


all: utrip.out

utrip.out: main.o Room.o StructsAndDefines.o Reserve.o Hotel.o Filter.o User.o Functions.o CVSReader.o Utrip.o ConsoleHandler.o Errors.o Rating.o Sort.o
	${CC} -o utrip.out main.o Room.o StructsAndDefines.o Reserve.o Hotel.o Filter.o User.o Functions.o CVSReader.o Utrip.o ConsoleHandler.o Errors.o Rating.o Sort.o

main.o: main.cpp CVSReader.hpp Utrip.hpp ConsoleHandler.hpp
	${CC} -c main.cpp

Room.o: Room.cpp Room.hpp StructsAndDefines.hpp
	${CC} -c Room.cpp

StructsAndDefines.o: StructsAndDefines.cpp StructsAndDefines.hpp Rating.hpp
	${CC} -c StructsAndDefines.cpp

Reserve.o: Reserve.cpp Reserve.hpp StructsAndDefines.hpp Room.hpp
	${CC} -c Reserve.cpp

Hotel.o: Hotel.cpp Hotel.hpp Reserve.hpp Room.hpp StructsAndDefines.hpp User.hpp
	${CC} -c Hotel.cpp

Filter.o: Filter.hpp Filter.cpp Hotel.hpp StructsAndDefines.hpp
	${CC} -c Filter.cpp

User.o: User.cpp User.hpp Filter.hpp StructsAndDefines.hpp Reserve.hpp Functions.hpp
	${CC} -c User.cpp

Functions.o: Functions.cpp Functions.hpp Hotel.hpp StructsAndDefines.hpp
	${CC} -c Functions.cpp

CVSReader.o: CVSReader.cpp CVSReader.hpp StructsAndDefines.hpp Room.hpp Hotel.hpp
	${CC} -c CVSReader.cpp

Utrip.o: Utrip.cpp Utrip.hpp Functions.hpp StructsAndDefines.hpp Room.hpp Hotel.hpp Reserve.hpp Rating.hpp Sort.hpp
	${CC} -c Utrip.cpp

ConsoleHandler.o: ConsoleHandler.cpp ConsoleHandler.hpp Utrip.hpp StructsAndDefines.hpp Errors.hpp
	${CC} -c ConsoleHandler.cpp

Errors.o: Errors.cpp Errors.hpp
	${CC} -c Errors.cpp

Rating.o: Rating.cpp Rating.hpp Functions.hpp StructsAndDefines.hpp
	${CC} -c Rating.cpp

Sort.o: Sort.cpp Sort.hpp User.hpp Hotel.hpp StructsAndDefines.hpp Errors.hpp
	${CC} -c Sort.cpp