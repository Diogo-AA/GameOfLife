main: ./GameOfLife/src/Main.cpp ./GameOfLife/src/GameOfLife.o ./GameOfLife/src/Log.o
	g++ ./GameOfLife/src/Main.cpp ./GameOfLife/src/GameOfLife.o ./GameOfLife/src/Log.o -Wall -lncurses -o main
./GameOfLife/src/GameOfLife.o: ./GameOfLife/src/GameOfLife.cpp ./GameOfLife/src/GameOfLife.h
	g++ ./GameOfLife/src/GameOfLife.cpp -Wall -c -lncurses -o ./GameOfLife/src/GameOfLife.o
./GameOfLife/src/Log.o: ./GameOfLife/src/Log.cpp ./GameOfLife/src/Log.h
	g++ ./GameOfLife/src/Log.cpp -Wall -c -lncurses -o ./GameOfLife/src/Log.o
clean:
	rm ./GameOfLife/src/*.o main