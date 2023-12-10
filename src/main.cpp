#include <ncurses.h>
#include <vector>
#include <cstring>
#include <chrono>
#include <ctime>  
#include "filereader.hpp"
#include "word.hpp"

using namespace std;

#define REDFGPAIR 1

WINDOW * text_box;
WINDOW * text_window;
WINDOW * tt_box;
WINDOW * tt_window;
string bookname = "";
int first_word = 0; 
char inpch;
const int WORD_CAP = 200; 
const double TWPER = 0.7;
vector<string> blocks;
vector<Word> runtimeWords;
int activeword = 0;
const int jumplen = 10;

int iswordchar (char ch);
int pushwords ();
int pullwords ();
void dopunct (string block, string& start, string& word, string& end);
int refresh_tt (void);
int fixori (void);
int isdefinedword (string word);
int print_words (void);
bool vechas (vector<string> vec, string str);
string getword (string block);
string tolower (string str);
void dodef (string& definition);
void dogram (int& grammar);
void dofam (int& familiarity);
void writeentry (string word, string definition, int grammar, int familiarity);
Word getactiveword (string word);
int ncurses_init();
int choose_text();
int main_init();
int main_loop();
int end_deinit();

struct Pos
{
	int x;
	int y;
};
Pos cursor;

int main (void)
{
    ncurses_init();
    choose_text();
    main_init();
    main_loop();
    end_deinit();
	return 0;
}


int main_loop () {
    // main loop
	int d = 0;
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
				break;
			case 'l':
				if (activeword < blocks.size() - 1)
				{
					activeword++;
					fixori();
				}
				break;
			case 'k':
				activeword -= jumplen;
				if (activeword < 0) activeword = 0;
				fixori();
				break;
			case 'j':
				activeword += jumplen;
				if (activeword >= blocks.size()) activeword = blocks.size() - 1;
				fixori();
				break;
			case '\n':
				// check if word is already defined
				for (int word = 0; word < runtimeWords.size(); word++)
				{
					if (runtimeWords.at(word).getword() == getword(blocks.at(activeword)))
					{
						d = 1;
						break;
					}
				}
			

				string block = blocks.at(activeword);
				string word = getword(block);
				string definition; 
				int grammar;
				
				// already defined
				if (d)
				{
					int familiarity;

					getyx (tt_window, cursor.y, cursor.x);
					mvwprintw (tt_window, cursor.y++ + 1, 1, "Modify which?");
					mvwprintw (tt_window, cursor.y++ + 1, 1, "1. Definition");
					mvwprintw (tt_window, cursor.y++ + 1, 1, "2. Grammar Use");
					mvwprintw (tt_window, cursor.y++ + 1, 1, "3. Familiarity");

					while ( (inpch = wgetch(tt_window)) < '1' || inpch > '3' );

					// get the member vars from the word
					Word temp = getactiveword (word);
					wclear (tt_window);

					// def
					if (inpch == '1')
					{
						dodef (definition);
						writeentry (temp.getword(), definition, temp.getigrammar(), temp.getifamiliarity());
					}
					// grammar
					else if (inpch == '2')
					{
						dogram (grammar);
						writeentry (temp.getword(), temp.getdefinition(), grammar, temp.getifamiliarity());
					}

					// fam
					else if (inpch == '3')
					{
						dofam (familiarity);
						writeentry (temp.getword(), temp.getdefinition(), temp.getigrammar(), familiarity);
					}
				}
				// not defined
				else
				{
					getyx (tt_window, cursor.y, cursor.x);
					mvwprintw (tt_window, cursor.y++ + 1, 1, "Add to dictionary?");
					mvwprintw (tt_window, cursor.y++ + 1, 1, "y\tn");
					wrefresh (tt_window);
					while ( (inpch = wgetch(tt_window)) != 'y' && inpch != 'n') { print_words(); }

					if (inpch == 'y')
					{
						werase (tt_window);
						dodef (definition);
						dogram (grammar);
						writeentry (word, definition, grammar, 0);	
					}

				}
				break;
		}
		print_words();
		refresh_tt ();


	}
    return 0;
}

int main_init () {
    // init word stuff
	blocks = slurp (bookname);
	pullwords ();

    // init screen
	// Create text window
	text_box = newwin((int)(LINES), (int)(COLS * TWPER), 0, 0); 	
	text_window = newwin((int)(LINES) - 2, (int)(COLS * TWPER) - 2, 1, 1);	

	print_words ();
	
	// Create tooltip window
	tt_box = newwin (LINES, (int)(COLS * (1 - TWPER)), 0, (int)(COLS * TWPER));
	tt_window = newwin (LINES - 2, (int)(COLS * (1 - TWPER)) - 2, 1, (int)(COLS * TWPER) + 1);

	refresh_tt ();
    return 0;
}

