#include <ncurses.h>
#include <cstring>
#include "filereader.h"
#include "word.h"
#include <vector>

using namespace std;

WINDOW * text_box;
WINDOW * text_window;
WINDOW * tt_window;
int first_word = 0; const int WORD_CAP = 200;
const double TWPER = 0.7;
vector<string> blocks;
int activeword = 0;
int cx, cy;

// TODO: Help Menu
int help (void);

int fixori (void)
{
	if (activeword >= WORD_CAP + first_word) first_word = activeword;
	else if (activeword < first_word)
	{
		first_word = activeword - WORD_CAP;
		if (first_word < 0) first_word = 0;
	}
	return 0;
}

int print_words (void)
{
	// We have to print word by word
	wmove (text_window, 1, 0); wrefresh (text_window);
	for (int i = first_word; i < first_word + WORD_CAP; i++)
	{
		if (i > blocks.size() - 1) break;

		if (i == activeword)
		{
			getyx (text_window, cy, cx);
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
	if(has_colors() == FALSE)
	{ 
		endwin();
		cout << "Your terminal does not support color! D:" << endl;
		return 1;
	}
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

	move (LINES - 2, 1); refresh ();


// input
	int inpch;
	const int jumplen = 10;
	while((inpch = wgetch(text_window)) != 'q')
	{ 
		switch(inpch)
		{ 
			case 'h':
				if (activeword >= 1)
				{
					activeword--;
					fixori();
				}
				print_words();
				break;
			case 'l':
				if (activeword < blocks.size() - 1)
				{
					activeword++;
					fixori();
				}
				print_words();
				break;
			case 'k':
				activeword -= jumplen;
				if (activeword < 0) activeword = 0;
				fixori();
				print_words();
				break;
			case 'j':
				activeword += jumplen;
				if (activeword >= blocks.size()) activeword = blocks.size() - 1;
				fixori();
				print_words();
				break;
			default:
				print_words();
				break;
		}
		move (LINES - 2, 1); refresh ();
	}


// End exec
	// getch();					// Wait for key to exit
	endwin();					// End curses mode
	return 0;
}
