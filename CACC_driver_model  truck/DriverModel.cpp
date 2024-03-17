/*==========================================================================*/
/*  DriverModel.cpp                                  DLL Module for VISSIM  */
/*                                                                          */
/*  Interface module for external driver models.                            */
/*  Dummy version that simply sends back VISSIM's suggestions to VISSIM.    */
/*                                                                          */
/*  Version of 2010-03-02                                   Lukas Kautzsch  */
/*  Modified on 2023-06-10                       By Lai Jintao &Yan Xuerun  */
/*==========================================================================*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <map>
#include <vector>
#include <mutex>
#include<thread>
#include "DriverModel.h"
#include "Log.h"
#include "Link.h"
#include "VehicleDynamicModel.h"
#include"Eigen\Dense"
#include<math.h>
#include"Control.h"
#include "READ.h"
#include"Decision Maker.h"


using namespace std;
using namespace Eigen;

/*==========================================================================*/
mutex mlock;

const int LANE_OFFSET = 2;				// -2 indicates second to the right, after transfer, 0 indicates second to the right
const int POSITION_OFFSET = 2;			// -2 indicates second next car upstream, after transfer, 0 indicates second next car upstream
const int CACC_VEH_TYPE = 700;      // vehicle type 

long DEFAULT_MAX_PLATOON_SIZE = 6;
double DEFAULT_INNER_PLATOON_HEADWAY = 0.6;		// in seconds
const double DEFAULT_INTER_PLATOON_HEADWAY = 1.5;		// in seconds
const int DEFAULT_CACC_MAX_COMMUNICATION_RANGE = 300;	// in meter, determined by DSRC communication range
const double ACC_prmts[5] = { 31.1,1.0, 4, 2, 3 };  //Acc parameters 
//(:,0) v0			(:,1) T //safe time gap  	(:,2) s0 //bumper to bumper gap+length of car	(:,3) a				(:,4) b

//Vehicle Dynamic Model defination
_declspec(thread) VDM CurrentVDM;


//SIMVEHICLE is a structure that definds all fundamental properties of a vehicle. Defined in DriverModel.h file
_declspec(thread) SimVehicle currentVehicle;
_declspec(thread) SimVehicle adjacentVehicles[5][5];

map<long, SimVehicle> vehiclesInNet;	//Stores all active vehicles. Key: vehicle ID; value: vehicle object, object is defined in SimVehicle class
map<int, Platoon> platoons;				//Stores all active platoons. Key: platoon ID; value: platoon object, object is defined in Platoon class
map<long, Link> links;
map<long, VDM> VDMInNet;
//print the logs.txt
//stringstream ss;

const int Step_total = 20;
double safedistance = 12;
double platoonlanechangeposition = 5000;
double vehiclelanechangedecisiontime = 20;


/*==========================================================================*/

BOOL APIENTRY DllMain (HANDLE  hModule, 
                       DWORD   ul_reason_for_call, 
                       LPVOID  lpReserved)
{
  switch (ul_reason_for_call) {
      case DLL_PROCESS_ATTACH:
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
      case DLL_PROCESS_DETACH:
         break;
  }
  return TRUE;
}

/*==========================================================================*/

