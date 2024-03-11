#pragma once
#ifndef __READ_H
#define __READ_H

#include <vector>
#include <string>
#include <map>
#include "Link.h"

using namespace std;

class READ
{
public:
	READ();
	~READ();
	vector<string> splitstr(string s, string spilt);
	void saveInfogui(string ms, long& maxplatoonlength, double& headway, double& safedistance, double& platoonlanechangeposition, double& vehiclelanechangedecisiontime);

	void saveInfolink(string ms);
	static void AddLink(Link newLink);
	static map<long, Link> GetLinks();
	static map<long, Link> Links;
};



#endif // !__GUI_H