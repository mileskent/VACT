#include <ncurses.h>
// #include <panel.h>
#include <cstring>
#include "filereader.h"

using namespace std;


int main( void )
{
	const double TWPER = 0.7;
	initscr();					// Start curses mode
	cbreak();					// Line Buffering Off
	keypad(stdscr, TRUE);		// Functions keys, etc
	refresh();					// Uhhhhhh

	// Create text window
	// TODO: Change this to a pad
	WINDOW * text_window = newwin(LINES, (int)(COLS * TWPER), 0, 0); 	// Da window
	box(text_window, 0, 0);		// Box idk
	char text_title[] = "Text";
	mvwprintw(text_window, 0, (int)(COLS * TWPER / 2) - strlen(text_title) / 2, text_title); // Title
	string contents = slurp ("book.txt"); 
	wrefresh(text_window); 		// Show the box
	
	// Create tooltip window
	WINDOW * tt_window = newwin(LINES, (int)(COLS * (1 - TWPER)), 0, (int)(COLS * TWPER));
	box(tt_window, 0, 0);
	char tt_title[] = "Tooltip";
	mvwprintw(tt_window, 0, (int)(COLS * (1 - TWPER) / 2) - strlen(tt_title) / 2, tt_title);
	wrefresh(tt_window);

	// End exec
	getch();					// Wait for key to exit
	endwin();					// End curses mode
	return 0;
}
