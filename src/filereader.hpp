#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

using namespace std;
const string filedir = "../res/files/";


vector<string> slurp (string file)
{
	ifstream ifs (filedir + file, ifstream::in);
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
	else v = slurp ("default.txt");
	return v;
}

vector<string> getdir (string relpath)
{
	vector<string> texts;
	for (auto & file : filesystem::directory_iterator{ relpath })  //loop through the current folder
    {
		texts.push_back ( file.path().filename() );
    }
	return texts;
}

vector<string> gettexts ()
{
	return getdir (filedir);
}

#endif
