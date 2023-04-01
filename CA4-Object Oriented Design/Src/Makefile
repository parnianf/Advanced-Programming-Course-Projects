CC=g++ -std=c++11

all: Goodreads.out

Goodreads.out: main.o GoodReads.o functions.o Author.o Book.o Review.o User.o
	${CC} -o Goodreads.out main.o GoodReads.o functions.o Author.o Book.o Review.o User.o

main.o: main.cpp GoodReads.hpp
	${CC} -c main.cpp

GoodReads.o: GoodReads.cpp GoodReads.hpp User.hpp Book.hpp functions.hpp Review.hpp
	${CC} -c GoodReads.cpp

User.o: User.cpp User.hpp Book.hpp Review.hpp
	${CC} -c User.cpp

Author.o: Author.cpp Author.hpp
	${CC} -c Author.cpp

Book.o: Book.cpp Book.hpp Author.hpp Review.hpp
	${CC} -c Book.cpp

Review.o: Review.cpp Review.hpp
	${CC} -c Review.cpp

functions.o: functions.cpp functions.hpp
	${CC} -c functions.cpp
