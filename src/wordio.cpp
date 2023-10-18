#include <fstream>
#include <iostream>
#include <vector>

#include "word.h"

using namespace std;

int pullwords ();
int pushwords ();
vector<Word> runtimeWords;

int main (void)
{
	pullwords ();
	cout << "Printing rtw: \n";
	for (int i = 0; i < runtimeWords.size(); i++)
	{
		cout << "Word: " << runtimeWords.at(i).getword() << " Def: " << runtimeWords.at(i).getdefinition() << " G: " << runtimeWords.at(i).getgrammar() << endl;
	}
	cout << "Adding word\n";
	runtimeWords.push_back (Word("million", "1,000,000", 0));
	pushwords();
	cout << "Pushed words\n";
	return 0;
}

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
			temp.setgrammar (stoi(istring.substr(start)));

			runtimeWords.push_back (temp);
			id++;
		}
		file.close();
	}
	else return 1;
	return 0;
}

int pushwords()
{
	ofstream file;
	// clear the file
	file.open("../res/dictionary/dict.vact", ofstream::out | ofstream::trunc);
	file.close();

	file.open("../res/dictionary/dict.vact", ios::app); // append mode
	if (file.is_open())
	{
		for (int id = 0; id < runtimeWords.size(); id++)
		{
			Word temp = runtimeWords.at(id);
			cout << "Wrote " << temp.getword() << " to the dictionary." << endl;
			file << temp.getword() << ";" << temp.getdefinition() << ";" << temp.getgrammar() << endl;
		}
		file.close();
	}
	else return 1; 
	return 0;
}
