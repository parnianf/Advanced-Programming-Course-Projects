CC=g++ -std=c++11


all: 1.out

1.out: main.o Data.o StringData.o NumericalData.o Object.o Array.o JsonBuilder.o InvalidId.o DuplicateKey.o UndefinedType.o
	${CC} -o 1.out main.o Data.o StringData.o NumericalData.o Object.o Array.o JsonBuilder.o InvalidId.o DuplicateKey.o UndefinedType.o

main.o: main.cpp JsonBuilder.hpp
	${CC} -c main.cpp

JsonBuilder.o: JsonBuilder.cpp JsonBuilder.hpp Data.hpp NumericalData.hpp StringData.hpp Object.hpp Array.hpp InvalidId.hpp DuplicateKey.hpp UndefinedType.hpp
	${CC} -c JsonBuilder.cpp

Data.o: Data.cpp Data.hpp
	${CC} -c Data.cpp

NumericalData.o: NumericalData.cpp NumericalData.hpp Data.hpp
	${CC} -c NumericalData.cpp

StringData.o: StringData.cpp StringData.hpp Data.hpp
	${CC} -c StringData.cpp

Object.o: Object.cpp Object.hpp Data.hpp
	${CC} -c Object.cpp

Array.o: Array.cpp Array.hpp Data.hpp
	${CC} -c Array.cpp

InvalidId.o: InvalidId.cpp InvalidId.hpp
	${CC} -c InvalidId.cpp

DuplicateKey.o: DuplicateKey.cpp DuplicateKey.hpp
	${CC} -c DuplicateKey.cpp

UndefinedType.o: UndefinedType.cpp UndefinedType.hpp
	${CC} -c UndefinedType.cpp