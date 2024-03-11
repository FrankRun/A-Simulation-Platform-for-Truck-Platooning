/*==========================================================================*/
/*  Platoon.cpp                           for Driver DLL Module for VISSIM  */
/*                                                                          */
/*  The abstract class which defines some basic properties of the platoon   */
/*  class. The following xx virtual methods should be implemented by users  */
/*  in the self defined inheriated class.                                   */
/*                                                                          */
/*  Version of 2023-8-25                                   Xuerun Yan          */
/*==========================================================================*/

#include "Platoon.h"
#include "SimVehicle.h"

int Platoon::maxPlatoonID = 0;

Platoon::Platoon()
{
	
}

Platoon::Platoon(long leadingVehID, double leadingVehiclePosition, long leadingVehiclelane, int maxPlatoonSize, int caccMaxCommunicationRange,
	double innerPlatoonHeadway, double interPlatoonHeadway):
	id(0), leadVehicleID(leadingVehID), leadingVehiclePosition(leadingVehiclePosition), size(0), maxSize(maxPlatoonSize),
	caccMaxCommunicationRange(caccMaxCommunicationRange), targetInnerPlatoonHeadway(innerPlatoonHeadway), 
	targetInterPlatoonHeadway(interPlatoonHeadway),currentlane(leadingVehiclelane),platoonlanechangestate(0)
{
	maxPlatoonID++;
	id = maxPlatoonID;
	vehiclesIDList.push_back(leadingVehID);
	size++;
}


Platoon::~Platoon()
{
}

//vehicle joins the preceding platoon
bool Platoon::vehicleBackJoin(SimVehicle &veh)
{
	this->size++;
	this->vehiclesIDList.push_back(veh.id);
	return true;
}

//two platoon formation
bool Platoon::platoonBackJoin(map<int, Platoon> &platoons, int platoonIDJoinFrom, int platoonIDJoinTo, map<long, SimVehicle> & vehiclesInNet)
{
	Platoon from = platoons[platoonIDJoinFrom];
	Platoon to = platoons[platoonIDJoinTo];
	if (to.vehiclesIDList.size()==0) 
	{
		return false;
	}
	Platoon newPlt = Platoon(to.leadVehicleID, to.leadingVehiclePosition,to.currentlane, from.maxSize,
		from.caccMaxCommunicationRange, from.targetInnerPlatoonHeadway, from.targetInterPlatoonHeadway);
	platoons[newPlt.id] = newPlt;

	for (vector<long>::iterator vehPos = ++to.vehiclesIDList.begin(); vehPos != to.vehiclesIDList.end();++vehPos) 
	{ 
		platoons[newPlt.id].size++;
		platoons[newPlt.id].vehiclesIDList.push_back(*vehPos);   
	}
	for (vector<long>::iterator vehPos = from.vehiclesIDList.begin(); vehPos != from.vehiclesIDList.end(); ++vehPos) 
	{
		platoons[newPlt.id].size++;
		platoons[newPlt.id].vehiclesIDList.push_back(*vehPos); 
	}
	//update the id
	for (vector<long>::iterator vehPos = from.vehiclesIDList.begin(); vehPos != from.vehiclesIDList.end(); ++vehPos) 
	{
		vehiclesInNet[*vehPos].platoonID = newPlt.id;
	}
	for (vector<long>::iterator vehPos = to.vehiclesIDList.begin(); vehPos != to.vehiclesIDList.end(); ++vehPos) 
	{
		vehiclesInNet[*vehPos].platoonID = newPlt.id;
	}
	
	platoons[newPlt.id].currentlane = to.currentlane;
	platoons[newPlt.id].targetlane = to.targetlane;
	platoons[newPlt.id].turndirection = to.turndirection;
	platoons[newPlt.id].platoonlanechangestate = to.platoonlanechangestate;
	platoons[newPlt.id].Lead_Lat_position_tar = to.Lead_Lat_position_tar;
	platoons[newPlt.id].Lead_Head_angle = to.Lead_Head_angle;
	platoons[newPlt.id].obstaclestate = to.obstaclestate;
	platoons[newPlt.id].londistance = to.londistance;

	platoons.erase(platoonIDJoinFrom);
	platoons.erase(platoonIDJoinTo);
	return true;
}

