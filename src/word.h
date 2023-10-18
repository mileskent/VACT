#ifndef WORD_H
#define WORD_H
#include <string>

using namespace std;

class Word
{
	public:
		Word ()
		{
			setWord ("Undefined", "Undefined", -1);
		}

		Word (string w, string d, int g)
		{
			setWord (w, d, g);
		}

		void setWord (string w, string d, int g)
		{			
			word = w;
			definition = d;
			grammar = g;
		}

		string getword ()
		{
			return word;
		}

		string getgrammar ()
		{
			string g[] = {"noun", "verb", "adverb", "article", "adjective", "other"};
			if (grammar < 0) return "Undefined";
			else return g[grammar];
		}

		string getdefinition ()
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
			grammar = g;
		}

	private:
		string word;
		string definition;
		int grammar;
};

#endif
