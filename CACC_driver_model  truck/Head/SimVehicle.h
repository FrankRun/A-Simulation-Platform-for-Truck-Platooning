/*==========================================================================*/
/*  SimVehicle.h                          for Driver DLL Module for VISSIM  */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Version of 2023-8-25                                   Xuerun Yan          */
/*==========================================================================*/

#pragma once

#ifndef __SIMVEHICLE_H
#define __SIMVEHICLE_H

#include <map>
#include"Eigen\Dense"


using namespace std;
using namespace Eigen;

class Platoon;
class SimVehicle
{
public:
	double timestep;
	long id;
	long type;
	double time;
	long color;
	double length;
	double width;
	long platoonState;		// 0: Waiting for platoon; 1: Leading vehicle; 2: Following vehicle; 3: Left platoon; 4: Not suitable for platoon
	long platoonID;
	long followingcolor;

	double speed;
	double acceleration;
	double headwayDistance;
	int controlState;				//user can self-define it for the control state; 0 is default value.

	double previousSpeed;
	double previousAcceleration;
	double previousHeadwayDistance;
	int previousControlState;
	double previousDistanceTravelled;
	double previousDesiredAcceleration; 
	double previousDesiredSpeed; 
	double previousPlatoonState; 
	long previouslane; 

	long previousFrontVehicle;

	double desiredSpeed;
	double desiredAcceleration;

	double laneAngle;
	double desiredLaneAngle;

	long currentLink;
	long nextLink;         
	long currentLane;		//1 for right most lane
	long relativeTargetLane;
	long vehrelativeTargetLane;
	long lanesOfCurrentLink; 

	long activeLaneChange;
	long vehactiveLaneChange;
	long turningIndicator;
	
	double distanceTravelled;
	double lateralPosition;
	double weigth;
	double maxAcceleration;
	long vehicleCategory;
	long preferredRelativeLane;
	long usePreferredLane;
	double	vehXCoordinate;
	double vehYCoordinate;
	double	vehRearXCoordinate;
	double vehRearYCoordinate;

	double PosInLink;  
	long lastLink;		
	double DTBeforeNode;  
	double lastlinktopos;
	
	long usesimplelanechange;
	long useinternalmodel;
	long wantsuggestion;

	long vehIntacState; //details in DriverModel.h
	long vehIntacTargetType; //details in DriverModel.h
	long vehIntacTargetID; //details in DriverModel.h
	long vehIntacHeadway; //details in DriverModel.h
	

	double MinDedeceleration;
	
	double intial_speed;	
	double as;

	int timeIntoCACC;

	double accDuringTransition;
	//MPC parameters
	long   MPCstep ;
	double wheelangle  ;
	long   lanechangestate ;
	long   returnlanestate ;
	double lanewidth;
	long   manualstate;
	long   decisiontime;

	int step;
	int VDMdisabledtime; 

	enum PlatoonStates 
	{
		PlatoonStateWaitingForPlatooning = 0,
		PlatoonStatePlatoonLeading = 1,
		PlatoonStatePlatoonFollowing = 2,
		PlatoonStatePlatoonLeaving = 3,  
		PlatoonStateVehTypeIsNotForPlatooning = 4, 
		PlatoonStatePlatoonLanechange = 5,
		PlatoonStatePlatoonLanechangereturn = 6

	};

	enum ControlStates   
	{
		ControlStateVISSIM = 0,
		ControlStateCAVFreeDriving = 1,
		ControlStateACCGapRegulation = 2,
		ControlStateACCSpeedRegulation = 3,
		ControlStateCACCGapRegulation = 4,
		ControlStateCACCSpeedRegulation = 5,
		ControlStateCACCKill = 6
	};

	enum VehType
	{
		VehTypeRegularCar=100,
		VehTypeRegualrTruck = 200,
		VehTypeCACC = 700,
		VehTypeCVwithoutCACC = 800
	};

	SimVehicle();
	~SimVehicle();

	virtual SimVehicle::PlatoonStates determinVehPlatooningState(SimVehicle previouVeh,  map<int, Platoon>& platoonList, map<long, SimVehicle>& vehiclesInNet);
	void SimVehicle::reInit();
	bool SimVehicle::updatePreviousStates(SimVehicle statesFromVeh);
	void setLCcontrolparaszero();

	double gettimestep();
	void settimestep(double timestep);

	int getId();
	void setId(long id);

	long getType();
	void setType(long type);

	double getTime();
	void setTime(double time);

	long getColor();
	void setColor(long color);