//platoon spliting
bool Platoon::splitPlatoon(map<int, Platoon> &platoons, int platoonID, long splitAt, map<long, SimVehicle> &vehiclesInNet)
{

	bool HeadError=(platoons[platoonID].leadVehicleID==splitAt);
	if (HeadError) return false;
	Platoon frontPlt = Platoon(platoons[platoonID].leadVehicleID, platoons[platoonID].leadingVehiclePosition, platoons[platoonID].currentlane,platoons[platoonID].maxSize,
		platoons[platoonID].caccMaxCommunicationRange, platoons[platoonID].targetInnerPlatoonHeadway, platoons[platoonID].targetInterPlatoonHeadway);
	Platoon backPlt = Platoon(splitAt, platoons[platoonID].leadingVehiclePosition, platoons[platoonID].currentlane,platoons[platoonID].maxSize,
		platoons[platoonID].caccMaxCommunicationRange, platoons[platoonID].targetInnerPlatoonHeadway, platoons[platoonID].targetInterPlatoonHeadway);
	platoons[frontPlt.id] = frontPlt;
	platoons[backPlt.id] = backPlt;
	bool isFront = true;
	for (vector<long>::iterator vehPos = platoons[platoonID].vehiclesIDList.begin(); vehPos != platoons[platoonID].vehiclesIDList.end(); ++vehPos) {
		if (*vehPos == splitAt) {
			isFront = false; continue;
		}
		if (isFront) {
			if (*vehPos == platoons[platoonID].leadVehicleID) continue;
			platoons[frontPlt.id].size++;
			platoons[frontPlt.id].vehiclesIDList.push_back(*vehPos);   
		}
		else {
			platoons[backPlt.id].size++;
			platoons[backPlt.id].vehiclesIDList.push_back(*vehPos); 
		}
	}
	Platoon oldPlt = platoons[platoonID];
	isFront = true;
	for (vector<long>::iterator vehPos = oldPlt.vehiclesIDList.begin(); vehPos != oldPlt.vehiclesIDList.end(); ++vehPos) {
		if (*vehPos == splitAt) isFront = false;
		if (isFront)	vehiclesInNet[*vehPos].platoonID = frontPlt.id;
		else vehiclesInNet[*vehPos].platoonID = backPlt.id;
	}
	platoons[frontPlt.id].currentlane = vehiclesInNet[platoons[frontPlt.id].leadVehicleID].currentLane;  
	platoons[backPlt.id].currentlane = vehiclesInNet[platoons[backPlt.id].leadVehicleID].currentLane;
	platoons[frontPlt.id].targetlane = platoons[platoonID].targetlane;
	platoons[backPlt.id].targetlane= platoons[platoonID].targetlane;
	if (platoons[frontPlt.id].lanechangejudgment(vehiclesInNet,platoons,frontPlt.id)==0 ) 
	{
		platoons[frontPlt.id].platoonlanechangestate = 1;
		platoons[frontPlt.id].Lead_Lat_position_tar = platoons[platoonID].Lead_Lat_position_tar;
		platoons[frontPlt.id].Lead_Head_angle = platoons[platoonID].Lead_Head_angle;
		platoons[frontPlt.id].obstaclestate = platoons[platoonID].obstaclestate;
		platoons[frontPlt.id].londistance = platoons[platoonID].londistance;
		platoons[frontPlt.id].currentlane = platoons[platoonID].currentlane;
	}
	platoons.erase(platoonID);
	return true;
}

bool Platoon::leavePlatoon(SimVehicle veh) 
{
	if (this->size == 1)
	{
		this->size--;
		return true;
	}
	if (veh.id == this->leadVehicleID)
	{
		vector<long>::iterator leadingVehPos = vehiclesIDList.begin();
		leadingVehPos=vehiclesIDList.erase(leadingVehPos);
		if (vehiclesIDList.size()!=0)
		{
			this->leadVehicleID = vehiclesIDList[0];
		}
		this->size--;
	}else
	{
		for (vector<long>::iterator vehPos = vehiclesIDList.begin(); vehPos != vehiclesIDList.end(); ++vehPos)
		{
			if (*vehPos == veh.id)
			{
				vehPos = vehiclesIDList.erase(vehPos);
				this->size--;
				break;
			}
		}
	}
	return true;
}


int Platoon::getNumInPlatoon(long vehicleID) {
	int no = 1;
	for (vector<long>::iterator vehPos = vehiclesIDList.begin(); vehPos != vehiclesIDList.end(); ++vehPos)
	{
		if (*vehPos == vehicleID)
		{
			return no;
		}
		no++;
	}
	return 0;
}

