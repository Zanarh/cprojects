#include <stdio.h>
#include <ncurses.h>
#include <curses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// #include <gsl/gsl_rng.h>

#define DELAY 30000
#define MAXX 1000
// int j = 0;
// int tx, ty;
// getmaxyx(stdscr, tx, ty);
// WINDOW *field = newwin(max_y, max_x, 0, 0); 

// 	int j = ty/2; 

int j = 0;
int possy[MAXX];

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

// int max_y = 0, max_x = 0;



void draw_x(WINDOW *screen, int pos_x, int pos_y, int max_x, int max_y) {
	// static int x = max_x/2;
	// static int y = max_y/2;
	pos_x = max_x/2;
	pos_y = max_y/2;
	mvwprintw(screen, pos_y, pos_x, "o");
}


int main(int argc, char *argv[]) {
	// gsl_rng * r;

	// int num = gsl_rng_uniform(r);

	int x = 3, y = 4;

	int max_y = 1, max_x = 1;

	int new_x, new_y; 

	int pos_x = 5, pos_y = 5;

	int next_x = 0;
	int direction = 1;

	int len;
	char str[50];

	strcpy(str, "I'm moving!");
	len = strlen(str);

	initscr();
	noecho();
	curs_set(FALSE);

	WINDOW *field = newwin(max_y, max_x, 0, 0); 
	getmaxyx(stdscr, pos_y, pos_x);
	j = pos_y/2;

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
	mvwprintw(field, 3, x, str);
	// draw_x(field, pos_x, pos_y, max_x, max_y);

	init_graph(field);

	wrefresh(field);	

	usleep(DELAY);

	while(1) {
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
		mvwprintw(field, 3, x, str);
		// draw_x(field, pos_x, pos_y, max_x, max_y);

		draw_graph(field);

		wrefresh(field);	

		usleep(DELAY);

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

	// int static j = (int) max_y; 
	int randy, tempy;

	for (int i = 1; i < (max_x - 1); i++) {
		randy = rand() % 2;
		tempy = rand() % 2;
		if (tempy == 0) {
			randy *= -1;
		}

		if (((j + randy) < (max_y - 1)) && (j + randy) > 4) {
			j += randy;
		}

		possy[i-1] = j;
		
		mvwprintw(screen, j, i, "o");
	}	
}

void draw_graph(WINDOW *screen) {
	int max_x, max_y;
	int randy, tempy;
	getmaxyx(stdscr, max_y, max_x);
	randy = rand() % 2;
	tempy = rand() % 2;
	if (tempy == 0) {
		randy *= -1;
	}

	for (int i = 1; i < (max_x - 1); i++) {
		if (i == (max_x - 2)) {
			if (((j + randy) < (max_y - 1)) && (j + randy) > 4) {
				j += randy;
			}
			possy[i-1] = j;
		}
		else {
			possy[i-1] = possy[i];
		}
		mvwprintw(screen, possy[i-1], i, "o");
	}
}