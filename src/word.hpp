#ifndef WORD_HPP
#define WORD_HPP
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> fvec = {"New", "Hard", "Medium", "Easy", "Mastered"};
const vector<string> gvec = {"noun", "verb", "adverb", "article", "adjective", "other"};

class Word
{
	public:
		Word ()
		{
			setWord ("Undefined", "Undefined", -1, 0);
		}

		Word (string word, string definition, int grammar)
		{
			setWord (word, definition, grammar);
            this->familiarity = 0;
		}

		Word (string word, string definition, int grammar, int familiarity)
		{
			setWord (word, definition, grammar, familiarity);
		}


		void setWord (string word, string definition, int grammar)
		{			
			this->word = word;
			this->definition = definition;
			this->grammar = grammar;
		}

		void setWord (string word, string definition, int grammar, int familiarity)
		{			
			this->word = word;
			this->definition = definition;
			this->grammar = grammar;
			this->familiarity = familiarity;
		}


		string getword () const
		{
			return word;
		}

		string getgrammar () const
		{
			if (grammar < 0) return "Undefined";
			return gvec[grammar];
		}

		int getigrammar () const
		{
			return grammar;
		}

	
		string getfamiliarity () const
		{
			if (familiarity < 0) return "Undefined";
			return fvec[familiarity];
		}

		int getifamiliarity () const
		{
			return familiarity;
		}


		string getdefinition () const
		{
			return definition;
		}

		void setword (string word)
		{
			this->word = word;
		}

		void setdef (string definition)
		{
			this->definition = definition;
		}

		void setgrammar (int grammar)
		{
			if (this->grammar > gvec.size() -1 ) this->grammar = gvec.size() -1;
			this->grammar = grammar;
		}

		void setfam (int familiarity)
		{
			if (this->familiarity > fvec.size() -1 ) this->familiarity = fvec.size() -1;
			this->familiarity = familiarity;
		}
		
		// only care about title (word) of entry
		// this is used for removing dupes and such so we want to eval is true even if grammar et al doesnt match
		// no situation where having two entries with same title and diff def is good
		bool operator==(const Word & other) const 
		{
			return word == other.word;
		}
		
		bool operator==(const string & other) const 
		{
			return word == other;
		}

        std::string getinfo () const {
            return "Verb: " + word + 
                ", Definition: " + definition + 
                ", Grammar: " + this->getgrammar() + 
                ", Familiarity: " + this->getfamiliarity();
        }


        // Defines behavior for printing a word
        friend std::ostream& operator<<(std::ostream& os, const Word& word) { 
            return os << "Word: " << word.getword();
        }
        

	private:
		string word;
		string definition;
		int grammar;
		int familiarity;
};


#endif
