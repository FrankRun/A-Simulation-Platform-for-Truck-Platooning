#pragma once
#ifndef __CONTROL_H
#define __CONTROL_H

#include <windows.h>
#include <map>
#include"Eigen\Dense"
#include"SimVehicle.h"
#include"Platoon.h"
#include"VehicleDynamicModel.h"

using namespace Eigen;

struct MatrixParameter
{
	MatrixXd k0;
	MatrixXd s;
	MatrixXd lat_slope;
	MatrixXd state_vector_lonspeed;
	MatrixXd Lat_position_tar;
	MatrixXd Head_angle_tar;
	MatrixXd State_vector;
};

class Control
{
public:
	Control();
	Control(const int LANE_OFFSET,const  int POSITION_OFFSET,const int Step_total,double innerplatoonheadway, double safedistance,const double ACC_prmts[]);
	~Control();	
	bool latcontrol(double Simulation_step_time, double Lat_position_error0, double Wheel_angle0, double Yaw_angle_error0, int Step_total,
		MatrixXd k0, MatrixXd Lat_position_tar, MatrixXd s, MatrixXd lat_slope, MatrixXd state_vector_lonspeed, MatrixXd Head_angle_tar, MatrixXd& State_vector,int numinplatoon);
	double loncontrol(double dis, double v_local, double a0, double v_leading, double hi, double safedis, double af, double timestep, int numinplatoon);
	int ACC_carFollowing(SimVehicle& currentVehicle, map<long, SimVehicle>& vehiclesInNet, SimVehicle adjacentVehicles[][5]);
	int carFollowing(MatrixParameter* Mx, SimVehicle& currentVehicle, VDM& CurrentVDM, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons, map<long, VDM>& VDMInNet, SimVehicle adjacentVehicles[][5]);
	int lanechangecontrol(MatrixParameter* Mx, SimVehicle& currentVehicle, map<long, SimVehicle>& vehiclesInNet, map<int, Platoon>& platoons);
private:
	int LANE_OFFSET;
	int POSITION_OFFSET;
	long followcolor;
	long leadingcolor;
	long originalcolor;
	int timesOfTransition;
	int Step_total;
	double innerplatoonheadway;
	double safedistance;
	double ACC_prmts[5];
};
#endif // !__CONTROL_H


