/*==========================================================================*/
/*  Log.h                                 for Driver DLL Module for VISSIM  */
/*                                                                          */
/*  Class build for easy exporting log info into local log file.            */
/*                                                                          */
/*  Version of 2017-8-25                                   Yi Zhao          */
/*==========================================================================*/

#pragma once

#ifndef __LOG_H
#define __LOG_H

#ifndef _LOGS
#include <string>
#include <map>
#include <vector>
#include "SimVehicle.h"
#include "Platoon.h"
#include "Link.h"
#endif // !_LOGS

class Log
{
public:
	Log();
	~Log();
	static int logging(std::string str);
	static int logging(std::string filename,std::string str);
	static int logging(char* charPtr);
	static int inifile(std::string filename);
	static int gettext(std::string filename, std::string &str);
	static std::string getCurrentTimeToString();
	static void printVehicleInfo(SimVehicle veh);
	static void printPlatoonsInfo(std::map<int, Platoon> plt);
	static void printVehsInPlatoon(Platoon plt);
	static void printLinksInfo(Link link);
	static vector<string> splitstr(string s, string spilt);
};
#endif