int choose_text () {
	vector<string> fileoptions = gettexts(); // get the texts from the appropriate directory
	if (fileoptions.size() > 0)	{
		echo ();
		while ( !vechas(fileoptions, bookname) ) {
			bookname = "";
			printw ("Enter the name of the file you want.\n");
			for (string file : fileoptions)	{
				printw ((" > " + file + "\n").c_str());
			}
			inpch = getch(); 
			while ( inpch != '\n' ) {
                // backspace; my machine detects as ascii 7 but it should be 8... 
				if ( (inpch == KEY_BACKSPACE || inpch == 7 || inpch == 8) && bookname.length() > 0) { 
					getyx (stdscr, cursor.y, cursor.x); // write over the original character that was there
					printw (" ");
					move (cursor.y, cursor.x);
					bookname.pop_back(); // actually affect the string
				}
				else // everything else
				{
					bookname.push_back (inpch);
				}
				inpch = getch();
			}
			refresh (); // can still see the text even when I don't call this for some reason; here for safety
			clear();

			if ( !vechas(fileoptions, bookname) ) {
                attron(COLOR_PAIR(REDFGPAIR));
				printw ( ("You entered \"" + bookname + "\". File does not exist. Please try again.\n").c_str() );
                attroff(COLOR_PAIR(REDFGPAIR));
			}
		}
		noecho ();
	}
	else
	{
		printw ("Error. No available texts. Ending execution now.\n");
		refresh();
		getch();
		endwin(); 
		return 1;
	}
    return 0;
}

int ncurses_init () {
	initscr();					// Start curses mode
	cbreak();					// Line Buffering Off
	keypad(stdscr, true);		// Functions keys, etc
	if(has_colors() == false)
	{ 
		endwin();
		cout << "Your terminal does not support color! D:" << endl;
		return 1;
	}
	start_color();				// color
    init_pair(REDFGPAIR, COLOR_RED, COLOR_BLACK);
	noecho (); // hide input
    return 0;
}

// Is the character one we want in our Word's word?
int iswordchar (char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '-' || (ch >= '0' && ch <= '9');
}

// Does the vector have string str?
bool vechas (vector<string> vec, string str)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec.at(i) == str) return true;
	}
	return false;
}

// Update the dictionary file with the new words, after exec is done
int pushwords()
{
	ofstream file;
	// clear the file
	file.open("../res/dictionary/dict.vact", ofstream::out | ofstream::trunc);
	file.close();

	file.open("../res/dictionary/dict.vact", ios::app); // append mode
	ofstream log;
	log.open("../log.txt", ios::app); // append mode
	if (file.is_open() && log.is_open())
	{
		for (int id = 0; id < runtimeWords.size(); id++)
		{
			Word temp = runtimeWords.at(id);

			time_t current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
			log << "Wrote \"" << temp.getword() << "\" to the dictionary. " << ctime(&current_time) << endl;
			file << temp.getword() << ";" << temp.getdefinition() << ";" << temp.getigrammar() << ";" << temp.getifamiliarity() << endl;
		}
		file.close();
	}
	else return 1; 
	return 0;
}

// Get all the Words from the dictionary file on init
int pullwords()
{
        int id = 0;
        string istring;
        ifstream file("../res/dictionary/dict.vact");
        if (file.is_open())
        {
                while (getline(file, istring))
                {
                        Word temp;
                        unsigned long start = 0;
                        unsigned long len = istring.find_first_of(';');
                        temp.setword (istring.substr(start, len));

                        start += len + 1;
                        len = istring.substr(start).find_first_of(';');
                        temp.setdef (istring.substr(start, len));

					    start += len + 1;
                        len = istring.substr(start).find_first_of(';');
                        temp.setgrammar (atoi( istring.substr(start, len).c_str() ));

                        start += len + 1;
                        temp.setfam (atoi( istring.substr(start).c_str() ));

                        runtimeWords.push_back (temp);
                        id++;
                }
                file.close();
        }
        else return 1;
        return 0;
}

// tolower an entire string
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

// for each "block" (text in between spaces) get the word and the punctuation on the start and end, and isolate them
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

// return the word string from dopunct ^
string getword (string block)
{
	string s, w, e;
	dopunct (block, s, w, e);
	w = tolower(w);
	return w;
}

// the basic tooltip window
int refresh_tt (void)
{

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
	int tindex;
	for (int word = 0; word < runtimeWords.size(); word++)
	{
		if (runtimeWords.at(word).getword() == getword(blocks.at(activeword)))
		{
			defined = 1;
			tindex = word;
			break;
		}
	}
	getyx (tt_window, cursor.y, cursor.x);
	if (!defined)
	{
		wprintw (tt_window, "This word is undefined.");
	}
	else 
	{
		Word temp = runtimeWords.at(tindex);
		mvwprintw (tt_window, cursor.y++ + 1, 1, ("Word: " + temp.getword()).c_str());
		mvwprintw (tt_window, cursor.y++ + 1, 1, ("Definition: " + temp.getdefinition()).c_str());
		mvwprintw (tt_window, cursor.y++ + 1, 1, ("Grammatical Use: " + temp.getgrammar()).c_str());
		mvwprintw (tt_window, cursor.y++ + 1, 1, ("Familiarity: " + temp.getfamiliarity()).c_str());
	}
	wprintw (tt_window, "\n <Enter> to modify.");
	
	wrefresh (tt_window);
	
	return 0;

}

