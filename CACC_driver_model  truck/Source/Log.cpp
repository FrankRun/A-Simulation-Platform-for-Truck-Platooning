/*==========================================================================*/
/*  Log.cpp                               for Driver DLL Module for VISSIM  */
/*                                                                          */
/*  Class build for easy exporting logs into local file.                    */
/*                                                                          */
/*  Version of 2017-8-25                                   Yi Zhao          */
/*==========================================================================*/

#include "Log.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <sstream>


using namespace std;

Log::Log()
{
}


Log::~Log()
{
}

int Log::logging(std::string str)
{
	ofstream outputFile = ofstream("logs.txt", ios::out | ios::app);
	if (outputFile.is_open()) {
		//outputFile << "\n##########Start Logging, current time is: " << getCurrentTimeToString();
		outputFile << str;
		//outputFile << "##########End of the log.\n\n";
		outputFile.close();
		return 1;
	}
	else {
		cout << "Unable to open file";
		return 0;
	}
}

int Log::logging(std::string filename, std::string str)
{

	ofstream outputFile = ofstream(filename, ios::out | ios::app);
	if (outputFile.is_open()) {
		//outputFile << "\n##########Start Logging, current time is: " << getCurrentTimeToString();
		outputFile << str;
		//outputFile << "##########End of the log.\n\n";
		outputFile.close();
		return 1;
	}
	else {
		cout << "Unable to open file";
		return 0;
	}
	return 0;
}


int Log::gettext(std::string filename, std::string &str)
{
	ifstream inf("as");
	stringstream ss;
	if (inf.is_open()) {
		inf >> str;
		inf.close();
	}
	return 0;
}

int Log::logging(char * charPtr)
{
	string tmpStr = string(charPtr);
	return logging(tmpStr);
}

int Log::inifile(std::string filename)
{
	ofstream myfile(filename, ios::out | ios::app);
	myfile = ofstream(filename, ios::out | ios::trunc);
	myfile.is_open();
	myfile.close();
	myfile = ofstream(filename, ios::out | ios::app);
	return 0;
}

std::string Log::getCurrentTimeToString()
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	string rStr = "";
	rStr += asctime(timeinfo);
	return rStr;
}

void Log::printVehicleInfo(SimVehicle veh) {

	stringstream ss;

	ss << "id " << veh.id << "; type " << veh.type << "; platoonState " << veh.platoonState << "; platoonID " << veh.platoonID <<
		"; color " << veh.color << "; time " << veh.time << "; linkNumber " << veh.currentLink << "; laneNumber " << veh.currentLane <<
		"; speed " << veh.speed << "; acceleration " << veh.acceleration << "; desiredSpeed " << veh.desiredSpeed << "; desiredAcceleration " << veh.desiredAcceleration <<
		"; previousStepSpeed " << veh.previousSpeed << "; previousAcceleration " << veh.previousAcceleration << "; previousHeadwayDistance " << veh.previousHeadwayDistance <<
		"; laneAngle " << veh.laneAngle << "; desiredLaneAngle " << veh.desiredLaneAngle << "; headwayDistance " << veh.headwayDistance << "; length " << veh.length <<
		"; width " << veh.width << "; currentLane " << veh.currentLane << "; targetLane " << veh.relativeTargetLane << "; activeLaneChange " << veh.activeLaneChange <<
		"; turningIndicator " << veh.turningIndicator << "; platoonState " << veh.platoonState << "; platoonID " << veh.platoonID <<"  latral position:"<<veh.lateralPosition<< ". \n";
	logging(ss.str());
}

void Log::printPlatoonsInfo(map<int, Platoon> plt)
{
	stringstream ss;
	ss << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
	ss << "There are " << plt.size() << " platoons in the list." <<endl;
	for (int pltID = 1; pltID <= plt.size(); pltID++)
	{
		ss << "id " << plt[pltID].id << "; leadVehicleID " << plt[pltID].leadVehicleID << "; size " << plt[pltID].size <<
			"; Size " << plt[pltID].size << "; maxSize " << plt[pltID].maxSize <<
			"; leadingVehiclePosition " << plt[pltID].leadingVehiclePosition <<
			"; caccMaxCommunicationRange " << plt[pltID].caccMaxCommunicationRange <<
			"; targetInnerPlatoonHeadway " << plt[pltID].targetInnerPlatoonHeadway <<
			"; targetInterPlatoonHeadway " << plt[pltID].targetInterPlatoonHeadway <<". \n";
		for (int vehs = 0; vehs < plt[pltID].vehiclesIDList.size(); vehs++)
		{
			ss << "	Vehicle ID List- No: " << vehs << " is " << plt[pltID].vehiclesIDList[vehs] << "\n";
		}
	}
	ss << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
	logging(ss.str());
}

void Log::printVehsInPlatoon(Platoon plt)
{
	stringstream ss;
	ss << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
	ss << "This platoon contains the following vehs: \n";
	for (int i = 0; i < plt.size; i++)
	{
		ss << plt.vehiclesIDList[i] << " --> ";
	}
	ss << "the end. \n";
	ss << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ \n";
	logging(ss.str());
}

void Log::printLinksInfo(Link link)
{
	stringstream ss;
	ss << "~~~~~~~~~~~~~~~~~~~~LinkInfo~~~~~~~~~~~~~~~~~~~~~~~~ \n";
	ss << link.No << " | " << link.isConn << " | " << link.LanesNum << " | " << link.LinkFrom << " | " << link.LaneFrom<< " | "<< link.posFrom << " | " << link.LinkTo << " | " << link.LaneTo << " | " << link.posTo << " | " << link.Length <<"\n";
	logging(ss.str());
}

vector<string> Log::splitstr(string s, string spilt)
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