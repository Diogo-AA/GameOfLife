#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include "Log.h"

void showControls() {
	std::cout << "\nControls:\n";
	std::cout << "p - resume/pause\n";
	std::cout << "r - restart\n";
	std::cout << "w - increase speed\n";
	std::cout << "s - decrease speed\n";
	std::cout << "q - quit\n";
}

void showCursor() {
#ifdef _WIN32
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = true; // true to show, false to hide
	SetConsoleCursorInfo(out, &cursorInfo);
#else
	printf("\e[?25h"); //show cursor
#endif
}

void hideCursor() {
#ifdef _WIN32
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // true to show, false to hide
	SetConsoleCursorInfo(out, &cursorInfo);
#else
	printf("\e[?25l"); //hide cursor
#endif
}