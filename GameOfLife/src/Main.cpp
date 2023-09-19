#ifdef _WIN32
#include <conio.h>
#else
#include <ncurses.h>
#endif
#include <thread>
#include "GameOfLife.h"
#include "Log.h"

#ifndef _WIN32
int kbhit()
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    }
    else {
        return 0;
    }
}
#endif

int main()
{
    GameOfLife game;

    clearScreen();
    initialize();
    std::thread gameThread(&GameOfLife::start, &game);

    while (true) {
#ifdef _WIN32
        char key = _getch();
#else
        if (!kbhit()) {
            continue;
        }
        char key = getch();
#endif
        switch (key) {
            case 'p': 
                game.togglePause();
                break;
            case 'r': 
                game.restart();
                break;
            case 'w':
                game.increaseSpeed();
                break;
            case 's':
                game.decreaseSpeed();
                break;
            case 'q':                 
                quit();
                game.stop();
                return 0;
            default:
                break;
        }
    }
}