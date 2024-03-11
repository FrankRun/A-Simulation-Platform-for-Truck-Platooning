/*==========================================================================*/
/*  SimVehicle.cpp                        for Driver DLL Module for VISSIM  */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*  Version of 2023-8-25                                   Xuerun Yan          */
/*==========================================================================*/

#include "SimVehicle.h"
#include "Platoon.h"


SimVehicle::SimVehicle() : timestep(0.10),id(0), type(0), color(0), platoonState(0), platoonID(0), time(0), currentLink(0), nextLink(0),
currentLane(0), speed(0), acceleration(0), desiredSpeed(0), desiredAcceleration(0), followingcolor(0),
previousSpeed(0), previousAcceleration(0), previousHeadwayDistance(0), previousDesiredSpeed(0), previousDistanceTravelled(0), previousPlatoonState(0),
laneAngle(0), desiredLaneAngle(0), headwayDistance(0), length(0), width(0), relativeTargetLane(0),vehrelativeTargetLane(0), lanesOfCurrentLink(0),
activeLaneChange(0), vehactiveLaneChange(0),turningIndicator(0), distanceTravelled(0), lateralPosition(0), weigth(0),
maxAcceleration(0), vehicleCategory(0), preferredRelativeLane(0), usePreferredLane(0),
vehXCoordinate(0), vehYCoordinate(0), vehRearXCoordinate(0), vehRearYCoordinate(0),
vehIntacState(0), vehIntacTargetType(0), vehIntacTargetID(0), vehIntacHeadway(0),
controlState(0), previousControlState(0), PosInLink(0), lastLink(0), DTBeforeNode(0), previousFrontVehicle(0),
usesimplelanechange(0), useinternalmodel(0), wantsuggestion(1), MinDedeceleration(8), 
intial_speed(-1),timeIntoCACC(0), accDuringTransition(0),MPCstep(0),wheelangle(0),lanechangestate(0),returnlanestate(0),lanewidth(0),manualstate(0),decisiontime(0),step(0),VDMdisabledtime(0)
{
	as = 0.01;
}

SimVehicle::~SimVehicle()
{
}

SimVehicle::PlatoonStates SimVehicle::determinVehPlatooningState(SimVehicle previouVeh,map<int, Platoon> &platoonList, map<long, SimVehicle>& vehiclesInNet)
{
	Platoon vehPlatoon = platoonList[this->platoonID];
	SimVehicle::PlatoonStates pltState;
	Platoon previousPlatoon ;	

	if (this->type == SimVehicle::VehTypeCACC)
	{
		as = 0.01;
		if (previouVeh.type == SimVehicle::VehTypeCACC)
		{
			previousPlatoon = platoonList[previouVeh.platoonID];
			if (previousPlatoon.id != this->platoonID) 
			{
				if (previousPlatoon.isNotFull() && headwayDistance < previousPlatoon.caccMaxCommunicationRange/4 
					&& vehPlatoon.size+previousPlatoon.size<=previousPlatoon.maxSize 
					&& (this->speed-previouVeh.getSpeed())*abs(this->speed - previouVeh.getSpeed())/as<this->headwayDistance-this->length
					&& platoonList[previousPlatoon.id].platoonlanechangestate == 0)  
				{ 
					pltState = SimVehicle::PlatoonStatePlatoonFollowing;
					//route decision
					if (vehiclesInNet[this->id].currentLink == vehiclesInNet[previouVeh.id].currentLink
						&&vehiclesInNet[this->id].nextLink != vehiclesInNet[previouVeh.id].nextLink
						&&vehiclesInNet[this->id].nextLink != vehiclesInNet[this->id].currentLink
						&&vehiclesInNet[previouVeh.id].nextLink != vehiclesInNet[previouVeh.id].currentLink)
					{
						pltState = SimVehicle::PlatoonStatePlatoonLeading;
					}
				}
				else
				{
					pltState = SimVehicle::PlatoonStatePlatoonLeading;
				}
			}			
			else   
			{
				if (headwayDistance > previousPlatoon.caccMaxCommunicationRange / 4 + 1)
					pltState = SimVehicle::PlatoonStatePlatoonLeading;
				else {
					if (vehPlatoon.size > previousPlatoon.maxSize && vehPlatoon.getNumInPlatoon(this->id) == previousPlatoon.maxSize + 1)
						pltState = SimVehicle::PlatoonStatePlatoonLeading;
					else
					{
						pltState = SimVehicle::PlatoonStatePlatoonFollowing;
						
						if (vehiclesInNet[this->id].currentLink == vehiclesInNet[previouVeh.id].currentLink
							&& vehiclesInNet[this->id].nextLink != vehiclesInNet[previouVeh.id].nextLink
							&& vehiclesInNet[this->id].nextLink != vehiclesInNet[this->id].currentLink
							&& vehiclesInNet[previouVeh.id].nextLink != vehiclesInNet[previouVeh.id].currentLink)
						{
							pltState = SimVehicle::PlatoonStatePlatoonLeading;
						}
					}
				}
			}
		}
		else
		{
			pltState = SimVehicle::PlatoonStatePlatoonLeading;
		}
	}
	else
	{
		pltState = SimVehicle::PlatoonStateVehTypeIsNotForPlatooning;
	}
	return pltState;
}

