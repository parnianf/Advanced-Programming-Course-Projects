CC=g++ -std=c++11


all: 2.out

2.out: main.o Channel.o Robot.o Echo.o Fred.o Logger.o Librarian.o Observer.o DuplicateName.o InvalidChannel.o SameName.o
	${CC} -o 2.out main.o Channel.o Robot.o Echo.o Fred.o Logger.o Librarian.o Observer.o DuplicateName.o InvalidChannel.o SameName.o

main.o: main.cpp Observer.hpp
	${CC} -c main.cpp

Observer.o: Observer.cpp Observer.hpp Channel.hpp Robot.hpp Echo.hpp Fred.hpp Logger.hpp Librarian.hpp DuplicateName.hpp InvalidChannel.hpp SameName.hpp
	${CC} -c Observer.cpp

Channel.o: Channel.cpp Channel.hpp Robot.hpp
	${CC} -c Channel.cpp

Robot.o: Robot.hpp Robot.cpp
	${CC} -c Robot.cpp

Echo.o: Echo.hpp Echo.cpp Robot.hpp Channel.hpp
	${CC} -c Echo.cpp

Fred.o: Fred.cpp Fred.hpp Robot.hpp Channel.hpp
	${CC} -c Fred.cpp

Logger.o: Logger.cpp Logger.hpp Robot.hpp Channel.hpp
	${CC} -c Logger.cpp

Librarian.o: Librarian.cpp Librarian.hpp Robot.hpp Channel.hpp
	${CC} -c Librarian.cpp

DuplicateName.o: DuplicateName.cpp DuplicateName.hpp
	${CC} -c DuplicateName.cpp

InvalidChannel.o: InvalidChannel.cpp InvalidChannel.hpp
	${CC} -c InvalidChannel.cpp

SameName.o: SameName.hpp SameName.cpp
	${CC} -c SameName.cpp