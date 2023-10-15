/* File path -> String */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string slurp (string file)
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
	return str;
}
