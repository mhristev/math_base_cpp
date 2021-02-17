all: poll

point.o: point.hpp point.cpp
vector.o: vector.hpp vector.cpp
ground.o: ground.hpp ground.cpp
game.o: game.hpp game.cpp

main.o: main.cpp point.hpp vector.hpp ground.hpp game.hpp


poll: main.o point.o vector.o ground.o game.o
	g++ main.o point.o vector.o ground.o game.o -o play

clean:
	rm -f *.o