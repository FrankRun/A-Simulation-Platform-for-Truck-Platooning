/*==========================================================================*/
/*  Platoon.h                             for Driver DLL Module for VISSIM  */
/*                                                                          */
/*  The abstract class which defines some basic properties of the platoon   */
/*  class. The following xx virtual methods should be implemented by users  */
/*  in the self defined inheriated class.                                   */
/*                                                                          */
/*  Version of 2023-8-25                                   Xuerun Yan          */
/*==========================================================================*/

#pragma once
#ifndef __PLATOON_H
#define __PLATOON_H

#include <vector>
#include <list>
#include "SimVehicle.h"
#include"Eigen\Dense"

using namespace std;
using namespace Eigen;

class Platoon
{
public:
	long id;
	long leadVehicleID;
	std::vector<long> vehiclesIDList;   //vehicle id list in platoon
	int maxSize;
	int size;
	int caccMaxCommunicationRange;
	double leadingVehiclePosition;
	double targetInnerPlatoonHeadway;
	double targetInterPlatoonHeadway;

	long currentlane; 
	long targetlane;
	long turndirection;
	long obstaclestate;
	long platoonlanechangestate;
	double londistance; 
	double platoonlength;

	Matrix<double, 1, 200> Lead_Lat_position_tar = MatrixXd::Ones(1,200);
	Matrix<double, 1, 200> Lead_Head_angle = MatrixXd::Zero(1,200);

	static int maxPlatoonID;
	
	Platoon();
	/*    parameters:
	* maxCommunicationRange: Suggested communication range for DSRC or LTE, in meters, 200 meters for default
	* innerPlatoonHeadway: time headway between two vehicles in the platoon, in seconds, 0.6 second for default
	* interPlatoonHeadway: time headway between two platoons, in seconds, 1.5 second for default
	*/
	Platoon(long leadingVehID, double leadingVehiclePosition, long leadingVehiclelane, int maxPlatoonSize = 10, int caccMaxCommunicationRange = 200,
		double innerPlatoonHeadway = 0.6, double interPlatoonHeadway= 1.5);

    virtual ~Platoon();

	virtual bool vehicleBackJoin(SimVehicle &veh);
	virtual bool platoonBackJoin(map<int, Platoon> &platoons, int platoonIDJoinFrom, int platoonIDJoinTo, map<long, SimVehicle> & vehiclesInNet);
	virtual bool splitPlatoon(map<int, Platoon> &platoons, int platoonID, long splitAt, map<long, SimVehicle> & vehiclesInNet);
	virtual bool leavePlatoon(SimVehicle veh);
	virtual int getNumInPlatoon(long vehicleID);
	virtual double getPositionInPlatoon(map<long,SimVehicle> &vehiclesInNet,long ID);
	virtual long getBackIDof(long);
	virtual long getFrontIDof(long);
	virtual void setplatoonlength(map<long, SimVehicle>& vehiclesInNet);
	virtual long  getlastIDof();
	

	bool isNotFull();

	virtual void setcurrentlane(long current_lane);
	virtual void settargetlane(long target_lane);
	virtual void setturndirection(long turn_direction);
	virtual void setobstaclestate(long obstacle_state);
	virtual void setlondistance(double lon_distance);
	virtual void setleadlatpositiontar(long i, double Lat_position_error);
	virtual void setleadheadangle(long i, double head_angle_error);
	virtual void setplatoonlanechangestate(long state);
	virtual bool lanechangejudgment(map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, int platoonID);
	virtual bool lanechangereturnjudgment(map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, int platoonID);
};

#endif