DRIVERMODEL_API  int  DriverModelSetValue (long   type, 
                                           long   index1,
                                           long   index2,
                                           long   long_value,
                                           double double_value,
                                           char   *string_value)
{
  /* Sets the value of a data object of type <type>, selected by <index1> */
  /* and possibly <index2>, to <long_value>, <double_value> or            */
  /* <*string_value> (object and value selection depending on <type>).    */
  /* Return value is 1 on success, otherwise 0.                           */
	//Server.initial();//initialize the communication between COM and DLL.
  switch (type) {
    case DRIVER_DATA_PATH                   :
    case DRIVER_DATA_TIMESTEP               :
		currentVehicle.settimestep(double_value);
		return 1;
	case DRIVER_DATA_TIME                   :
		currentVehicle.setTime(double_value);
		return 1;
	case DRIVER_DATA_VEH_ID                 :
		currentVehicle.setId(long_value);
		return 1;
    case DRIVER_DATA_VEH_LANE               :
		currentVehicle.setCurrentLane(long_value);
		return 1;
	case DRIVER_DATA_VEH_ODOMETER           :
		currentVehicle.setDistanceTravelled(double_value);
		return 1;
    case DRIVER_DATA_VEH_LANE_ANGLE         :
		currentVehicle.setLaneAngle(double_value);
		return 1;
    case DRIVER_DATA_VEH_LATERAL_POSITION   :
		currentVehicle.setLateralPosition(double_value);
		return 1;
	case DRIVER_DATA_VEH_VELOCITY           :
		currentVehicle.setSpeed(double_value);
		return 1;
    case DRIVER_DATA_VEH_ACCELERATION       :
		currentVehicle.setAcceleration(double_value);
		return 1;
    case DRIVER_DATA_VEH_LENGTH             :
		currentVehicle.setLength(double_value);
		return 1;
    case DRIVER_DATA_VEH_WIDTH              :
		currentVehicle.setWidth(double_value);
		return 1;
    case DRIVER_DATA_VEH_WEIGHT             :
		currentVehicle.setWeight(double_value);
		return 1;
    case DRIVER_DATA_VEH_MAX_ACCELERATION   :
		currentVehicle.setMaxAcceleration(double_value);
		return 1;
    case DRIVER_DATA_VEH_TURNING_INDICATOR  : /* long:   left = 1, right = -1, none = 0, both = 2 */
		currentVehicle.setTurningIndicator(long_value);
        return 1;
    case DRIVER_DATA_VEH_CATEGORY           :
		currentVehicle.setVehicleCategory(long_value);
		return 1;
    case DRIVER_DATA_VEH_PREFERRED_REL_LANE :
		currentVehicle.setPreferredRelativeLane(long_value);
		return 1;
    case DRIVER_DATA_VEH_USE_PREFERRED_LANE :
		currentVehicle.setUsePreferredLane(long_value);
		return 1;
    case DRIVER_DATA_VEH_DESIRED_VELOCITY   :
		currentVehicle.setDesiredSpeed(double_value);
		return 1;
    case DRIVER_DATA_VEH_X_COORDINATE       :
		currentVehicle.setVehXCoordinate(double_value);
		return 1;
    case DRIVER_DATA_VEH_Y_COORDINATE       :
		currentVehicle.setVehYCoordinate(double_value);
		return 1;
    case DRIVER_DATA_VEH_TYPE               :
		currentVehicle.setType(long_value);
		return 1;
	case DRIVER_DATA_VEH_COLOR: 
		currentVehicle.setColor(long_value);
		return 1;
    case DRIVER_DATA_VEH_CURRENT_LINK       :
		currentVehicle.setCurrentLink(long_value);
		return 1; /* (To avoid getting sent lots of DRIVER_DATA_VEH_NEXT_LINKS messages) */
			      /* Must return 1 if these messages are to be sent from VISSIM!         */
    case DRIVER_DATA_VEH_NEXT_LINKS         :
		if (currentVehicle.step == 0)
		{
			vehiclesInNet[currentVehicle.id].setNextLink(long_value);
			currentVehicle.setstep(1);
		}
		return 1; 
    case DRIVER_DATA_VEH_ACTIVE_LANE_CHANGE :
		currentVehicle.setVehActiveLaneChange(long_value);
		return 1;
    case DRIVER_DATA_VEH_REL_TARGET_LANE    :
		currentVehicle.setVehRelativeTargetLane(long_value);
		return 1;
	//next four are newly added from VISSIM 9.0
	case DRIVER_DATA_VEH_INTAC_STATE:
		currentVehicle.setVehIntacState(long_value);
		return 1;
	case DRIVER_DATA_VEH_INTAC_TARGET_TYPE:
		currentVehicle.setVehIntacTargetType(long_value);
		return 1;
	case DRIVER_DATA_VEH_INTAC_TARGET_ID:
		currentVehicle.setVehIntacTargetID(long_value);
		return 1;
	case DRIVER_DATA_VEH_INTAC_HEADWAY:
		currentVehicle.setVehIntacHeadway(long_value);
		return 1;
	case DRIVER_DATA_NVEH_ID                :

		adjacentVehicles[LANE_OFFSET + index1][POSITION_OFFSET + index2].setNEVHid(long_value, index2);
		if (index1 ==0&&index2 == 1 && long_value == -1)
		{
			currentVehicle.setHeadwayDistance(255);
		}
		return 1;
	case DRIVER_DATA_NVEH_LANE_ANGLE        :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setLaneAngle(double_value);
		return 1;
	case DRIVER_DATA_NVEH_LATERAL_POSITION  :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setLateralPosition(double_value);
		return 1;
	case DRIVER_DATA_NVEH_DISTANCE			:
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setHeadwayDistance(double_value);  
		if (index1 == 0 && index2 == 1) {
			currentVehicle.setHeadwayDistance(double_value);
		}
		return 1;
	case DRIVER_DATA_NVEH_REL_VELOCITY      :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setSpeed(currentVehicle.speed - double_value);  
		return 1;
	case DRIVER_DATA_NVEH_ACCELERATION      :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setAcceleration(double_value);
		return 1;
	case DRIVER_DATA_NVEH_LENGTH            :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setLength(double_value);
		return 1;
	case DRIVER_DATA_NVEH_WIDTH             :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setWidth(double_value);
		return 1;
	case DRIVER_DATA_NVEH_WEIGHT            :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setWeight(double_value);
		return 1;
    case DRIVER_DATA_NVEH_TURNING_INDICATOR :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setTurningIndicator(long_value);
		return 1;
	case DRIVER_DATA_NVEH_CATEGORY          :
    case DRIVER_DATA_NVEH_LANE_CHANGE       :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setActiveLaneChange(long_value); 
		return 1;
	case DRIVER_DATA_NVEH_TYPE              :
		adjacentVehicles[index1 + LANE_OFFSET][index2 + POSITION_OFFSET].setType(long_value);
		return 1;
	case DRIVER_DATA_NO_OF_LANES            :
		currentVehicle.setLanesOfCurrentLink(long_value);
		return 1;
    case DRIVER_DATA_LANE_WIDTH             :
		currentVehicle.setlanewidth(double_value);
		return 1;
    case DRIVER_DATA_LANE_END_DISTANCE      :
    case DRIVER_DATA_RADIUS                 :
    case DRIVER_DATA_MIN_RADIUS             :
    case DRIVER_DATA_DIST_TO_MIN_RADIUS     :
    case DRIVER_DATA_SLOPE                  :
    case DRIVER_DATA_SLOPE_AHEAD            :
    case DRIVER_DATA_SIGNAL_DISTANCE        :
    case DRIVER_DATA_SIGNAL_STATE           :
    case DRIVER_DATA_SIGNAL_STATE_START     :
    case DRIVER_DATA_SPEED_LIMIT_DISTANCE   :
    case DRIVER_DATA_SPEED_LIMIT_VALUE      :
    case DRIVER_DATA_DESIRED_ACCELERATION :
		currentVehicle.setDesiredAcceleration(double_value);
		return 1;
    case DRIVER_DATA_DESIRED_LANE_ANGLE :
		currentVehicle.setDesiredLaneAngle(double_value);
		return 1;
    case DRIVER_DATA_ACTIVE_LANE_CHANGE :
		currentVehicle.setActiveLaneChange(long_value);
		return 1;
    case DRIVER_DATA_REL_TARGET_LANE :
		currentVehicle.setRelativeTargetLane(long_value);
		return 1;
    default :
		return 0;
  }
}

