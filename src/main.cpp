#include <ncurses.h>
#include <cstring>
#include "filereader.h"
#include "word.h"
#include <vector>

using namespace std;

WINDOW * text_box;
WINDOW * text_window;
WINDOW * tt_box;
WINDOW * tt_window;
WINDOW * cmd_box;
WINDOW * cmd_window;
int first_word = 0; 
char inpch;
const int WORD_CAP = 200; // TODO: Figure out a way to fit this to the window instead of hardcoding
const double TWPER = 0.7;
vector<string> blocks;
vector<Word> runtimeWords;
int activeword = 0;
int cx, cy;

int iswordchar (char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '-' || (ch >= '0' && ch <= '9');
}

string tolower (string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str.at(i) >= 'A' && str.at(i) <= 'Z')
		{
			str[i] += 'a' - 'A';
		}
	}
	return str;
}

void dopunct (string block, string & start, string & word, string & end)
{
	// Handle punctuation	

	start = ""; end = " ";
	int wordch1, wordchlast;
	for (int i = 0; i < block.length(); i++)
	{
		if (iswordchar(block.at(i)))
		{
			word += block.at(i);
		}
	}

	for (int i = 0; i < block.length(); i++)
	{
		if (iswordchar(block.at(i)))
		{
			wordch1 = i;
			break;
		}
	}
	start = block.substr(0, wordch1);

	for (int i = block.length() - 1; i >= 0; i--)
	{
		if (iswordchar(block.at(i)))
		{
			wordchlast = i + 1;
			break;
		}
	}
	// Idk why this was causing coredump but it was so I wrapped it
	// end = block.substr(wordchlast) + " ";
	if (wordchlast >= 0 && wordchlast < block.length()) 
	{
		end = block.substr(wordchlast) + " ";
	} 


}

string getword (string block)
{
	string s, w, e;
	dopunct (block, s, w, e);
	return w;
}

int refresh_tt (void)
{

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	// TODO: Add more than just the word
	// tt_window
	werase (tt_window);
	box (tt_box, 0, 0); 
	char tt_title[] = "Tooltip";	
	mvwprintw (tt_box, 0, (int)(COLS * (1 - TWPER) / 2) - strlen(tt_title) / 2, tt_title); 
	wrefresh (tt_box); 

	string s, tt_word, e;
	dopunct (blocks.at(activeword), s, tt_word, e); 
	
	tt_word = "Selected: \"" + tt_word + "\"";
	wmove (tt_window, 0, 1);
	wprintw (tt_window, tt_word.c_str());
	wmove (tt_window, 1, 1);
	
	int defined = 0;
	if (!defined)
	{
		wprintw (tt_window, "This word is undefined.");
	}
	wprintw (tt_window, "\n <Enter> to select.");
	
	wrefresh (tt_window);
	
	return 0;

}
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
	wmove (text_window, 0, 0); wrefresh (text_window);
	for (int i = first_word; i < first_word + WORD_CAP; i++)
	{
		if (i > blocks.size() - 1) break;

		string block = blocks.at(i);
		string word, start, end;
		dopunct (block, start, word, end);

				// print nonalphanum start
		wprintw (text_window, start.c_str());

		// differentiate word if active word
		if (i == activeword)
		{
			getyx (text_window, cy, cx);
			wattron(text_window, A_BOLD | A_BLINK | A_ITALIC);
			wprintw (text_window, word.c_str());
			wattroff(text_window, A_BOLD | A_BLINK | A_ITALIC);	
		}
		else 
		{
			wprintw (text_window, word.c_str());
		}
		

		// print nonalphanum end
		wprintw (text_window, end.c_str());
	}

	box (text_box, 0, 0);		// Draw a box border for the window
	char text_title[] = "Text";
	mvwprintw (text_box, 0, (int)(COLS * TWPER / 2) - strlen(text_title) / 2, text_title); // Title
	wrefresh (text_box);
	wrefresh (text_window);

	return 0;
}

/*
string getstring()
{
    string input;

    nocbreak();
    echo();

    int ch = getch();

    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }

	cbreak();
	noecho();

    return input;
}
*/

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
	noecho ();


// init screen
	// Create text window
	text_box = newwin((int)(LINES), (int)(COLS * TWPER), 0, 0); 	
	text_window = newwin((int)(LINES) - 2, (int)(COLS * TWPER) - 2, 1, 1);	

	print_words ();
	
	// Create tooltip window
	tt_box = newwin (LINES, (int)(COLS * (1 - TWPER)), 0, (int)(COLS * TWPER));
	tt_window = newwin (LINES - 2, (int)(COLS * (1 - TWPER)) - 2, 1, (int)(COLS * TWPER) + 1);

	refresh_tt ();


// input
	const int jumplen = 10;
	while ((inpch = wgetch(text_window)) != 'q')
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
			case '\n':
				getyx (tt_window, cy, cx);
				mvwprintw (tt_window, cy++ + 1, 1, "Add to dictionary?");
				mvwprintw (tt_window, cy++ + 1, 1, "y\tn");
				wrefresh (tt_window);
				while ( (inpch = wgetch(tt_window)) != 'y' && inpch != 'n') { print_words(); }
				if (inpch == 'y')
				{
					string word = getword (blocks.at(activeword));
					string definition; 
					int grammar;
					
					mvwprintw (tt_window, cy++ + 1, 1, "Definition: ");
					nocbreak ();	
					echo();
					int ch = wgetch(tt_window);
					
					while ( ch != '\n' )
					{
						definition.push_back( ch );
						ch = wgetch(tt_window);
					}
					cbreak();
					noecho();
					// TODO add the other variables
					// write it to vector
					// have diff behavior if already defined
					
					mvwprintw (tt_window, cy++ + 1, 1, ("Definition: " + definition).c_str());
					

					wgetch(tt_window); // Wait
					print_words();

				}
				else if (inpch == 'n')
				{
					print_words();
				}
				break;
			default:
				print_words();
				break;
		}
		refresh_tt ();


	}


// End exec
	erase();
	printw ("Execution terminated. Press any key to continue...");
	getch();
	endwin(); // exit curse mode
	return 0;
}
