#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> slurp (string file)
{
	ifstream ifs ("../res/files/" + file, ifstream::in);
	vector<string> v;
	string block;
	if (ifs.is_open()) 
	{
		while (ifs >> block) 
		{
			v.push_back (block);
		}
		ifs.close();
	}
	return v;
}

