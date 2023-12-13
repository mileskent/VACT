#ifndef WORDHELPER_HPP
#define WORDHELPER_HPP
#include <string>

class WordHelper {
public:
    // for each "block" (text in between spaces) get the word and the punctuation on the start and end, and isolate them
    static void splitblock (std::string wordblock, std::string & start, std::string & word, std::string & end) {
        // Handle punctuation	
        start = ""; end = " ";
        int wordch1, wordchlast;
        for (int i = 0; i < wordblock.length(); i++)
        {
            if (iswordchar(wordblock.at(i)))
            {
                word += wordblock.at(i);
            }
        }

        for (int i = 0; i < wordblock.length(); i++)
        {
            if (iswordchar(wordblock.at(i)))
            {
                wordch1 = i;
                break;
            }
        }
        start = wordblock.substr(0, wordch1);

        for (int i = wordblock.length() - 1; i >= 0; i--)
        {
            if (iswordchar(wordblock.at(i)))
            {
                wordchlast = i + 1;
                break;
            }
        }

        // end = wordblock.substr(wordchlast) + " ";
        if (wordchlast >= 0 && wordchlast < wordblock.length()) // prevents OOB Error
        {
            end = wordblock.substr(wordchlast) + " ";
        } 
    }

    // return the word std::string from ^
    static std::string getword (std::string wordblock)
    {
        std::string s, w, e;
        splitblock (wordblock, s, w, e);
        w = tolower(w);
        return w;
    }
    
    // tolower an entire std::string
    // Note: Works with stuff like german esset as the letter just stays the same
    static std::string tolower (std::string str) {
        for (int i = 0; i < str.length(); i++)
        {
            if (str.at(i) >= 'A' && str.at(i) <= 'Z')
            {
                str[i] += 'a' - 'A';
            }
        }
        return str;
    }

    // Is the character one we want in our Word's word?
    static int iswordchar (char ch)
    {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '-' || (ch >= '0' && ch <= '9');
    }
};

#endif
