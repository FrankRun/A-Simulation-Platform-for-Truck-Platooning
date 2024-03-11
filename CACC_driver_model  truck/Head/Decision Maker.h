#pragma once
#ifndef __DECISION MAKER_H
#define __DECISION MAKER_H
#include <windows.h>
#include"SimVehicle.h"
#include"Platoon.h"
#include"Link.h"
#include"Control.h"
#include"Eigen\Dense"
#include <map>

using namespace Eigen;
using namespace std;

class DecMaker
{
public:
	DecMaker();
	DecMaker(const int LANE_OFFSET, const int POSITION_OFFSET, long DEFAULT_MAX_PLATOON_SIZE,const int DEFAULT_CACC_MAX_COMMUNICATION_RANGE,double DEFAULT_INNER_PLATOON_HEADWAY,
		const double DEFAULT_INTER_PLATOON_HEADWAY, const int Step_total, double platoonlanechangeposition, double vehiclelanechangedecisiontime,const double ACC_prmts[]);
	~DecMaker();
	bool target(int Step_total, int i, MatrixXd& Lat_position_tar, MatrixXd& Head_angle_tar, MatrixXd Lead_Lat_position_tar, MatrixXd Lead_Head_angle);
	int vehiclePlatooning( SimVehicle& currentVehicle, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, SimVehicle adjacentVehicles[][5]);
	bool useManualDriving(SimVehicle& currentVehicle, map<long, Link>& links);
	int PLCupdate(SimVehicle& currentVehicle, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, map<long, Link>& links);
	int lanechangedecision(MatrixParameter* Mx, SimVehicle& currentVehicle, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons,map<long, Link>& links, SimVehicle adjacentVehicles[][5]);
	double distance(int T1, int T2, double v0, double v1);
private:
	int LANE_OFFSET;				
	int POSITION_OFFSET;			
	long DEFAULT_MAX_PLATOON_SIZE ;
	int DEFAULT_CACC_MAX_COMMUNICATION_RANGE ;	
	double DEFAULT_INNER_PLATOON_HEADWAY ;		
	double DEFAULT_INTER_PLATOON_HEADWAY ;		
	long manualcolor;
	int Step_total ;
	double platoonlanechangeposition ;
	double vehiclelanechangedecisiontime;
	double ACC_prmts[5];
};

#endif