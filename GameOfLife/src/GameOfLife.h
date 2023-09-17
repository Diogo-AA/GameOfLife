#include <vector>
#pragma once
class GameOfLife
{
public: 
	GameOfLife();
	void start();
	void togglePause();
	void restart();
	void stop();
	void increaseSpeed();
	void decreaseSpeed();
private:
	static const int BOARD_ROWS = 20;
	static const int BOARD_COLS = 40;
	bool isRunning;
	int sleepMiliseconds;
	std::vector<std::vector<char>> board;
	std::vector<std::vector<int>> positionsToChange;
	void showBoard();
	void updateBoard();
	void proccessLife();
	void restartBoard();
	int countNeighbours(std::vector<std::vector<char>>, int, int);
};