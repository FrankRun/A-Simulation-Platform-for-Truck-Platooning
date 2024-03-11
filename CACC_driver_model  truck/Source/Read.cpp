#include "READ.h"

using namespace std;
map<long, Link> READ::Links;

READ::READ()
{

}
READ::~READ()
{

}

vector<string> READ::splitstr(string s, string spilt)
{
	vector<string> ret;
	size_t last = 0;
	size_t index = s.find_first_of(spilt, last);
	while (index != std::string::npos)
	{
		ret.push_back(s.substr(last, index - last));
		last = index + 1;
		index = s.find_first_of(spilt, last);
	}
	if (index - last > 0)
	{
		ret.push_back(s.substr(last, index - last));
	}
	return ret;
}

void READ::saveInfogui(string ms, long& maxplatoonlength, double& headway, double& safedistance, double& platoonlanechangeposition, double& vehiclelanechangedecisiontime)
{
	vector<string> elements;

	elements = READ::splitstr(ms, ",");
	int index = 0;
	for (vector<string>::iterator pos = elements.begin(); pos != elements.end(); ++pos) {
		string element = *pos;
		index++;
		switch (index)
		{
		case 1: maxplatoonlength = atoi(element.c_str());
		case 2: headway = atof(element.c_str());
		case 3: safedistance = atof(element.c_str());
		case 4: platoonlanechangeposition = atof(element.c_str());
		case 5: vehiclelanechangedecisiontime = atof(element.c_str());

		default:
			break;
		}
	}
}

void READ::saveInfolink(string ms)
{
	vector<string> elements;
	long No = 0;
	long isConn = 0;
	long LanesNum = 0;
	long LinkFrom = 0;
	long LaneFrom = 0;
	double posFrom = 0;
	long LinkTo = 0;
	long LaneTo = 0;
	double posTo = 0;
	double length = 0;

	elements = READ::splitstr(ms, ",");
	int index = 0;
	for (vector<string>::iterator pos = elements.begin(); pos != elements.end(); ++pos) {
		string element = *pos;
		index++;
		switch (index)
		{
		case 1: No = atoi(element.c_str());
		case 2: isConn = atoi(element.c_str());
		case 3: LanesNum = atoi(element.c_str());
		case 4: LinkFrom = atoi(element.c_str());
		case 5: LaneFrom = atoi(element.c_str());
		case 6: posFrom = atof(element.c_str());
		case 7: LinkTo = atoi(element.c_str());
		case 8: LaneTo = atoi(element.c_str());
		case 9: posTo = atof(element.c_str());
		case 10: length = atof(element.c_str());
		default:
			break;
		}
	}
	Link newLink = Link(No, isConn, LanesNum, length, LinkFrom, LaneFrom, posFrom,
		LinkTo, LaneTo, posTo);
	READ::AddLink(newLink);
}

void READ::AddLink(Link newLink)
{
	Links[newLink.No] = newLink;
}

map<long, Link> READ::GetLinks()
{
	return Links;
}