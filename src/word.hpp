#ifndef WORD_HPP
#define WORD_HPP
#include <string>
#include <vector>

using namespace std;

vector<string> fvec = {"New", "Hard", "Medium", "Easy", "Mastered"};
vector<string> gvec = {"noun", "verb", "adverb", "article", "adjective", "other"};

class Word
{
	public:
		Word ()
		{
			setWord ("Undefined", "Undefined", -1, 0);
		}

		Word (string w, string d, int g)
		{
			setWord (w, d, g);
		}

		Word (string w, string d, int g, int f)
		{
			setWord (w, d, g, f);
		}


		void setWord (string w, string d, int g)
		{			
			word = w;
			definition = d;
			grammar = g;
		}

		void setWord (string w, string d, int g, int f)
		{			
			word = w;
			definition = d;
			grammar = g;
			familiarity = f;
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

		void setword (string w)
		{
			word = w;
		}

		void setdef (string def)
		{
			definition = def;
		}

		void setgrammar (int g)
		{
			if (grammar > gvec.size() -1 ) grammar = gvec.size() -1;
			grammar = g;
		}

		void setfam (int f)
		{
			if (familiarity > fvec.size() -1 ) familiarity = fvec.size() -1;
			familiarity = f;
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

	private:
		string word;
		string definition;
		int grammar;
		int familiarity;
};

#endif
