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
/*
int pushwords()
{
	ofstream file;
	// clear the file
	file.open("bookings.tbkr", ofstream::out | ofstream::trunc);
	file.close();
	file.open("bookings.tbkr", ios::app); // append mode
	if (file.is_open())
	{
	for (int id = 0; id < MAX_BOOKINGS; id++)
	{
	  if(bookingNum[id].name.empty()) break;
	  else 
	  {
		// cout << "Wrote " << bookingNum[id].name << "'s booking to the file" << endl;
		file << bookingNum[id].name << ";" << bookingNum[id].origin << ";" 
		  << bookingNum[id].destination << ";" << bookingNum[id].date << endl;
	  }
	}
	file.close();
	}
	else return 1; 
	return 0;
}
*/
