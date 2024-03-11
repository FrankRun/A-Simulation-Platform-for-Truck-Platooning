#include"VehicleDynamicModel.h"

VDM::VDM()
{

}

VDM::~VDM()
{

}

void VDM::Initialize()
{
	this->rtObj.initialize();
}

void VDM::SetParameter(double Initial_Speed)
{
	this->rtObj.rtU.initial_speed = Initial_Speed; //input
}

void VDM::OneStep(double self_acceleration)
{
	static boolean_T OverrunFlag = false;
	if (OverrunFlag) {
		rtmSetErrorStatus(this->rtObj.getRTM(), "Overrun");
		return;
	}
	OverrunFlag = true;
	// input 
	this->rtObj.rtU.self_acceleration = self_acceleration;// input
	this->rtObj.step();// VDM run
	OverrunFlag = false;
}

double VDM::OutPutacc()
{
	return this->rtObj.rtY.output_acceleration; // output
}
double VDM::OutPutspeed()
{
	return this->rtObj.rtY.output_speed;//output
}