/*--------------------------------------------------------------------------*/

DRIVERMODEL_API  int  DriverModelGetValue (long   type, 
                                           long   index1,
                                           long   index2,
                                           long   *long_value,
                                           double *double_value,
                                           char   **string_value)
{
  /* Gets the value of a data object of type <type>, selected by <index1> */
  /* and possibly <index2>, and writes that value to <*double_value>,     */
  /* <*float_value> or <**string_value> (object and value selection       */
  /* depending on <type>).                                                */
  /* Return value is 1 on success, otherwise 0.                           */
	
  switch (type) {
    case DRIVER_DATA_STATUS :
		*long_value = 0;
		return 1;
    case DRIVER_DATA_VEH_TURNING_INDICATOR	:
		*long_value = vehiclesInNet[currentVehicle.id].getTurningIndicator();
		return 1;
    case DRIVER_DATA_VEH_DESIRED_VELOCITY   :
		*double_value = vehiclesInNet[currentVehicle.id].getDesiredSpeed();
		return 1;
    case DRIVER_DATA_VEH_COLOR				:
		*long_value = vehiclesInNet[currentVehicle.id].getColor();
		return 1;
    case DRIVER_DATA_WANTS_SUGGESTION		:
		*long_value = 1;				
		return 1;
	case DRIVER_DATA_DESIRED_ACCELERATION:
		*double_value = vehiclesInNet[currentVehicle.id].getDesiredAcceleration();
		return 1;
    case DRIVER_DATA_DESIRED_LANE_ANGLE		:
		*double_value = vehiclesInNet[currentVehicle.id].getDesiredLaneAngle();
		return 1;
    case DRIVER_DATA_ACTIVE_LANE_CHANGE		:
		*long_value = vehiclesInNet[currentVehicle.id].getActiveLaneChange();
		return 1;
    case DRIVER_DATA_REL_TARGET_LANE		:
		*long_value = vehiclesInNet[currentVehicle.id].getRelativeTargetLane();
		return 1;
    case DRIVER_DATA_SIMPLE_LANECHANGE		:	
		if (currentVehicle.type == CACC_VEH_TYPE)
		{
			*long_value = vehiclesInNet[currentVehicle.id].getusesimplelanechange();
		}
		if (currentVehicle.type != CACC_VEH_TYPE)
			*long_value = vehiclesInNet[currentVehicle.id].getuseinternalmodel();// vehiclesInNet[currentVehicle.id].getuseinternalmodel();
			// simple lane change set 0 when use our lane change model;
		return 1;
	case DRIVER_DATA_USE_INTERNAL_MODEL:
		if (currentVehicle.type == CACC_VEH_TYPE)
		{
			*long_value = vehiclesInNet[currentVehicle.id].getuseinternalmodel();
		}
		if (currentVehicle.type != CACC_VEH_TYPE)
			*long_value = vehiclesInNet[currentVehicle.id].getuseinternalmodel();// vehiclesInNet[currentVehicle.id].getuseinternalmodel();
		return 1;
	case DRIVER_DATA_ALLOW_MULTITHREADING:
		*long_value = 1; /* must be set to 1 to allow a simulation run to be started with multiple cores used in the simulation parameters */
		return 1;
    default :
		return 0;
  }
}

