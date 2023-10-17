/* File path -> String */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


void formatter (string & text, int wraplen)
{
	for (int i = 0; i < text.length(); i++)
	{
		if (text.at(i) == '\n')
		{
			text.erase(i, 1);
		}
	}
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

// return index of nth occurence of char in string
int nthoc(string str, char target, int N)
{
    int occur = 0;
    for (int i = 0; i < str.length(); i++) 
	{
        if (str[i] == target) occur++;
        if (occur == N) return i;
    }
    return -1;
}

// return num of occurences of char in string
int numoc (string str, char target)
{
	int occur = 0;
	for (int i = 0; i < str.length(); i++) if (str.at(i) == target) occur++;
	return occur;
}

// nth string of content string
string nthline (string contents, int N)
{
	// NOTE: string::substr is substr(start, len), not substr(start, end)
	
	/* DEBUG */ cout << "The number of occurence of nl: " << numoc(contents, '\n') << endl;

	if (N == numoc(contents, '\n'))
	{
		return contents.substr(contents.find_last_of("\n"));
	}

	else if (N == 1) return contents.substr(0, nthoc(contents, '\n', 1));
	
	else if (N > 1 && N < numoc(contents, '\n'))
	{
		int start = nthoc(contents, '\n', N - 1) + 1; // + 1 so we don't include \n from prev line
		int len = nthoc(contents, '\n', N) - start;
		return contents.substr(start, len);
	}

	return "";
}

int main (void)
{
	string contents = slurp ("book.txt", 50);
	// cout << contents;
	
	cout << "\"" << nthline (contents, 52) << "\"" << endl;
	/*
	for (int i = 1; i <= 50; i++) 
		cout << "\"" << nthline (contents, i) << "\"" << endl;
	*/
	// Current output messes up with what seems like the second to last line
	
	// TODO: Print from line A to line B
	return 0;
}
