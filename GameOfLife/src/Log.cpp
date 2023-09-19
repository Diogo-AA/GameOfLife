#ifdef _WIN32
#include <Windows.h>
#else
#include <ncurses.h>
#endif
#include <iostream>
#include "Log.h"

void print(const char* string) {
#ifdef _WIN32
	std::cout << string;
#else
	printw("%s", string);
#endif
}

void showControls() {
	print("\nControls:\n");
	print("p - resume/pause\n");
	print("r - restart\n");
	print("w - increase speed\n");
	print("s - decrease speed\n");
	print("q - quit\n");
}

void showCursor() {
#ifdef _WIN32
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = true; // true to show, false to hide
	SetConsoleCursorInfo(out, &cursorInfo);
#else
	curs_set(TRUE); //show cursor
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
	curs_set(FALSE); //hide cursor
#endif
}

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void initialize() {
	hideCursor();
#ifndef _WIN32
	initscr();
	timeout(-1);
	cbreak();
	noecho();
#endif
}

void quit() {
#ifndef _WIN32
	endwin();
#endif
	showCursor();
}