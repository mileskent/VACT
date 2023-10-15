#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{	WINDOW *my_win;
	int startx, starty, width, height;
	int ch;

	initscr();					// Start curses mode
	cbreak();					// Line Buffering Off
	keypad(stdscr, TRUE);		// Functions keys, etc

	height = LINES;
	width = COLS;
	starty = 0;
	startx = 0;
	printw("Press F1 to exit");
	refresh();
	my_win = create_newwin(height, width, starty, startx);
	getch();
	endwin();			/* End curses mode		  */
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
