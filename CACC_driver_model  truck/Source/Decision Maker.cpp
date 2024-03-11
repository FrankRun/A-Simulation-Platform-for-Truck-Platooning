#include"Decision Maker.h"
DecMaker::DecMaker()
{

}
DecMaker::DecMaker(const int LANE_OFFSET,const int POSITION_OFFSET, long DEFAULT_MAX_PLATOON_SIZE,const int DEFAULT_CACC_MAX_COMMUNICATION_RANGE, double DEFAULT_INNER_PLATOON_HEADWAY,
	const double DEFAULT_INTER_PLATOON_HEADWAY, const int Step_total,  double platoonlanechangeposition, double vehiclelanechangedecisiontime, const double ACC_prmts[]):
	LANE_OFFSET(LANE_OFFSET),POSITION_OFFSET(POSITION_OFFSET),DEFAULT_MAX_PLATOON_SIZE(DEFAULT_MAX_PLATOON_SIZE),DEFAULT_CACC_MAX_COMMUNICATION_RANGE(DEFAULT_CACC_MAX_COMMUNICATION_RANGE),DEFAULT_INNER_PLATOON_HEADWAY(DEFAULT_INNER_PLATOON_HEADWAY),
	DEFAULT_INTER_PLATOON_HEADWAY(DEFAULT_INTER_PLATOON_HEADWAY),Step_total(Step_total),platoonlanechangeposition(platoonlanechangeposition),vehiclelanechangedecisiontime(vehiclelanechangedecisiontime)
{
	this->ACC_prmts[0] = ACC_prmts[0];
	this->ACC_prmts[1] = ACC_prmts[1];
	this->ACC_prmts[2] = ACC_prmts[2];
	this->ACC_prmts[3] = ACC_prmts[3];
	this->ACC_prmts[4] = ACC_prmts[4];
	this->manualcolor = 4279236615;
}
DecMaker::~DecMaker()
{

}
bool DecMaker::target(int Step_total, int i, MatrixXd& Lat_position_tar, MatrixXd& Head_angle_tar, MatrixXd Lead_Lat_position_tar, MatrixXd Lead_Head_angle)
{
	//target trajectory
	if (i <= (Lead_Lat_position_tar.cols() - 1 - Step_total))
	{
		Lat_position_tar = Lead_Lat_position_tar.block(0, i, 1, Step_total + 1);
		Head_angle_tar = Lead_Head_angle.block(0, i, 1, Step_total + 1);
	}
	else
	{
		Lat_position_tar = Lead_Lat_position_tar.rightCols(Step_total + 1);
		Head_angle_tar = Lead_Head_angle.rightCols(Step_total + 1);
	}
	return true;
}