//initialize the vehicle
void SimVehicle::reInit()
{
	this->followingcolor = 0;
	this->platoonState = 0;
	this->platoonID = 0;
	this->controlState = 0;
	this->previousSpeed = 0;
	this->previousAcceleration = 0;
	this->previousHeadwayDistance = 0;
	this->previousControlState = 0;
	this->previousDistanceTravelled = 0;
	this->nextLink = 0;
	this->vehrelativeTargetLane = 0;
	this->relativeTargetLane = 0;
	this->vehactiveLaneChange = 0;
	this->activeLaneChange = 0;
	this->PosInLink = 0;
	this->lastLink = 0;
	this->DTBeforeNode = 0;
	this->wantsuggestion = 1;
	this->previousFrontVehicle = 0;
	this->useinternalmodel = 1;    
	this->usesimplelanechange = 1; 
	this->MinDedeceleration = 10;  
	this->intial_speed = -1;
	this->MPCstep = 0;
	this->wheelangle = 0;
	this->lanechangestate = 0;
	this->returnlanestate = 0;
	this->manualstate = 0;
	this->decisiontime = 0;
	this->step = 0;
	this->VDMdisabledtime = 0;
}

bool SimVehicle::updatePreviousStates(SimVehicle statesFromVeh)
{
	try
	{
		this->previousSpeed = statesFromVeh.speed;
		this->previousAcceleration = statesFromVeh.acceleration;
		this->previousHeadwayDistance = statesFromVeh.headwayDistance;
		this->previousControlState = statesFromVeh.controlState;
		this->previousDistanceTravelled = statesFromVeh.distanceTravelled;
		this->previousDesiredAcceleration = statesFromVeh.desiredAcceleration;
		this->previousDesiredSpeed = statesFromVeh.desiredSpeed;
		this->previouslane = statesFromVeh.currentLane;
	
		this->lastLink = statesFromVeh.currentLink;
		this->DTBeforeNode = statesFromVeh.DTBeforeNode;
		this->lastlinktopos = statesFromVeh.lastlinktopos;

		this->platoonState = statesFromVeh.platoonState;
		this->platoonID = statesFromVeh.platoonID;
		this->controlState = 0;

		this->previousFrontVehicle = statesFromVeh.previousFrontVehicle;
		this->MinDedeceleration = statesFromVeh.MinDedeceleration;
		this->intial_speed = statesFromVeh.intial_speed;
		this->step = 0;

		this->MPCstep = statesFromVeh.MPCstep;
		this->wheelangle = statesFromVeh.wheelangle;
		this->lanechangestate = statesFromVeh.lanechangestate;
		this->returnlanestate = statesFromVeh.returnlanestate;
		this->turningIndicator = statesFromVeh.turningIndicator;
		this->manualstate = statesFromVeh.manualstate;
		this->decisiontime = statesFromVeh.decisiontime;
		this->activeLaneChange = statesFromVeh.activeLaneChange;
		this->VDMdisabledtime = statesFromVeh.VDMdisabledtime;
		return  true;
	}
	catch (exception e)
	{
		return false;
	}
}

