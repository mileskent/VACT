#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include "sllist.hpp"

using namespace std;
const string filedir = "../res/files/";


SLList<string> slurp (string file)
{
	ifstream ifs (filedir + file, ifstream::in);
	SLList<string> list;
	string wordblock;
	if (ifs.is_open()) 
	{
		while (ifs >> wordblock) 
		{
			list.push_back_node (wordblock);
		}
		ifs.close();
	}
	else list = slurp ("default.txt");
	return list;
}

SLList<string> getdir (string relpath)
{
	SLList<string> texts;
	for (const auto& file : filesystem::directory_iterator{ relpath })  //loop through the current folder
    {
		texts.push_back_node ( file.path().filename() );
    }
	return texts;
}

SLList<string> gettexts ()
{
	return getdir (filedir);
}

#endif
