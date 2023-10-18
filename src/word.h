#include <string>

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
	private:
		string word;
		string definition;
		int grammar;
};