#pragma region getters/setters
void SimVehicle::setLCcontrolparaszero()
{
	this->lanechangestate = 0; 
	this->returnlanestate = 0;
	this->MPCstep = 0;
	this->wheelangle = 0;
	this->decisiontime = 0;
}

double SimVehicle::gettimestep()
{
	return this->timestep;
}
void SimVehicle::settimestep(double timestep)
{
	this->timestep = timestep;
}
int SimVehicle::getId()
{
	return this->id;
}
void SimVehicle::setId(long id)
{
	this->id = id;
}
void SimVehicle::setNEVHid(long id, long index2)
{
	this->id = id;
	if (id < 0)
	{
		this->speed = 0;
		this->acceleration = 0;
		this->length = 0;
		if (index2 > 0)
		{
			this->headwayDistance = 255;
		}
		else if (index2 < 0)
		{
			this->headwayDistance = -255;
		}
	}
}

long SimVehicle::getType()
{
	return this->type;
}
void SimVehicle::setType(long type)
{
	this->type = type;
}

double SimVehicle::getTime()
{
	return this->time;
}
void SimVehicle::setTime(double time)
{
	this->time = time;
}

long SimVehicle::getColor()
{
	return this->color;
}
void SimVehicle::setColor(long color)
{
	this->color = color;
}

double SimVehicle::getLength()
{
	return this->length;
}
void SimVehicle::setLength(double length)
{
	this->length = length;
}

double SimVehicle::getWidth()
{
	return this->width;
}
void SimVehicle::setWidth(double width)
{
	this->width = width;
}

double SimVehicle::getWeight()
{
	return this->weigth;
}
void SimVehicle::setWeight(double weight)
{
	this->weigth = weight;
}

long SimVehicle::getPlatoonState()
{
	return this->platoonState;
}
void SimVehicle::setPlatoonState(long platoonState)
{
	this->platoonState = platoonState;
}

long SimVehicle::getPlatoonID()
{
	return this->platoonID;
}
void SimVehicle::setPlatoonID(long platoonID)
{
	this->platoonID = platoonID;
}

double SimVehicle::getDesiredSpeed()
{
	return this->desiredSpeed;
}
void SimVehicle::setDesiredSpeed(double desiredSpeed)
{
	this->desiredSpeed = desiredSpeed;
}

double SimVehicle::getDesiredAcceleration()
{
	return this->desiredAcceleration;
}
void SimVehicle::setDesiredAcceleration(double desiredAcceleration)
{
	this->desiredAcceleration = desiredAcceleration;
}

double SimVehicle::getSpeed()
{
	return this->speed;
}
void SimVehicle::setSpeed(double speed)
{
	this->speed = speed;
}

double SimVehicle::getAcceleration()
{
	return this->acceleration;
}
void SimVehicle::setAcceleration(double acceleration)
{
	this->acceleration = acceleration;
}

double SimVehicle::getHeadwayDistance()
{
	return this->headwayDistance;
}
void SimVehicle::setHeadwayDistance(double headwayDistance)
{
	this->headwayDistance = headwayDistance;
}

int SimVehicle::getControlState()
{
	return this->controlState;
}
void SimVehicle::setControlState(int controlState)
{
	this->controlState = controlState;
}

double SimVehicle::getPreviousSpeed()
{
	return this->previousSpeed;
}
void SimVehicle::setPreviousSpeed(double previousSpeed)
{
	this->previousSpeed = previousSpeed;
}

double SimVehicle::getPreviousAcceleration()
{
	return this->previousAcceleration;
}
void SimVehicle::setPreviousAcceleration(double previousAcceleration)
{
	this->previousAcceleration = previousAcceleration;
}

double SimVehicle::getPreviousHeadwayDistance()
{
	return this->previousHeadwayDistance;
}
void SimVehicle::setPreviousHeadwayDistance(double previousHeadwayDistance)
{
	this->previousHeadwayDistance = previousHeadwayDistance;
}

int SimVehicle::getPreviousControlState()
{
	return this->previousControlState;
}
void SimVehicle::setPreviousControlState(int previousControlState)
{
	this->previousControlState = previousControlState;
}

