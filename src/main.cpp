#include <ncurses.h>
// #include <panel.h>
#include <cstring>
#include "filereader.h"

using namespace std;


int main (void)
{
	const double TWPER = 0.7;
	initscr();					// Start curses mode
	cbreak();					// Line Buffering Off
	keypad(stdscr, TRUE);		// Functions keys, etc
	refresh();					// Uhhhhhh

	// Create text window
	// TODO: Scrollable text window
	WINDOW * text_window = newwin(LINES, (int)(COLS * TWPER), 0, 0); 	// Da window
	int wrap = (int)(COLS * TWPER - 3);
	string contents = slurp ("book.txt", wrap); 
		
	// TODO: Print from line A to line B
	int A, B, start, end;
	A = 0;
	B = 4;
	start = 0;
	string line;
	for (int i = A; i <= B; i++)
	{
		if (start < contents.length())
		{
			end = contents.find("\n", start);
			line = contents.substr(start, end);
			start = end + 1;
			mvwprintw (text_window, 1 + i - A, 1, line.c_str());
		}
	}
	// box (text_window, 0, 0);		// Draw a box border for the window
	char text_title[] = "Text";
	mvwprintw (text_window, 0, (int)(COLS * TWPER / 2) - strlen(text_title) / 2, text_title); // Title
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
