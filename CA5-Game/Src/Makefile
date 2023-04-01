CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: FieldRunners.out

FieldRunners.out: game.o rsdl.o Enemy.o TheRunner.o StubbornRunner.o SuperTrooper.o Scramble.o Bullet.o Functions.o Tower.o Gatling.o Missile.o Tesla.o Player.o FieldRunners.o Glue.o
	$(CC) game.o rsdl.o Enemy.o TheRunner.o StubbornRunner.o SuperTrooper.o Scramble.o Bullet.o Functions.o Tower.o Gatling.o Missile.o Tesla.o Player.o FieldRunners.o Glue.o $(CCFLAGS) -o FieldRunners.out

game.o: rsdl.hpp game.cpp Enemy.hpp
	$(CC) -c game.cpp -o game.o

FieldRunners.o: rsdl.hpp FieldRunners.cpp FieldRunners.hpp Functions.hpp Tower.hpp Tesla.hpp Gatling.hpp Missile.hpp Enemy.hpp Scramble.hpp StubbornRunner.hpp SuperTrooper.hpp TheRunner.hpp Player.hpp
	$(CC) -c FieldRunners.cpp -o FieldRunners.o


Enemy.o: Enemy.hpp Enemy.cpp rsdl.hpp
	$(CC) -c Enemy.cpp -o Enemy.o

TheRunner.o: TheRunner.cpp TheRunner.hpp Enemy.hpp
	$(CC) -c TheRunner.cpp -o TheRunner.o

StubbornRunner.o: StubbornRunner.hpp StubbornRunner.cpp Enemy.hpp
	$(CC) -c StubbornRunner.cpp -o StubbornRunner.o

SuperTrooper.o: SuperTrooper.cpp SuperTrooper.hpp Enemy.hpp
	$(CC) -c SuperTrooper.cpp -o SuperTrooper.o

Scramble.o: Scramble.cpp Scramble.hpp Enemy.hpp
	$(CC) -c Scramble.cpp -o Scramble.o

Bullet.o: Bullet.cpp Bullet.hpp
	$(CC) -c Bullet.cpp -o Bullet.o

Functions.o: Functions.cpp Functions.hpp
	$(CC) -c Functions.cpp -o Functions.o

Tower.o: Tower.cpp Tower.hpp Functions.hpp Bullet.hpp Enemy.hpp
	$(CC) -c Tower.cpp -o Tower.o

Gatling.o: Gatling.cpp Gatling.hpp Functions.hpp Tower.hpp 
	$(CC) -c Gatling.cpp -o Gatling.o

Missile.o: Missile.cpp Missile.hpp Functions.hpp Tower.hpp
	$(CC) -c Missile.cpp -o Missile.o

Tesla.o: Tesla.cpp Tesla.hpp Functions.hpp Tower.hpp
	$(CC) -c Tesla.cpp -o Tesla.o

Glue.o: Glue.cpp Glue.hpp Functions.hpp Tower.hpp Enemy.hpp
	$(CC) -c Glue.cpp -o Glue.o

Player.o: Player.cpp Player.hpp
	$(CC) -c Player.cpp -o Player.o

rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp -o rsdl.o

.PHONY: clean
clean: 
	rm -r *.o