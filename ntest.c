#include <stdio.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// #include <gsl/gsl_rng.h>

#define DELAY 30000 // refresh
#define MAXX 1000
#define ever (;;)

int y_increment = 0;
int y_position[MAXX];

void init_graph(WINDOW *screen);
void draw_graph(WINDOW *screen);

void draw_borders(WINDOW *screen) { 
	int x, y, i; 
	getmaxyx(screen, y, x); 

	mvwprintw(screen, 0, 0, "+"); 
	mvwprintw(screen, y - 1, 0, "+"); 
	mvwprintw(screen, 0, x - 1, "+"); 
	mvwprintw(screen, y - 1, x - 1, "+"); 

	for (i = 1; i < (y - 1); i++) { 
		mvwprintw(screen, i, 0, "|"); 
		mvwprintw(screen, i, x - 1, "|"); 
	} 
	for (i = 1; i < (x - 1); i++) { 
		mvwprintw(screen, 0, i, "-"); 
		mvwprintw(screen, y - 1, i, "-"); 
	}
}

int main(int argc, char *argv[]) {
	int x = 3, y = 4; // arbitrary starting positions
	int max_y, max_x;
	int new_x, new_y; 

	int next_x = 0;
	int direction = 1;

	int len;
	char scroll_str[50];

	initscr();
	noecho();
	curs_set(FALSE);

	WINDOW *field = newwin(max_y, max_x, 0, 0); 
	getmaxyx(stdscr, max_y, max_x);
	y_increment = max_y/2;

	wclear(field);
	draw_borders(field); 
	getmaxyx(stdscr, new_y, new_x); 
	if (new_y != max_y || new_x != max_x) { 
		max_x = new_x; max_y = new_y; 
		wresize(field, new_y, new_x); 
		wclear(stdscr); 
		wclear(field); 
		draw_borders(field); 
	} 
	mvwprintw(field, 1, 2, "Pseudo-random walk");
	strcpy(scroll_str, "turk sux massive dongers!!1!");
	len = strlen(scroll_str);
	mvwprintw(field, 3, x, scroll_str);

	init_graph(field);

	wrefresh(field);	
	usleep(DELAY);

	for ever {
		wclear(field);
		draw_borders(field); 
		getmaxyx(stdscr, new_y, new_x); 
		if (new_y != max_y || new_x != max_x) { 
			max_x = new_x; max_y = new_y; 
			wresize(field, new_y, new_x); 
			wclear(stdscr); 
			wclear(field); 
			draw_borders(field); 
		} 
		mvwprintw(field, 1, 2, "Pseudo-random walk");
		mvwprintw(field, 3, x, scroll_str);

		draw_graph(field);

		wrefresh(field);	
		usleep(DELAY);

		// horizontal increment of scrolling text 
		next_x = x + direction;
		if (next_x >= (max_x - len - 1) || next_x < 2) {
			direction *= -1;
		} else {
			x += direction;
		}
	}

	delwin(field); 
	endwin();
	return 0;
}

void init_graph(WINDOW *screen) {
	int max_x, max_y;
	getmaxyx(stdscr, max_y, max_x);
	y_increment = max_y/2;

	// int static y_increment = (int) max_y; 
	int randy, signy;

	for (int i = 1; i < (max_x - 1); i++) {
		randy = rand() % 2;
		signy = rand() % 2;
		if (signy == 0) {
			randy *= -1;
		}

		if (((y_increment + randy) < (max_y - 1)) && (y_increment + randy) > 4) {
			y_increment += randy;
		}

		y_position[i-1] = y_increment;
		
		mvwprintw(screen, y_increment, i, "o");
	}	
}

void draw_graph(WINDOW *screen) {
	int max_x, max_y;
	int randy, signy;
	getmaxyx(stdscr, max_y, max_x);
	randy = rand() % 2;
	signy = rand() % 2;
	if (signy == 0) {
		randy *= -1;
	}

	for (int i = 1; i < (max_x - 1); i++) {
		if (i == (max_x - 2)) {
			if (((y_increment + randy) < (max_y - 1)) && (y_increment + randy) > 4) {
				y_increment += randy;
			}
			y_position[i-1] = y_increment;
		}
		else {
			y_position[i-1] = y_position[i];
		}
		mvwprintw(screen, y_position[i-1], i, "o");
	}
}