double SimVehicle::getPreviousDistanceTravelled() {
	return this->previousDistanceTravelled;
}
void SimVehicle::setPreviousDistanceTravelled(double previousDistanceTravelled) {
	this->previousDistanceTravelled= previousDistanceTravelled;
}

long SimVehicle::getCurrentLink()
{
	return this->currentLink;
}
void SimVehicle::setCurrentLink(long currentLink)
{
	this->currentLink = currentLink;
}

long SimVehicle::getNextLink()
{
	return this->nextLink;
}
void SimVehicle::setNextLink(long nextLink)
{
	this->nextLink = nextLink;
}

long SimVehicle::getCurrentLane()
{
	return this->currentLane;
}
void SimVehicle::setCurrentLane(long currentLane)
{
	this->currentLane = currentLane;
}
long SimVehicle::getVehRelativeTargetLane()
{
	return this->vehrelativeTargetLane;
}

void SimVehicle::setVehRelativeTargetLane(long relativeTargetLane)
{
	this->vehrelativeTargetLane = relativeTargetLane;
}
long SimVehicle::getRelativeTargetLane()
{
	return this->relativeTargetLane;
}
void SimVehicle::setRelativeTargetLane(long relativeTargetLane)
{
	this->relativeTargetLane = relativeTargetLane;
}
long SimVehicle::getLanesOfCurrentLink()
{
	return this->lanesOfCurrentLink;
}
void SimVehicle::setLanesOfCurrentLink(long lanesOfCurrentLink)
{
	this->lanesOfCurrentLink = lanesOfCurrentLink;
}
double SimVehicle::getLaneAngle()
{
	return this->laneAngle;
}
void SimVehicle::setLaneAngle(double laneAngle)
{
	this->laneAngle = laneAngle;
}

double SimVehicle::getDesiredLaneAngle()
{
	return this->desiredLaneAngle;
}
void SimVehicle::setDesiredLaneAngle(double desiredLaneAngle)
{
	this->desiredLaneAngle = desiredLaneAngle;
}
long SimVehicle::getVehActiveLaneChange()
{
	return this->vehactiveLaneChange;
}
void SimVehicle::setVehActiveLaneChange(long vehactiveLaneChange)
{
	this->vehactiveLaneChange = vehactiveLaneChange;
}
long SimVehicle::getActiveLaneChange()
{
	return this->activeLaneChange;
}
void SimVehicle::setActiveLaneChange(long activeLaneChange)
{
	this->activeLaneChange = activeLaneChange;
}

long SimVehicle::getTurningIndicator()
{
	return this->turningIndicator;
}
void SimVehicle::setTurningIndicator(long turningIndicator)
{
	this->turningIndicator = turningIndicator;
}

double SimVehicle::getDistanceTravelled()
{
	return this->distanceTravelled;
}
void SimVehicle::setDistanceTravelled(double distanceTravelled)
{
	this->distanceTravelled = distanceTravelled;
}

double SimVehicle::getLateralPosition()
{
	return this->lateralPosition;
}
void SimVehicle::setLateralPosition(double lateralPosition)
{
	this->lateralPosition = lateralPosition;
}

double SimVehicle::getMaxAcceleration()
{
	return this->maxAcceleration;
}
void SimVehicle::setMaxAcceleration(double maxAcceleration)
{
	this->maxAcceleration = maxAcceleration;
}

long SimVehicle::getVehicleCategory()
{
	return this->vehicleCategory;
}
void SimVehicle::setVehicleCategory(long vehicleCategory)
{
	this->vehicleCategory = vehicleCategory;
}

long SimVehicle::getPreferredRelativeLane()
{
	return this->preferredRelativeLane;
}
void SimVehicle::setPreferredRelativeLane(long preferredRelativeLane)
{
	this->preferredRelativeLane = preferredRelativeLane;
}

long SimVehicle::getUsePreferredLane()
{
	return this->usePreferredLane;
}
void SimVehicle::setUsePreferredLane(long usePreferredLane)
{
	this->usePreferredLane = usePreferredLane;
}

double SimVehicle::getVehXCoordinate()
{
	return this->vehXCoordinate;
}
void SimVehicle::setVehXCoordinate(double vehXCoordinate)
{
	this->vehXCoordinate = vehXCoordinate;
}