	double getLength();
	void setLength(double length);

	double getWidth();
	void setWidth(double width);

	double getWeight();
	void setWeight(double weight);

	long getPlatoonState();
	void setPlatoonState(long platoonState);

	long getPlatoonID();
	void setPlatoonID(long platoonID);

	double getDesiredSpeed();
	void setDesiredSpeed(double desiredSpeed);

	double getDesiredAcceleration();
	void setDesiredAcceleration(double desiredAcceleration);

	double getSpeed();
	void setSpeed(double speed);

	double getAcceleration();
	void setAcceleration(double acceleration);

	double getHeadwayDistance();
	void setHeadwayDistance(double headwayDistance);

	int getControlState();
	void setControlState(int controlState);

	double getPreviousSpeed();
	void setPreviousSpeed(double previousSpeed);

	double getPreviousAcceleration();
	void setPreviousAcceleration(double previousAcceleration);

	double getPreviousHeadwayDistance();
	void setPreviousHeadwayDistance(double previousHeadwayDistance);

	int getPreviousControlState();
	void setPreviousControlState(int previousControlState);

	double getPreviousDistanceTravelled();
	void setPreviousDistanceTravelled(double);

	long getCurrentLink();
	void setCurrentLink(long currentLink);

	long getNextLink();
	void setNextLink(long nextLink);

	long getCurrentLane();
	void setCurrentLane(long currentLane);

	long getRelativeTargetLane();
	void setRelativeTargetLane(long relativeTargetLane);

	long getVehRelativeTargetLane();
	void setVehRelativeTargetLane(long relativeTargetLane);

	double getLaneAngle();
	void setLaneAngle(double laneAngle);

	double getDesiredLaneAngle();
	void setDesiredLaneAngle(double desiredLaneAngle);

	long getActiveLaneChange();
	void setActiveLaneChange(long activeLaneChange);

	long getVehActiveLaneChange();
	void setVehActiveLaneChange(long vehactiveLaneChange);

	long getTurningIndicator();
	void setTurningIndicator(long turningIndicator);

	double getDistanceTravelled();
	void setDistanceTravelled(double distanceTravelled);

	double getLateralPosition();
	void setLateralPosition(double lateralPosition);

	double getMaxAcceleration();
	void setMaxAcceleration(double maxAcceleration);

	long getVehicleCategory();
	void setVehicleCategory(long vehicleCategory);

	long getPreferredRelativeLane();
	void setPreferredRelativeLane(long preferredRelativeLane);

	long getLanesOfCurrentLink();
	void setLanesOfCurrentLink(long lanesOfCurrentLink);

	long getUsePreferredLane();
	void setUsePreferredLane(long usePreferredLane);

	double getVehXCoordinate();
	void setVehXCoordinate(double vehXCoordinate);

	double getVehYCoordinate();
	void setVehYCoordinate(double vehYCoordinate);

	double getVehRearXCoordinate();
	void setVehRearXCoordinate(double vehRearXCoordinate);

	double getVehRearYCoordinate();
	void setVehRearYCoordinate(double vehRearYCoordinate);

	double getPosInLink();
	void setPosInLink(double PosInLink);

	long getVehIntacState();
	void setVehIntacState(long vehIntacState);

	long getVehIntacTargetType();
	void setVehIntacTargetType(long vehIntacTargetType);

	long getVehIntacTargetID();
	void setVehIntacTargetID(long vehIntacTargetID);

	long getVehIntacHeadway();
	void setVehIntacHeadway(long vehIntacHeadway);
	
	int gettimeIntoCACC();
	void settimeIntoCACC(int timeIntoCACC);

	double getaccDuringTransition();
	void setaccDuringTransition(double accDuringTransition);

	long getusesimplelanechange();
	void setusesimplelanechange(long use_simplelanechange);

	long getuseinternalmodel();
	void setuseinternalmodel(long use_internalmodel);

	long getMPCstep();
	void setMPCstep(long MPC_step);

	long getlanechangestate();
	void setlanechangestate(long lane_changestate);

	long getreturnlanestate();
	void setreturnlanestate(long return_lanestate);

	double getwheelangle();
	void   setwheelangle(double wheel_angle);

	double getlanewidth();
	void   setlanewidth(double lane_width);

	long getmanualstate();
	void   setmanualstate(long state);

	void setdecisiontime(long time);
	long getdecisiontime();

	void setstep(int step);
	int getstep();

	void setNEVHid(long id, long index2);
};
#endif

