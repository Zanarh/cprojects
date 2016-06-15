#include <stdio.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <string.h>

#define DELAY 30000

int main(int argc, char *argv[])
{
	int x = 4, y = 4;
	int max_y = 0, max_x = 0;
	int next_x = 0;
	int direction = 1;

	int len;
	char str[50];

	strcpy(str, "I'm moving!");
	len = strlen(str);

	initscr();
	noecho();
	curs_set(FALSE);

	// Global var `stdscr` is created by the call to `initscr()`
	getmaxyx(stdscr, max_y, max_x);

	while(1){
		clear();
		mvprintw(1, 4, "Hello, World!");
		mvprintw(y, x, str);
		refresh();

		usleep(DELAY);

		next_x = x + direction;

		if (next_x >= (max_x - len) || next_x < 0) {
			direction *= -1;
		} else {
			x += direction;
		}
	}

	// getch();
	endwin();

	return 0;
}