#include <thread>
#include <conio.h>
#include "GameOfLife.h"
#include "Log.h"

int main()
{
    GameOfLife game;
    std::thread gameThread(&GameOfLife::start, &game);
    hideCursor();

    while (true) {
        char key = _getch();
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
                showCursor();
                game.stop();
                exit(0);
            default:
                break;
        }
    }
}