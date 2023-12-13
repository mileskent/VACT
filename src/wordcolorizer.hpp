#ifndef WORDCOLORIZER_HPP
#define WORDCOLORIZER_HPP
#include "wordprocessor.hpp"
#include "wordhelper.hpp"
#include <ncurses.h>
#include <string>

#define REDFGPAIR 1
#define YELLOWFGPAIR 2

class WordColorizer : public WordProcessor {
private:
   bool isactiveword;
   bool isdefined;
public:
// CONSTRUCTOR
    WordColorizer (std::string wordblock, 
            WINDOW* writingwindow,
            bool isactiveword,
            bool isdefined) : WordProcessor (wordblock, writingwindow) {
        this->isactiveword = isactiveword;
        this->isdefined = isdefined;
    }
// PROCESSING FUNCTION
    // Does all the colors and effects for a given word
    void process () override {
        std::string word, start, end; 
        WordHelper::splitblock(wordblock, start, word, end);

		wprintw (writingwindow, start.c_str());   // print nonalphanum start

		if (!isdefined) wattron (writingwindow, A_UNDERLINE);   

		// differentiate word if active word
		if (isactiveword)
		{
            wattron(writingwindow, COLOR_PAIR(REDFGPAIR));
			wattron(writingwindow, A_BOLD | A_BLINK | A_ITALIC);
			wprintw (writingwindow, word.c_str());
			wattroff(writingwindow, A_BOLD | A_BLINK | A_ITALIC);	
            wattroff(writingwindow, COLOR_PAIR(REDFGPAIR));
		}
		else 
		{
			wprintw (writingwindow, word.c_str());
		}
		
		if (!isdefined) wattroff (writingwindow, A_UNDERLINE);   

		
		wprintw (writingwindow, end.c_str());   // print nonalphanum end
    }
};

#endif


