#include <ncurses.h>
#include <cstring>
#include "filereader.h"
#include <vector>

using namespace std;


int main (void)
{
	// init word stuff
	vector<string> blocks = slurp ("book.txt");
	const int WORD_CAP = 200;

	// init ncurses stuff
	const double TWPER = 0.7;
	initscr();					// Start curses mode
	cbreak();					// Line Buffering Off
	keypad(stdscr, TRUE);		// Functions keys, etc
	refresh();					// Uhhhhhh

	// Create text window
	// TODO: Scrollable text window
	
	WINDOW * text_box = newwin(LINES, (int)(COLS * TWPER), 0, 0); 	
	WINDOW * text_window = newwin(LINES, (int)(COLS * TWPER) - 2, 0, 1); 	// Da window
	// int wrap = (int)(COLS * TWPER - 3); // we can do wrap later

	// We have to print word by word
	int A = 0;
	wmove (text_window, 1, 0); wrefresh (text_window);
	for (int i = A; i < A + WORD_CAP; i++)
	{
		if (i > blocks.size() - 1) break;
		string block = blocks.at(i) + " ";
		wprintw (text_window, block.c_str());
	}

	box (text_box, 0, 0);		// Draw a box border for the window
	char text_title[] = "Text";
	mvwprintw (text_window, 0, (int)(COLS * TWPER / 2) - strlen(text_title) / 2, text_title); // Title
	wrefresh (text_box);
	wrefresh (text_window);
	refresh ();
	
	// Create tooltip window
	WINDOW * tt_window = newwin (LINES, (int)(COLS * (1 - TWPER)), 0, (int)(COLS * TWPER));
	box (tt_window, 0, 0);
	char tt_title[] = "Tooltip";
	mvwprintw (tt_window, 0, (int)(COLS * (1 - TWPER) / 2) - strlen(tt_title) / 2, tt_title);
	wrefresh (tt_window);

	// End exec
	getch();					// Wait for key to exit
	endwin();					// End curses mode
	return 0;
}