double SimVehicle::getVehYCoordinate()
{
	return this->vehYCoordinate;
}
void SimVehicle::setVehYCoordinate(double vehYCoordinate)
{
	this->vehYCoordinate = vehYCoordinate;
}

double SimVehicle::getVehRearXCoordinate()
{
	return this->vehRearXCoordinate;
}
void SimVehicle::setVehRearXCoordinate(double vehRearXCoordinate)
{
	this->vehRearXCoordinate = vehRearXCoordinate;
}

double SimVehicle::getVehRearYCoordinate()
{
	return  this->vehRearYCoordinate;
}
void SimVehicle::setVehRearYCoordinate(double vehRearYCoordinate)
{
	this->vehRearYCoordinate = vehRearYCoordinate;
}

double SimVehicle::getPosInLink()
{
	return this->PosInLink;
}

void SimVehicle::setPosInLink(double PosInLink)
{
	this->PosInLink = PosInLink;
}

long SimVehicle::getVehIntacState()
{
	return this->vehIntacState;
}
void SimVehicle::setVehIntacState(long vehIntacState)
{
	this->vehIntacState = vehIntacState;
}

long SimVehicle::getVehIntacTargetType()
{
	return this->vehIntacTargetType;
}
void SimVehicle::setVehIntacTargetType(long vehIntacTargetType)
{
	this->vehIntacTargetType = vehIntacTargetType;
}

long SimVehicle::getVehIntacTargetID()
{
	return this->vehIntacTargetID;
}
void SimVehicle::setVehIntacTargetID(long vehIntacTargetID)
{
	this->vehIntacTargetID = vehIntacTargetID;
}

long SimVehicle::getVehIntacHeadway()
{
	return this->vehIntacHeadway;
}
void SimVehicle::setVehIntacHeadway(long vehIntacHeadway)
{
	this->vehIntacHeadway = vehIntacHeadway;
}

int SimVehicle::gettimeIntoCACC()
{
	return this->timeIntoCACC;
}

void SimVehicle::settimeIntoCACC(int timeIntoCACC)
{
	this->timeIntoCACC = timeIntoCACC;
}

double SimVehicle::getaccDuringTransition()
{
	return this->accDuringTransition;
}

void SimVehicle::setaccDuringTransition(double accDuringTransition)
{
	this->accDuringTransition = accDuringTransition;
}

long SimVehicle::getusesimplelanechange()
{
	return this->usesimplelanechange;
}

void SimVehicle::setusesimplelanechange(long use_simplelanechange)
{
	this->usesimplelanechange = use_simplelanechange;
}

long SimVehicle::getuseinternalmodel()
{
	return this->useinternalmodel;
}
void SimVehicle::setuseinternalmodel(long use_internalmodel)
{
	this->useinternalmodel = use_internalmodel;
}

long SimVehicle::getMPCstep()
{
	return this->MPCstep;
}
void SimVehicle::setMPCstep(long MPC_step)
{
	this->MPCstep = MPC_step;
}
long SimVehicle::getlanechangestate()
{
	return this->lanechangestate;
}
void SimVehicle::setlanechangestate(long lane_changestate)
{
	this->lanechangestate = lane_changestate;
}

long SimVehicle::getreturnlanestate()
{
	return this->returnlanestate;
}
void SimVehicle::setreturnlanestate(long return_lanestate)
{
	this->returnlanestate = return_lanestate;
}
double SimVehicle::getwheelangle()
{
	return this->wheelangle;
}
void SimVehicle::setwheelangle(double wheel_angle)
{
	this->wheelangle = wheel_angle;
}

double SimVehicle::getlanewidth()
{
	return this->lanewidth;
}
void SimVehicle::setlanewidth(double lane_width)
{
	this->lanewidth = lane_width;
}
long SimVehicle::getmanualstate()
{
	return this->manualstate;
}
void  SimVehicle::setmanualstate(long state)
{
	this->manualstate = state;
}

long SimVehicle::getdecisiontime()
{
	return this->decisiontime;
}
void SimVehicle::setdecisiontime(long time)
{
	this->decisiontime = time;
}
void SimVehicle::setstep(int step)
{
	this->step = step;
}
int SimVehicle::getstep()
{
	return this->step;
}
#pragma endregion

