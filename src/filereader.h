/* File path -> String */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void formatter (string & text, int wraplen)
{
	int a = 0;
	char c;
	while (a + wraplen < text.length())
	{
		a += wraplen;
		char c = text.at(a);
		if (c == ' ')
		{
			text[a] = '\n';
		}
		else
		{
			while (c != ' ')
			{
				c = text.at(--a);
			}
			text[a] = '\n';
		}
	}
}

string slurp (string file, int wraplen)
{
	ifstream ifs ("../res/" + file, ifstream::in);
	string str, line;
	if (ifs.is_open()) 
	{
		while (getline(ifs, line)) 
		{
			str.append(line);
		}
		ifs.close();
	}
	formatter (str, wraplen);
	return str;
}

