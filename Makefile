main: ./GameOfLife/src/Main.cpp ./GameOfLife/src/GameOfLife.o Log.o
	g++ ./GameOfLife/src/Main.cpp ./GameOfLife/src/GameOfLife.o ./GameOfLife/src/Log.o -Wall -lncurses -o ./main
./GameOfLife/src/GameOfLife.o: ./GameOfLife/src/GameOfLife.cpp ./GameOfLife/src/GameOfLife.h
	g++ GameOfLife.cpp -Wall -c -lncurses
./GameOfLife/src/Log.o: ./GameOfLife/src/Log.cpp ./GameOfLife/src/Log.h
	g++ ./GameOfLife/src/Log.cpp -Wall -c -lncurses
clean:
	rm ./GameOfLife/src/*.o main