int DecMaker::vehiclePlatooning(SimVehicle& currentVehicle, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, SimVehicle adjacentVehicles[][5])
{
	try
	{
		SimVehicle previousVehicle = adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1];
		SimVehicle::PlatoonStates tmpState;
		long previousFrontVehicleid = vehiclesInNet[currentVehicle.id].previousFrontVehicle;

		if (previousVehicle.getType() == SimVehicle::VehTypeCACC)
		{
			previousVehicle = vehiclesInNet[adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].id];

			if (previousVehicle.currentLink == currentVehicle.currentLink
				&& previousVehicle.currentLane == currentVehicle.currentLane) 
			{
			}
			else 
				if (vehiclesInNet.count(previousFrontVehicleid) == 1) 
					if (vehiclesInNet[previousFrontVehicleid].currentLink == currentVehicle.currentLink
						&& vehiclesInNet[previousFrontVehicleid].currentLane == currentVehicle.currentLane)  
					{
						previousVehicle = vehiclesInNet[previousFrontVehicleid];
					}
		}
		else
		{
			previousVehicle.setPlatoonID(0);
			previousVehicle.setPlatoonState(SimVehicle::PlatoonStateVehTypeIsNotForPlatooning);
		}

		vehiclesInNet[currentVehicle.id].previousFrontVehicle = previousVehicle.id;

		tmpState = vehiclesInNet[currentVehicle.id].determinVehPlatooningState(previousVehicle, platoons, vehiclesInNet); 
		if (vehiclesInNet[currentVehicle.id].controlState == SimVehicle::ControlStateCACCKill)
			tmpState = SimVehicle::PlatoonStatePlatoonLeaving;
		vehiclesInNet[currentVehicle.id].setPlatoonState(tmpState);

		int b = platoons[vehiclesInNet[currentVehicle.id].platoonID].getBackIDof(currentVehicle.id);
		switch (tmpState) {

		case SimVehicle::PlatoonStatePlatoonLeading:
		{

			if (vehiclesInNet[currentVehicle.id].platoonID == 0)
			{
				if (previousVehicle.type==SimVehicle::VehTypeCACC&&previousVehicle.id > 0 && platoons[previousVehicle.platoonID].size < platoons[previousVehicle.platoonID].maxSize &&  
					currentVehicle.getHeadwayDistance() < 30) {
					
					platoons[previousVehicle.platoonID].vehicleBackJoin(vehiclesInNet[currentVehicle.id]);
					vehiclesInNet[currentVehicle.id].platoonState = SimVehicle::PlatoonStatePlatoonFollowing;
					vehiclesInNet[currentVehicle.id].platoonID = previousVehicle.platoonID;
				}
				else {
					vehiclesInNet[currentVehicle.id].platoonState = SimVehicle::PlatoonStatePlatoonLeading;

					Platoon newPlt = Platoon(currentVehicle.id, currentVehicle.distanceTravelled, currentVehicle.currentLane, DEFAULT_MAX_PLATOON_SIZE,
						DEFAULT_CACC_MAX_COMMUNICATION_RANGE, DEFAULT_INNER_PLATOON_HEADWAY, DEFAULT_INTER_PLATOON_HEADWAY);
					platoons[newPlt.id] = newPlt;

					vehiclesInNet[currentVehicle.id].platoonID = newPlt.id;
					return 1;
				}
			}
			else
			{

				if (vehiclesInNet[currentVehicle.id].platoonID != previousVehicle.platoonID)
				{

					if (currentVehicle.platoonState == SimVehicle::PlatoonStatePlatoonFollowing)
						platoons[currentVehicle.platoonID].splitPlatoon(platoons, currentVehicle.platoonID, currentVehicle.id, vehiclesInNet);
					vehiclesInNet[currentVehicle.id].setPlatoonState(SimVehicle::PlatoonStatePlatoonLeading);
					platoons[vehiclesInNet[currentVehicle.id].platoonID].leadingVehiclePosition = currentVehicle.distanceTravelled;
					return 1;
				}
				else 
				{
					vehiclesInNet[currentVehicle.id].setPlatoonState(SimVehicle::PlatoonStatePlatoonLeading);
					platoons[previousVehicle.platoonID].splitPlatoon(platoons, previousVehicle.platoonID, currentVehicle.id, vehiclesInNet);
					return 1;
				}
			}
		}

		case SimVehicle::PlatoonStatePlatoonFollowing:
		{

			if (vehiclesInNet[currentVehicle.id].platoonID == 0)
			{

				int followingID = platoons[previousVehicle.platoonID].getBackIDof(previousVehicle.getId());
				if (followingID == 0)
				{

					platoons[previousVehicle.platoonID].vehicleBackJoin(vehiclesInNet[currentVehicle.id]);
					vehiclesInNet[currentVehicle.id].platoonState = SimVehicle::PlatoonStatePlatoonFollowing;
					vehiclesInNet[currentVehicle.id].platoonID = previousVehicle.platoonID;
				}
				else
				{

					platoons[previousVehicle.platoonID].splitPlatoon(platoons, previousVehicle.platoonID, followingID, vehiclesInNet);
					previousVehicle = vehiclesInNet[adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1].id];
					platoons[previousVehicle.platoonID].vehicleBackJoin(vehiclesInNet[currentVehicle.getId()]);
					vehiclesInNet[currentVehicle.id].platoonID = previousVehicle.platoonID;
					vehiclesInNet[currentVehicle.id].platoonState = SimVehicle::PlatoonStatePlatoonFollowing;
				}
			}
			else
			{

				if (vehiclesInNet[currentVehicle.id].platoonID == previousVehicle.platoonID)
				{

					int PreIDInString = platoons[previousVehicle.platoonID].getFrontIDof(currentVehicle.getId());

					if (PreIDInString != previousVehicle.getId())
					{

						platoons[previousVehicle.platoonID].splitPlatoon(platoons, previousVehicle.platoonID, currentVehicle.getId(), vehiclesInNet);
						vehiclesInNet[currentVehicle.id].platoonState = SimVehicle::PlatoonStatePlatoonLeading;
					}
					else
						vehiclesInNet[currentVehicle.id].platoonState = SimVehicle::PlatoonStatePlatoonFollowing;
					return 1;
				}
				else 
				{

					if (previousVehicle.platoonState == SimVehicle::PlatoonStatePlatoonLeaving)
						return 1;

					int stringID = vehiclesInNet[currentVehicle.id].getPlatoonID();
					int PreIDInString = platoons[stringID].getFrontIDof(currentVehicle.getId());

					if (PreIDInString != 0)
					{

						platoons[stringID].splitPlatoon(platoons, stringID, currentVehicle.getId(), vehiclesInNet);
						vehiclesInNet[currentVehicle.id].platoonState = SimVehicle::PlatoonStatePlatoonLeading;
					}
					else
					{

						int platoonIDJoinFrom = vehiclesInNet[currentVehicle.id].platoonID;
						int platoonIDJoinTo = previousVehicle.platoonID;
						platoons[platoonIDJoinTo].platoonBackJoin(platoons, platoonIDJoinFrom, platoonIDJoinTo, vehiclesInNet);
						vehiclesInNet[currentVehicle.id].platoonState = SimVehicle::PlatoonStatePlatoonFollowing;
					}
				}
			}
			return 1;
		}
		case SimVehicle::PlatoonStatePlatoonLeaving:
		{
			if (vehiclesInNet[currentVehicle.id].controlState == SimVehicle::ControlStateCACCKill)
			{
				platoons[vehiclesInNet[currentVehicle.id].platoonID].leavePlatoon(vehiclesInNet[currentVehicle.id]);
				if (platoons[vehiclesInNet[currentVehicle.id].platoonID].size == 0)
				{
					platoons.erase(vehiclesInNet[currentVehicle.id].platoonID);
				}
				return 1;
			}
			if (vehiclesInNet[currentVehicle.id].platoonID != 0 && platoons[vehiclesInNet[currentVehicle.id].platoonID].size != 1)
			{
				platoons[vehiclesInNet[currentVehicle.id].platoonID].leavePlatoon(vehiclesInNet[currentVehicle.id]);
				Platoon newPlt = Platoon(currentVehicle.id, currentVehicle.distanceTravelled, currentVehicle.currentLane, DEFAULT_MAX_PLATOON_SIZE,
					DEFAULT_CACC_MAX_COMMUNICATION_RANGE, DEFAULT_INNER_PLATOON_HEADWAY, DEFAULT_INTER_PLATOON_HEADWAY);
				platoons[newPlt.id] = newPlt;
				vehiclesInNet[currentVehicle.id].platoonID = platoons[previousVehicle.platoonID].maxPlatoonID;
			}
			return 1;
		}
		case SimVehicle::PlatoonStateVehTypeIsNotForPlatooning:
		{
			vehiclesInNet[currentVehicle.id].setColor(manualcolor);
			if (vehiclesInNet[currentVehicle.id].platoonID != 0)
			{
				platoons[vehiclesInNet[currentVehicle.id].platoonID].leavePlatoon(vehiclesInNet[currentVehicle.id]);
				if (platoons[vehiclesInNet[currentVehicle.id].platoonID].size == 0)
				{
					platoons.erase(vehiclesInNet[currentVehicle.id].platoonID);
				}
				else
				{
					if (platoons[vehiclesInNet[currentVehicle.id].platoonID].lanechangejudgment(vehiclesInNet, platoons, vehiclesInNet[currentVehicle.id].platoonID))
					{
						platoons[vehiclesInNet[currentVehicle.id].platoonID].platoonlanechangestate = 0;
					}
				}
				vehiclesInNet[currentVehicle.id].platoonID = 0;
			}
			else
				vehiclesInNet[currentVehicle.id].platoonID = 0;
			return 1;
		}
		default:
			return 0;
		}
	}
	catch (...)
	{
		return 0;
	}
}
bool DecMaker::useManualDriving(SimVehicle &currentVehicle, map<long, Link> &links)
{
	if (currentVehicle.currentLink != currentVehicle.nextLink
		&& links[currentVehicle.nextLink].posFrom > 0
		&& links[currentVehicle.nextLink].posFrom - currentVehicle.PosInLink < 150
		&& links[currentVehicle.nextLink].posFrom - currentVehicle.PosInLink>0
		&& (currentVehicle.currentLane > links[currentVehicle.nextLink].LaneFrom + links[currentVehicle.nextLink].LanesNum - 1
			|| currentVehicle.currentLane < links[currentVehicle.nextLink].LaneFrom)) 
	{
		return 1;
	}
	return 0;
}
int DecMaker::PLCupdate(SimVehicle& currentVehicle, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, map<long, Link>& links)
{
	long ID = currentVehicle.id;
	if (vehiclesInNet[ID].platoonID != 0 && platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID) == 1)
	{
		if (vehiclesInNet[ID].currentLink != vehiclesInNet[ID].nextLink &&
			vehiclesInNet[ID].currentLane > links[vehiclesInNet[ID].nextLink].LaneFrom + links[vehiclesInNet[ID].nextLink].LanesNum - 1 &&
			vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].getlastIDof()].currentLane == vehiclesInNet[ID].currentLane &&
			((platoons[vehiclesInNet[ID].platoonID].lanechangejudgment(vehiclesInNet, platoons, vehiclesInNet[ID].platoonID) &&
				vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].getlastIDof()].currentLane == platoons[vehiclesInNet[ID].platoonID].targetlane) ||
				vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].getlastIDof()].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane))  
		{
			platoons[vehiclesInNet[ID].platoonID].setturndirection(-1);
			platoons[vehiclesInNet[ID].platoonID].setplatoonlength(vehiclesInNet);
		}
		else if (vehiclesInNet[ID].currentLink != vehiclesInNet[ID].nextLink &&
			vehiclesInNet[ID].currentLane < links[vehiclesInNet[ID].nextLink].LaneFrom &&
			vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].getlastIDof()].currentLane == vehiclesInNet[ID].currentLane &&  
			((platoons[vehiclesInNet[ID].platoonID].lanechangejudgment(vehiclesInNet, platoons, vehiclesInNet[ID].platoonID) &&
				vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].getlastIDof()].currentLane == platoons[vehiclesInNet[ID].platoonID].targetlane) ||
				vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].getlastIDof()].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane))
		{
			platoons[vehiclesInNet[ID].platoonID].setturndirection(1);
			platoons[vehiclesInNet[ID].platoonID].setplatoonlength(vehiclesInNet);
		}
		else
			platoons[vehiclesInNet[ID].platoonID].setturndirection(0);  
		if (platoons[vehiclesInNet[ID].platoonID].lanechangejudgment(vehiclesInNet, platoons, vehiclesInNet[ID].platoonID))     
		{

			platoons[vehiclesInNet[ID].platoonID].currentlane = vehiclesInNet[ID].currentLane;
			platoons[vehiclesInNet[ID].platoonID].settargetlane(vehiclesInNet[ID].currentLane + platoons[vehiclesInNet[ID].platoonID].turndirection);
		}
		return 1;
	}
	else if (vehiclesInNet[ID].platoonID != 0 && platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID) != 1) 
	{
		if (vehiclesInNet[ID].currentLane > platoons[vehiclesInNet[ID].platoonID].targetlane)
			platoons[vehiclesInNet[ID].platoonID].setturndirection(-1);
		else if (vehiclesInNet[ID].currentLane < platoons[vehiclesInNet[ID].platoonID].targetlane)
			platoons[vehiclesInNet[ID].platoonID].setturndirection(1);
		else
			platoons[vehiclesInNet[ID].platoonID].setturndirection(0);
		return 1;
	}
	return 0;
}
int DecMaker::lanechangedecision(MatrixParameter* Mx, SimVehicle& currentVehicle, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, map<long, Link>& links, SimVehicle adjacentVehicles[][5])
{
	PLCupdate(currentVehicle,vehiclesInNet,platoons,links); 
	long ID = currentVehicle.id;
	SimVehicle previousVehicle = adjacentVehicles[LANE_OFFSET][POSITION_OFFSET + 1];
	SimVehicle obstaclevehicle = adjacentVehicles[LANE_OFFSET + platoons[vehiclesInNet[ID].platoonID].turndirection][POSITION_OFFSET - 1]; 
	SimVehicle fronttargetvehicle = adjacentVehicles[LANE_OFFSET + platoons[vehiclesInNet[ID].platoonID].turndirection][POSITION_OFFSET + 1];

	if (vehiclesInNet[ID].platoonID != 0 && platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID) == 1)
	{

		if (platoons[vehiclesInNet[ID].platoonID].size > 1)
		{
			if (vehiclesInNet[ID].lanechangestate == 0)
			{
				vehiclesInNet[ID].activeLaneChange = 0;
				vehiclesInNet[ID].relativeTargetLane = 0;
				vehiclesInNet[ID].MPCstep = 0;

				if (vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane &&
					vehiclesInNet[ID].currentLink != vehiclesInNet[ID].nextLink
					&& links[vehiclesInNet[ID].nextLink].posFrom > 0
					&& links[vehiclesInNet[ID].nextLink].posFrom - vehiclesInNet[ID].PosInLink < platoonlanechangeposition
					&& links[vehiclesInNet[ID].nextLink].posFrom - vehiclesInNet[ID].PosInLink>0)  
				{
					if (platoons[vehiclesInNet[ID].platoonID].turndirection != 0 &&
						(vehiclesInNet[ID].headwayDistance - previousVehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, previousVehicle.speed) &&
						(fronttargetvehicle.headwayDistance - fronttargetvehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) &&
						(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > (distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) /*+ vehiclesInNet[ID].speed * 0.5*/) && 
						(fronttargetvehicle.headwayDistance - obstaclevehicle.headwayDistance - fronttargetvehicle.length) > (distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) + distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) + platoons[vehiclesInNet[ID].platoonID].platoonlength)
						)
					{
						vehiclesInNet[ID].lanechangestate = 1;
						if (obstaclevehicle.id == -1)
						{
							platoons[vehiclesInNet[ID].platoonID].setobstaclestate(0);
							platoons[vehiclesInNet[ID].platoonID].setlondistance(vehiclesInNet[ID].PosInLink); 
						}
						else 
						{
							platoons[vehiclesInNet[ID].platoonID].setobstaclestate(1);
						}
					}
				}
			}
			if (vehiclesInNet[ID].lanechangestate == 1 && vehiclesInNet[ID].returnlanestate == 0) 
			{
				if ((platoons[vehiclesInNet[ID].platoonID].turndirection != 0 && 
					(vehiclesInNet[ID].headwayDistance - previousVehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, previousVehicle.speed) &&
					(fronttargetvehicle.headwayDistance - fronttargetvehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) &&
					(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) &&
					(fronttargetvehicle.headwayDistance - obstaclevehicle.headwayDistance - fronttargetvehicle.length) > (distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) + distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) + platoons[vehiclesInNet[ID].platoonID].platoonlength))
					||
					(platoons[vehiclesInNet[ID].platoonID].turndirection == 0 && obstaclevehicle.id != platoons[vehiclesInNet[ID].platoonID].getBackIDof(ID) && 
						(fronttargetvehicle.headwayDistance - obstaclevehicle.headwayDistance - fronttargetvehicle.length) > (distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) + distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) + platoons[vehiclesInNet[ID].platoonID].platoonlength))
					||
					(platoons[vehiclesInNet[ID].platoonID].turndirection == 0 && obstaclevehicle.id == platoons[vehiclesInNet[ID].platoonID].getBackIDof(ID) && 
						(fronttargetvehicle.headwayDistance - obstaclevehicle.headwayDistance - fronttargetvehicle.length) > ((DEFAULT_INNER_PLATOON_HEADWAY - 0.2) * obstaclevehicle.speed + distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed)))
					)
				{
					//target reference
					Mx->k0.setZero();
					Mx->lat_slope.setZero();
					Mx->s.setOnes(); Mx->s = Mx->s * vehiclesInNet[ID].speed * currentVehicle.timestep;
					//state initialize
					Mx->state_vector_lonspeed.setOnes(); Mx->state_vector_lonspeed = Mx->state_vector_lonspeed * vehiclesInNet[ID].speed;
					Mx->Lat_position_tar.setOnes(); Mx->Lat_position_tar = Mx->Lat_position_tar * ((platoons[vehiclesInNet[ID].platoonID].targetlane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2); 
					Mx->Head_angle_tar.setZero();
					if (vehiclesInNet[ID].MPCstep == 0)
					{
						
						platoons[vehiclesInNet[ID].platoonID].Lead_Lat_position_tar.setOnes();
						platoons[vehiclesInNet[ID].platoonID].Lead_Head_angle.setZero();
						platoons[vehiclesInNet[ID].platoonID].Lead_Lat_position_tar = platoons[vehiclesInNet[ID].platoonID].Lead_Lat_position_tar * ((platoons[vehiclesInNet[ID].platoonID].targetlane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2);
					}
					return 1;
				}
				else
				{
					vehiclesInNet[ID].returnlanestate = 1;
				}
			}
			if (vehiclesInNet[ID].returnlanestate == 1)  
			{
				//target reference in lane-returning
				Mx->k0.setZero();
				Mx->lat_slope.setZero();
				Mx->s.setOnes(); Mx->s = Mx->s * vehiclesInNet[ID].speed * currentVehicle.timestep;
				Mx->state_vector_lonspeed.setOnes(); Mx->state_vector_lonspeed = Mx->state_vector_lonspeed * vehiclesInNet[ID].speed;
				Mx->Lat_position_tar.setOnes(); Mx->Lat_position_tar = Mx->Lat_position_tar * ((platoons[vehiclesInNet[ID].platoonID].currentlane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2);  
				Mx->Head_angle_tar.setZero();
				return 1;
			}
		}
		else if (platoons[vehiclesInNet[ID].platoonID].size == 1)
		{
			if (vehiclesInNet[ID].lanechangestate == 0)
			{
				vehiclesInNet[ID].activeLaneChange = 0;
				vehiclesInNet[ID].relativeTargetLane = 0;
				vehiclesInNet[ID].MPCstep = 0;
				if (vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane &&
					vehiclesInNet[ID].currentLink != vehiclesInNet[ID].nextLink  
					&& links[vehiclesInNet[ID].nextLink].posFrom > 0
					&& links[vehiclesInNet[ID].nextLink].posFrom - vehiclesInNet[ID].PosInLink < platoonlanechangeposition
					&& links[vehiclesInNet[ID].nextLink].posFrom - vehiclesInNet[ID].PosInLink>0)   
				{
					if (platoons[vehiclesInNet[ID].platoonID].turndirection != 0 &&
						(vehiclesInNet[ID].headwayDistance - previousVehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, previousVehicle.speed) &&
						(fronttargetvehicle.headwayDistance - fronttargetvehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) &&
						(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > (distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed)) 
						)
					{
						vehiclesInNet[ID].lanechangestate = 1;
					}
				}
			}
			if (vehiclesInNet[ID].lanechangestate == 1 && vehiclesInNet[ID].returnlanestate == 0)  
			{
				//lane-changing safety judgement
				if ((platoons[vehiclesInNet[ID].platoonID].turndirection != 0 && 
					(vehiclesInNet[ID].headwayDistance - previousVehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, previousVehicle.speed) &&
					(fronttargetvehicle.headwayDistance - fronttargetvehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) &&
					(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed))
					||
					(platoons[vehiclesInNet[ID].platoonID].turndirection == 0 && 
					(fronttargetvehicle.headwayDistance - fronttargetvehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) &&
					(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed))
					)
				{
					//target reference
					Mx->k0.setZero();
					Mx->lat_slope.setZero();
					//state initialize
					Mx->s.setOnes(); Mx->s = Mx->s * vehiclesInNet[ID].speed * currentVehicle.timestep;
					Mx->state_vector_lonspeed.setOnes(); Mx->state_vector_lonspeed = Mx->state_vector_lonspeed * vehiclesInNet[ID].speed;
					Mx->Lat_position_tar.setOnes(); Mx->Lat_position_tar = Mx->Lat_position_tar * ((platoons[vehiclesInNet[ID].platoonID].targetlane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2);  
					Mx->Head_angle_tar.setZero();
					return 1;
				}
				else
				{
					vehiclesInNet[ID].returnlanestate = 1;
				}
			}
			if (vehiclesInNet[ID].returnlanestate == 1)  
			{
				//target reference in lane-returning
				Mx->k0.setZero();
				Mx->lat_slope.setZero();
				Mx->s.setOnes(); Mx->s = Mx->s * vehiclesInNet[ID].speed * currentVehicle.timestep;
				Mx->state_vector_lonspeed.setOnes(); Mx->state_vector_lonspeed = Mx->state_vector_lonspeed * vehiclesInNet[ID].speed;
				Mx->Lat_position_tar.setOnes(); Mx->Lat_position_tar = Mx->Lat_position_tar * ((platoons[vehiclesInNet[ID].platoonID].currentlane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2);  
				Mx->Head_angle_tar.setZero();
				return 1;
			}
		}
	}
	else if (vehiclesInNet[ID].platoonID != 0 && platoons[vehiclesInNet[ID].platoonID].getNumInPlatoon(ID) != 1) 
	{
		SimVehicle platoonfrontvehicle = vehiclesInNet[platoons[vehiclesInNet[ID].platoonID].getFrontIDof(ID)];

		if (vehiclesInNet[ID].lanechangestate == 0)
		{
			vehiclesInNet[ID].activeLaneChange = 0;
			vehiclesInNet[ID].relativeTargetLane = 0;
			vehiclesInNet[ID].MPCstep = 0;
			if (vehiclesInNet[ID].currentLink == platoonfrontvehicle.currentLink
				&& vehiclesInNet[ID].nextLink != platoonfrontvehicle.nextLink
				&& vehiclesInNet[ID].nextLink != vehiclesInNet[ID].currentLink
				&& platoonfrontvehicle.nextLink != platoonfrontvehicle.currentLink)
			{
				platoons[vehiclesInNet[ID].platoonID].splitPlatoon(platoons, vehiclesInNet[ID].platoonID, ID, vehiclesInNet);
			}
			if (((platoonfrontvehicle.currentLane != vehiclesInNet[ID].currentLane && platoonfrontvehicle.MPCstep == 0 && platoonfrontvehicle.currentLink == vehiclesInNet[ID].currentLink) || (platoonfrontvehicle.MPCstep > 15)) &&
				(platoonfrontvehicle.lanechangestate == 1 || platoonfrontvehicle.currentLane != vehiclesInNet[ID].currentLane) && 
				platoonfrontvehicle.returnlanestate == 0 && vehiclesInNet[ID].nextLink == platoonfrontvehicle.nextLink &&  
				((platoons[vehiclesInNet[ID].platoonID].obstaclestate == 0 && 
				vehiclesInNet[ID].PosInLink > (platoons[vehiclesInNet[ID].platoonID].londistance - vehiclesInNet[ID].speed * 0.5)) ||
				(platoons[vehiclesInNet[ID].platoonID].obstaclestate == 1))
				)
			{
				vehiclesInNet[ID].decisiontime++;
				if (vehiclesInNet[ID].decisiontime == int(vehiclelanechangedecisiontime / currentVehicle.timestep) && vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane)
				{
					platoons[vehiclesInNet[ID].platoonID].splitPlatoon(platoons, vehiclesInNet[ID].platoonID, ID, vehiclesInNet);
					vehiclesInNet[ID].decisiontime = 0;
				}

				if (vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane && platoonfrontvehicle.id != previousVehicle.id &&  
					vehiclesInNet[ID].headwayDistance < (ACC_prmts[2] / 2 + max(0, (vehiclesInNet[ID].speed * ACC_prmts[1] / 2 + (vehiclesInNet[ID].speed * (vehiclesInNet[ID].speed - previousVehicle.speed)) / (2 * 2* sqrt(ACC_prmts[3] * ACC_prmts[4]))))))
				{
					platoons[vehiclesInNet[ID].platoonID].splitPlatoon(platoons, vehiclesInNet[ID].platoonID, ID, vehiclesInNet);
					vehiclesInNet[ID].decisiontime = 0;
				}
				//safety distance judgement
				if ((previousVehicle.id != platoonfrontvehicle.id && platoonfrontvehicle.id == fronttargetvehicle.id &&  
					(vehiclesInNet[ID].headwayDistance - previousVehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, previousVehicle.speed) &&
					(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) &&
					(fronttargetvehicle.headwayDistance - obstaclevehicle.headwayDistance ) > (distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) + vehiclesInNet[ID].length  + (DEFAULT_INNER_PLATOON_HEADWAY - 0.2) * vehiclesInNet[ID].speed)
					)
					||
					(previousVehicle.id == platoonfrontvehicle.id && 
					(vehiclesInNet[ID].headwayDistance) > (DEFAULT_INNER_PLATOON_HEADWAY - 0.2) * vehiclesInNet[ID].speed &&
					(fronttargetvehicle.headwayDistance - fronttargetvehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) &&
					(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed))
					)
				{
					vehiclesInNet[ID].lanechangestate = 1;
					vehiclesInNet[ID].decisiontime = 0;
				}
			}

		}
		if (vehiclesInNet[ID].lanechangestate == 1 && vehiclesInNet[ID].returnlanestate == 0)
		{
			if (platoonfrontvehicle.returnlanestate != 1 &&
				((vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane &&
				previousVehicle.id != platoonfrontvehicle.id && platoonfrontvehicle.id == fronttargetvehicle.id &&
				(vehiclesInNet[ID].headwayDistance - previousVehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, previousVehicle.speed) &&
				(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) &&
				(fronttargetvehicle.headwayDistance - obstaclevehicle.headwayDistance - fronttargetvehicle.length) > (distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) + vehiclesInNet[ID].length - fronttargetvehicle.length + (DEFAULT_INNER_PLATOON_HEADWAY - 0.2) * vehiclesInNet[ID].speed))
				||
				(vehiclesInNet[ID].currentLane != platoons[vehiclesInNet[ID].platoonID].targetlane &&
				previousVehicle.id == platoonfrontvehicle.id &&  
				vehiclesInNet[ID].headwayDistance > (DEFAULT_INNER_PLATOON_HEADWAY - 0.2) * vehiclesInNet[ID].speed &&
				(fronttargetvehicle.headwayDistance - fronttargetvehicle.length) > distance(2, 2, vehiclesInNet[ID].speed, fronttargetvehicle.speed) &&
				(abs(obstaclevehicle.headwayDistance) - vehiclesInNet[ID].length) > distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed))
				||
				(vehiclesInNet[ID].currentLane == platoons[vehiclesInNet[ID].platoonID].targetlane && obstaclevehicle.id != platoons[vehiclesInNet[ID].platoonID].getBackIDof(ID) && 
				(fronttargetvehicle.headwayDistance - obstaclevehicle.headwayDistance ) > (distance(1, 1, obstaclevehicle.speed, vehiclesInNet[ID].speed) + vehiclesInNet[ID].length  + (DEFAULT_INNER_PLATOON_HEADWAY - 0.2) * vehiclesInNet[ID].speed))
				||
				(vehiclesInNet[ID].currentLane == platoons[vehiclesInNet[ID].platoonID].targetlane && obstaclevehicle.id == platoons[vehiclesInNet[ID].platoonID].getBackIDof(ID) &&
				(fronttargetvehicle.headwayDistance - obstaclevehicle.headwayDistance ) > ((DEFAULT_INNER_PLATOON_HEADWAY - 0.2) * obstaclevehicle.speed + (DEFAULT_INNER_PLATOON_HEADWAY - 0.2) * vehiclesInNet[ID].speed))))
			{
				Mx->k0.setZero();
				Mx->lat_slope.setZero();
				Mx->s.setOnes(); Mx->s = Mx->s * vehiclesInNet[ID].speed * currentVehicle.timestep;
				Mx->state_vector_lonspeed.setOnes(); Mx->state_vector_lonspeed = Mx->state_vector_lonspeed * vehiclesInNet[ID].speed;
				target(Step_total, vehiclesInNet[ID].MPCstep, Mx->Lat_position_tar, Mx->Head_angle_tar, platoons[vehiclesInNet[ID].platoonID].Lead_Lat_position_tar, platoons[vehiclesInNet[ID].platoonID].Lead_Head_angle);  
				return 1;
			}
			else
			{
				vehiclesInNet[ID].returnlanestate = 1;
			}
		}
		if (vehiclesInNet[ID].returnlanestate == 1)
		{
			//target reference in lane-returning
			Mx->k0.setZero();
			Mx->lat_slope.setZero();
			Mx->s.setOnes(); Mx->s = Mx->s * vehiclesInNet[ID].speed * currentVehicle.timestep;
			Mx->state_vector_lonspeed.setOnes(); Mx->state_vector_lonspeed = Mx->state_vector_lonspeed * vehiclesInNet[ID].speed;
			Mx->Lat_position_tar.setOnes(); Mx->Lat_position_tar = Mx->Lat_position_tar * ((platoons[vehiclesInNet[ID].platoonID].currentlane - 1) * vehiclesInNet[ID].lanewidth + vehiclesInNet[ID].lanewidth / 2);
			Mx->Head_angle_tar.setZero();
			return 1;
		}
	}

	return 0;
}
double DecMaker::distance(int T1, int T2, double v0, double v1)
{
	//coumpute safety distance
	double t1 = 0.5;
	double t2 = 0.25;
	double bmax = 7;
	double l = 0.5; 
	double safetydistance;
	if (T1 == 1) //human driving
	{
		t1 = 0.5;
	}
	else if (T1 == 2)// autonomous driving 
	{
		t1 = 0.25;
	}
	if (T2 == 1) //car
	{
		t2 = 0.2;
	}
	else if (T2 == 2)//truck
	{
		t2 = 0.4;
	}
	safetydistance = (t1 + t2) * v0 + v0 * v0 / (2 * bmax) + l - v1 * v1 / (2 * bmax); //formula 
	return safetydistance;
}