/*==========================================================================*/

DRIVERMODEL_API  int  DriverModelExecuteCommand(long number)                
{
	/* Executes the command <number> if that is available in the driver */
	/* module. Return value is 1 on success, otherwise 0.               */

	switch (number) {
	case DRIVER_COMMAND_INIT:
	{
		ofstream myfile("logs.txt", ios::out | ios::trunc);
		myfile.is_open();
		myfile << "information will be recorded\n";
		myfile.close();
		myfile = ofstream("logs.txt", ios::out | ios::app);
		READ read;
		ifstream infile;
		infile.open("GUI.txt");
		string st;
		infile >> st;
		read.saveInfogui(st, DEFAULT_MAX_PLATOON_SIZE,DEFAULT_INNER_PLATOON_HEADWAY, safedistance, platoonlanechangeposition, vehiclelanechangedecisiontime);
		ifstream in("network.txt");
		string line;
		while (getline(in,line))
		{
			read.saveInfolink(line);
		}
		links = read.GetLinks();
		return 1;
	}

	case DRIVER_COMMAND_CREATE_DRIVER:
	{
		//initialize the vehicle and vehicle dynamincs model
		currentVehicle.reInit();
		vehiclesInNet[currentVehicle.id] = currentVehicle; 
		VDMInNet[currentVehicle.id] = CurrentVDM;
		VDMInNet[currentVehicle.id].Initialize();
		return 1;
	}

	case DRIVER_COMMAND_KILL_DRIVER: 
	{
		try
		{
			DecMaker decmaker = DecMaker(LANE_OFFSET,POSITION_OFFSET,DEFAULT_MAX_PLATOON_SIZE,DEFAULT_CACC_MAX_COMMUNICATION_RANGE,
				DEFAULT_INNER_PLATOON_HEADWAY,DEFAULT_INTER_PLATOON_HEADWAY,Step_total,platoonlanechangeposition,vehiclelanechangedecisiontime,ACC_prmts);
			int ID = currentVehicle.id;
			currentVehicle.controlState = SimVehicle::ControlStateCACCKill;
			vehiclesInNet[currentVehicle.id].controlState = SimVehicle::ControlStateCACCKill;
			decmaker.vehiclePlatooning(currentVehicle,vehiclesInNet,platoons,adjacentVehicles);
			vehiclesInNet.erase(ID); 
			VDMInNet.erase(ID);
			return 1;
		}
		catch (...)
		{
		}

	}
	case DRIVER_COMMAND_MOVE_DRIVER:   
	{
		stringstream ss;
		int ID = currentVehicle.id;
		long activelanechange = currentVehicle.activeLaneChange;
		long reltargetlane = currentVehicle.relativeTargetLane;
		//------------------update vehicle--------------------
		currentVehicle.updatePreviousStates(vehiclesInNet[ID]);
		if (currentVehicle.lastLink != currentVehicle.currentLink)
		{
			currentVehicle.DTBeforeNode = currentVehicle.distanceTravelled;
			if (links[currentVehicle.currentLink].LinkFrom == -1) 
				currentVehicle.lastlinktopos = links[currentVehicle.lastLink].posTo;
			else
				currentVehicle.lastlinktopos = 0;
			vehiclesInNet[ID].nextLink = 0;
		}
		if (vehiclesInNet[ID].nextLink == 0) 
		{
			vehiclesInNet[ID].nextLink = currentVehicle.currentLink;
		}
		currentVehicle.PosInLink = currentVehicle.distanceTravelled - currentVehicle.DTBeforeNode + currentVehicle.lastlinktopos; 
		currentVehicle.nextLink = vehiclesInNet[ID].nextLink;
		vehiclesInNet[ID] = currentVehicle;

		//------------------CACC control--------------------

		DecMaker decmaker = DecMaker(LANE_OFFSET, POSITION_OFFSET, DEFAULT_MAX_PLATOON_SIZE, DEFAULT_CACC_MAX_COMMUNICATION_RANGE,
			DEFAULT_INNER_PLATOON_HEADWAY, DEFAULT_INTER_PLATOON_HEADWAY, Step_total, platoonlanechangeposition, vehiclelanechangedecisiontime, ACC_prmts);
		
		if (decmaker.useManualDriving(currentVehicle,links)
			||vehiclesInNet[ID].manualstate==1) //manual control
		{
			vehiclesInNet[ID].type = SimVehicle::VehTypeRegularCar;
			decmaker.vehiclePlatooning(currentVehicle,vehiclesInNet,platoons,adjacentVehicles);
			vehiclesInNet[ID].manualstate = 1;
			vehiclesInNet[ID].useinternalmodel = 1;
			vehiclesInNet[ID].usesimplelanechange = 1;
			vehiclesInNet[ID].setLCcontrolparaszero(); 

			if (abs(vehiclesInNet[ID].lateralPosition) < 0.03 && !decmaker.useManualDriving(currentVehicle, links))  
			{
				vehiclesInNet[ID].useinternalmodel = 0;
				vehiclesInNet[ID].usesimplelanechange = 0;
				vehiclesInNet[ID].activeLaneChange = 0;
				vehiclesInNet[ID].relativeTargetLane = 0;
				vehiclesInNet[ID].desiredLaneAngle = 0;
				vehiclesInNet[ID].manualstate = 0;
			}
		}
		else// platooning control
		{
			Control con = Control(LANE_OFFSET,POSITION_OFFSET,Step_total,DEFAULT_INNER_PLATOON_HEADWAY,safedistance,ACC_prmts);
			MatrixXd k0(1, Step_total + 1);
			MatrixXd s(1, Step_total);
			MatrixXd lat_slope(1, Step_total + 1);
			MatrixXd state_vector_lonspeed(1, Step_total + 1);
			MatrixXd Lat_position_tar(1, Step_total + 1);
			MatrixXd Head_angle_tar(1, Step_total + 1);
			MatrixXd State_vector(3, Step_total + 1);
			MatrixParameter Mx = { k0,s,lat_slope,state_vector_lonspeed,Lat_position_tar,Head_angle_tar,State_vector };

			vehiclesInNet[ID].type = SimVehicle::VehTypeCACC;
			if (vehiclesInNet[ID].platoonID == 0 || platoons[vehiclesInNet[ID].platoonID].platoonlanechangestate == 0)  
			{
				lock_guard<mutex> lck(mlock);
				decmaker.vehiclePlatooning(currentVehicle,vehiclesInNet,platoons,adjacentVehicles);
			}
			decmaker.lanechangedecision(&Mx,currentVehicle,vehiclesInNet,platoons,links,adjacentVehicles);
			con.lanechangecontrol(&Mx,currentVehicle,vehiclesInNet,platoons);
			con.carFollowing(&Mx,currentVehicle,CurrentVDM,vehiclesInNet,platoons,VDMInNet,adjacentVehicles);
		}

		if ((activelanechange == 1 && vehiclesInNet[ID].desiredLaneAngle < 0) || (vehiclesInNet[ID].activeLaneChange == 1 && vehiclesInNet[ID].desiredLaneAngle < 0) ||
			(reltargetlane == 1 && vehiclesInNet[ID].desiredLaneAngle < 0) || (vehiclesInNet[ID].relativeTargetLane == 1 && vehiclesInNet[ID].desiredLaneAngle < 0))
		{
			vehiclesInNet[ID].desiredLaneAngle = 0;
		}
		else if ((activelanechange == -1 && vehiclesInNet[ID].desiredLaneAngle > 0) || (vehiclesInNet[ID].activeLaneChange == -1 && vehiclesInNet[ID].desiredLaneAngle > 0) ||
			(reltargetlane == -1 && vehiclesInNet[ID].desiredLaneAngle > 0) || (vehiclesInNet[ID].relativeTargetLane == -1 && vehiclesInNet[ID].desiredLaneAngle > 0))
		{
			vehiclesInNet[ID].desiredLaneAngle = 0;
		}
		return 1;
	}
	default:
		return 0;
	}
}
/*==========================================================================*/
/*  End of DriverModel.cpp                                                 */
/*==========================================================================*/


