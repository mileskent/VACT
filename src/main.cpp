#include <ncurses.h>
#include <cstring>
#include "filereader.h"
#include <vector>

using namespace std;

WINDOW * text_box;
WINDOW * text_window;
WINDOW * tt_window;
int first_word = 0; const int WORD_CAP = 200;
const double TWPER = 0.7;
vector<string> blocks;

int print_words (void)
{
	// We have to print word by word
	wmove (text_window, 1, 0); wrefresh (text_window);
	for (int i = first_word; i < first_word + WORD_CAP; i++)
	{
		if (i > blocks.size() - 1) break;

		if (i % 2 == 0)
		{
			wattron(text_window, A_BOLD | A_BLINK);
			wprintw (text_window, blocks.at(i).c_str());
			wattroff(text_window, A_BOLD | A_BLINK);	
		}
		else 
		{
			wprintw (text_window, blocks.at(i).c_str());
		}


		wprintw (text_window, " ");
	}

	box (text_box, 0, 0);		// Draw a box border for the window
	char text_title[] = "Text";
	mvwprintw (text_window, 0, (int)(COLS * TWPER / 2) - strlen(text_title) / 2, text_title); // Title
	wrefresh (text_box);
	wrefresh (text_window);
	refresh ();

	return 0;
}



int main (void)
{


// init word stuff
	blocks = slurp ("book.txt");


// init ncurses stuff
	initscr();					// Start curses mode
	cbreak();					// Line Buffering Off
	keypad(stdscr, TRUE);		// Functions keys, etc
	start_color();				// colorzzzzz
	refresh();					// The documentation has this here so Im copying it


// init screen
	// Create text window
	text_box = newwin(LINES, (int)(COLS * TWPER), 0, 0); 	
	text_window = newwin(LINES, (int)(COLS * TWPER) - 2, 0, 1);	
	// int wrap = (int)(COLS * TWPER - 3); // we can do wrap later

	print_words ();
	
	// Create tooltip window
	tt_window = newwin (LINES, (int)(COLS * (1 - TWPER)), 0, (int)(COLS * TWPER));
	box (tt_window, 0, 0);
	char tt_title[] = "Tooltip";
	mvwprintw (tt_window, 0, (int)(COLS * (1 - TWPER) / 2) - strlen(tt_title) / 2, tt_title);
	wrefresh (tt_window);


// input
	int inpch;
	while((inpch = wgetch(text_window)) != 'q')
	{ 
		switch(inpch)
		{ 
			case 'j':
				first_word+=50;
				if (first_word > blocks.size() - WORD_CAP) first_word = blocks.size() - WORD_CAP;
				print_words();
				break;
			case 'k':
				first_word-=50;
				if (first_word < 0) first_word = 0;
				print_words();
				break;
		}
		wmove (text_window, LINES, 1); wrefresh (text_window);
	}


// End exec
	// getch();					// Wait for key to exit
	endwin();					// End curses mode
	return 0;
}