// fix the orientation of the text window; we want WORD_CAP words to be shown 
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

// is the word string defined in the runtimeWords vector?
int isdefinedword (string word)
{
	for (int i = 0; i < runtimeWords.size(); i++)
	{
		if (runtimeWords.at(i).getword() == word) return 1;
	}
	return 0;
}

// output all of the words the we want to view into the text window
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
		
		if (!isdefinedword(tolower(word))) // to lower bc we want "Snake" and "snake" and "SNAKE" to have the same def
		{
            wattron(text_window, COLOR_PAIR(REDFGPAIR));
			wattron (text_window, A_UNDERLINE);
		}

		// differentiate word if active word
		if (i == activeword)
		{
			wattron(text_window, A_BOLD | A_BLINK | A_ITALIC);
			wprintw (text_window, word.c_str());
			wattroff(text_window, A_BOLD | A_BLINK | A_ITALIC);	
		}
		else 
		{
			wprintw (text_window, word.c_str());
		}
		
		if (!isdefinedword(word))
		{
			wattroff (text_window, A_UNDERLINE);
            wattroff(text_window, COLOR_PAIR(REDFGPAIR));
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

// handle assigning the definition of a word
void dodef (string & definition)
{
	mvwprintw (tt_window, 1, 1, "Definition: ");
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
}

// handle assigning the grammar of a word
void dogram (int & grammar)
{
	inpch = 0;
	wprintw (tt_window, " 1. Noun\n ");
	wprintw (tt_window, "2. Verb\n ");
	wprintw (tt_window, "3. Adverb\n ");
	wprintw (tt_window, "4. Article\n ");
	wprintw (tt_window, "5. Adjective\n ");
	wprintw (tt_window, "6. Other\n ");
	
	inpch = wgetch(tt_window) - '0'; // -'0' important; '0'-'9' != 0-9
	while ( !(inpch <= 6 && inpch >= 1) )
	{
		inpch = wgetch(tt_window) - '0';
	}
	grammar = inpch - 1; 
}


// handle assigning the familiarity of a word
void dofam (int & familiarity)
{
	inpch = 0;
	wprintw (tt_window, " 1. New\n ");
	wprintw (tt_window, " 2. Hard\n ");
	wprintw (tt_window, " 3. Medium\n ");
	wprintw (tt_window, " 4. Easy\n ");
	wprintw (tt_window, " 5. Mastered\n ");
	
	inpch = wgetch(tt_window) - '0'; // -'0' important; '0'-'9' != 0-9
	while ( !(inpch <= 5 && inpch >= 1) )
	{
		inpch = wgetch(tt_window) - '0';
	}
	familiarity = inpch - 1; 
}

// write Word to runtime entries and remove dupes if applicable
void writeentry (string word, string definition, int grammar, int familiarity)
{
	// now write it to vector -> this scen will have diff behavior if word already defined
	Word temp (word, definition, grammar, familiarity);

	// replace duplicates if applicable
	int dupes = 0;
	for (int word = 0; word < runtimeWords.size(); word++)
	{
		if (runtimeWords.at(word).getword() == temp.getword())
		{
			runtimeWords.at(word) = temp;
			dupes = 1;
		}
	}
	if (dupes == 0)	runtimeWords.push_back(temp);
	werase (tt_window);
	wprintw (tt_window, " Added the following entry:");
	wprintw (tt_window, ("\n Word: " + word + "\n").c_str());
	wprintw (tt_window, ("Definition: " + definition + "\n").c_str());
	wprintw (tt_window, ("Grammatical Use: " + temp.getgrammar() + "\n").c_str());
	wprintw (tt_window, ("Familiarity: " + temp.getfamiliarity() + "\n").c_str());


	wgetch(tt_window); // Wait
}

// get "activeword" as a Word from runtimeWords
Word getactiveword (string word)
{
	for (Word w : runtimeWords)
	{
		if (w == word)
		{
			return w;
		}
	}

	cerr << "Error! Internal disagreement about existence of dictionary entry." << endl;
	return Word();
}

int end_deinit() {
    // End exec
	clear ();
	printw ("Saving dictionary...\n");
	pushwords ();
	printw ("Dictionary saved.\n");
	printw ("Execution terminated. Press any key to continue...");
	refresh ();
	getch();
	endwin(); // exit curse mode
    return 0;
}
