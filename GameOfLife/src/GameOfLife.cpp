#ifdef _WIN32
#include <Windows.h>
#else
#include <ncurses.h>
#endif
#include <string.h>
#include <iostream>
#include <thread>
#include <cstdlib>
#include "GameOfLife.h"
#include "Log.h"

GameOfLife::GameOfLife() {
    sleepMiliseconds = 600;
    isRunning = true;
    positionsToChange = {};
    restartBoard();
}

void GameOfLife::restartBoard() {
    srand((unsigned)time(NULL));
    board.resize(BOARD_ROWS, std::vector<char>(BOARD_COLS, ' '));

    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            if (rand() % 3 == 0) {
                board[i][j] = 'o';
            }
        }
    }
}

void GameOfLife::showBoard() {
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            char* string = (char*)malloc(3*sizeof(char));
            if (string != NULL) {
                string[0] = board[i][j];
                string[1] = ' ';
                string[2] = '\0';
                print(string);
            }
        }
        print("\n");
    }
    showControls();
}

void GameOfLife::updateBoard() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    COORD originalPos = consoleInfo.dwCursorPosition;
    COORD consolePos;

    for (const std::vector<int> pos : positionsToChange)
    {
        consolePos = { (short)(pos[1] * 2), (short)(pos[0]) };
        SetConsoleCursorPosition(hConsole, consolePos);
        std::cout << board[pos[0]][pos[1]];
    }
    SetConsoleCursorPosition(hConsole, originalPos);
#else
    int rowOriginal, colOriginal;
    getyx(stdscr, rowOriginal, colOriginal);
    for (const std::vector<int>& pos : positionsToChange)
    {
        move(pos[0], pos[1] * 2);
        printw("%c", board[pos[0]][pos[1]]);
    }
    move(rowOriginal, colOriginal);
    refresh();
#endif
}

int GameOfLife::countNeighbours(std::vector<std::vector<char>> copyBoard, int row, int col) {
    int sumNeighbours = 0;
    int rowStart = row - 1 < 0 ? row : row - 1;
    int rowEnd = row + 1 > BOARD_ROWS - 1 ? row : row + 1;
    int colStart = col - 1 < 0 ? col : col - 1;
    int colEnd = col + 1 > BOARD_COLS - 1 ? col : col + 1;

    for (int i = rowStart; i <= rowEnd; i++) {
        for (int j = colStart; j <= colEnd; j++) {
            if (i == row && j == col) {
                continue;
            }
            if (copyBoard[i][j] == 'o') {
                sumNeighbours++;
            }
        }
    }

    return sumNeighbours;
}

void GameOfLife::proccessLife() {
    std::vector<std::vector<char>> copyBoard = board;

    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            int numNeighbours = countNeighbours(copyBoard, i, j);
            if (copyBoard[i][j] == ' ') {
                if (numNeighbours == 3) {
                    positionsToChange.insert(positionsToChange.end(), {i, j});
                    board[i][j] = 'o';
                }
            }
            else {
                if (numNeighbours < 2 || numNeighbours > 3) {
                    positionsToChange.insert(positionsToChange.end(), {i, j});
                    board[i][j] = ' ';
                }
            }
        }
    }
}

void GameOfLife::togglePause() {
    isRunning = !isRunning;
}

void GameOfLife::restart() {
    restartBoard();
}

void GameOfLife::stop() {
    exit(0);
}

void GameOfLife::increaseSpeed() {
    if (sleepMiliseconds <= 0)
        return;
    sleepMiliseconds -= 150;
}

void GameOfLife::decreaseSpeed() {
    if (sleepMiliseconds >= 1500)
        return;
    sleepMiliseconds += 150;
}

void GameOfLife::start() {
    showBoard();

    while (true) {
        if (!isRunning)
            continue;

        std::this_thread::sleep_for(std::chrono::milliseconds(sleepMiliseconds));
        proccessLife();
        updateBoard();
        positionsToChange.clear();
    }
}