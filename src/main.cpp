#include <ncurses.h>

int main( void )
{
	const double TWPER = 0.7;
	initscr();					// Start curses mode
	cbreak();					// Line Buffering Off
	keypad(stdscr, TRUE);		// Functions keys, etc
	refresh();					// Uhhhhhh

	// Create text window
	WINDOW * text_window = newwin(LINES, COLS * TWPER, 0, 0); 	// Da window
	box(text_window, 0, 0);		// Box idk
	wrefresh(text_window); 		// Show the box
	
	// Create tooltip window
	WINDOW * tt_window = newwin(LINES, COLS * (1 - TWPER), 0, COLS * TWPER);
	box(tt_window, 0, 0);
	wrefresh(tt_window);

	// End exec
	getch();					// Wait for key to exit
	endwin();					// End curses mode
	return 0;
}
