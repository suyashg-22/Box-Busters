build: game.out

run: game.out
	./game.out

game.out : main.o game.o
	g++ main.o game.o -o game.out -lsfml-graphics -lsfml-window -lsfml-system

main.o: ./src/main.cpp ./include/game.hpp
	g++ -I./include -c ./src/main.cpp 

game.o: ./src/game.cpp ./include/game.hpp
	g++ -I./include -c ./src/game.cpp 

clean:
	rm -f main.o game.o game.out
 