double Platoon::getPositionInPlatoon(map<long, SimVehicle>& vehiclesInNet, long ID)
{
	double distance=0;
	if (ID == leadVehicleID) return distance;
	for (vector<long>::iterator vehPos = this->vehiclesIDList.begin(); vehPos != this->vehiclesIDList.end();++vehPos )
	{
		if (*vehPos == leadVehicleID) continue;
		long tempID = *vehPos;
		if (this->platoonlanechangestate==0)
		{
			if (tempID != ID)
			{
				distance -= vehiclesInNet[tempID].getHeadwayDistance();
			}
			else 
			{
				distance -= vehiclesInNet[tempID].getHeadwayDistance(); 
				break;
			}
		}
		else
		{
			if (tempID != ID)
			{
				distance -= (vehiclesInNet[*(vehPos - 1)].PosInLink - vehiclesInNet[tempID].PosInLink); 
			}
			else
			{
				distance -= (vehiclesInNet[*(vehPos - 1)].PosInLink - vehiclesInNet[tempID].PosInLink); 
				break;
			}
		}
	}
	return distance;
} 

void Platoon::setplatoonlength(map<long, SimVehicle>& vehiclesInNet)
{
	this->platoonlength = 0;
	for (vector<long>::iterator vehPos = this->vehiclesIDList.begin(); vehPos != this->vehiclesIDList.end(); ++vehPos)
	{
		if (vehPos != this->vehiclesIDList.begin())
		{
			this->platoonlength += vehiclesInNet[*vehPos].getHeadwayDistance();  
		}
		if (vehPos == (this->vehiclesIDList.end() - 1))
		{
			this->platoonlength += vehiclesInNet[*vehPos].getLength();
		}
	}
}

long Platoon::getBackIDof(long ID)
{
	bool isTarg = false;
	for (vector<long>::iterator vehPos = this->vehiclesIDList.begin(); vehPos != this->vehiclesIDList.end(); ++vehPos)
	{
		long temp = *vehPos;
		if (isTarg) return temp;
		if (temp == ID) isTarg = true;
	}
	return 0;
}

long Platoon::getFrontIDof(long ID)
{
	bool isTarg = false;
	long lastID = 0;
	for (vector<long>::iterator vehPos = this->vehiclesIDList.begin(); vehPos != this->vehiclesIDList.end(); ++vehPos)
	{
		long temp = *vehPos;
		if (temp == ID) return lastID;
		lastID = *vehPos;
	}
	return 0;
}
long Platoon::getlastIDof()
{
	long lastID = 0;
	if (this->vehiclesIDList.size() != 0)
	{
		lastID = *(this->vehiclesIDList.end() - 1); 
	}
	return lastID;
}


bool Platoon::isNotFull()
{
	return (size < maxSize);
}

void Platoon::setcurrentlane(long current_lane)
{
	this->currentlane = current_lane;
}

void Platoon::settargetlane(long target_lane)
{
	this->targetlane = target_lane;
}
void Platoon::setturndirection(long turn_direction)
{
	this->turndirection = turn_direction;
}
void Platoon::setobstaclestate(long obstacle_state)
{
	this->obstaclestate = obstacle_state;
}
void Platoon::setlondistance(double lon_distance)
{
	this->londistance = lon_distance;
}
void Platoon::setleadlatpositiontar(long i, double Lat_position_error)
{
	this->Lead_Lat_position_tar(0, i) = Lat_position_error;
}
void Platoon::setleadheadangle(long i, double head_angle_error)
{
	this->Lead_Head_angle(0, i) = head_angle_error;
}
void Platoon::setplatoonlanechangestate(long state)
{
	this->platoonlanechangestate=state;
}
bool Platoon::lanechangejudgment(map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, int platoonID)  
{
	long currentlane;
	long currentlink;
	if (platoons[platoonID].vehiclesIDList.size() != 0)
	{
		currentlane = vehiclesInNet[platoons[platoonID].leadVehicleID].currentLane; 
		currentlink = vehiclesInNet[platoons[platoonID].leadVehicleID].currentLink;
	}
	else
	{
		return true;
	}
	for (vector<long>::iterator vehPos = platoons[platoonID].vehiclesIDList.begin(); vehPos != platoons[platoonID].vehiclesIDList.end(); ++vehPos)
	{

		if (vehiclesInNet[*vehPos].MPCstep!=0 || (vehiclesInNet[*vehPos].currentLane!= currentlane && vehiclesInNet[*vehPos].currentLink == currentlink))  
		{
			return false;
		}
	}
	return true;
}

bool Platoon::lanechangereturnjudgment(map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, int platoonID)  
{

	for (vector<long>::iterator vehPos = platoons[platoonID].vehiclesIDList.begin(); vehPos != platoons[platoonID].vehiclesIDList.end(); ++vehPos)
	{

		if (vehiclesInNet[*vehPos].MPCstep!= 0 )  
		{
			return false;
		}
	}
	return true;
}


