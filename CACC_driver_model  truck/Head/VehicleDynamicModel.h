#pragma once
#ifndef _VEHICLEDYNAMICMODEL_H_
#define _VEHICLEDYNAMICMODEL_H_
#include"MercedesBenz.h"

class VDM  // Vehicle Dynamic Model
{
private:
	MercedesBenzModelClass rtObj;
public:
	VDM();
	~VDM();
	void Initialize();
	void OneStep(double self_acceleration);
	double OutPutacc();
	double OutPutspeed();
	void SetParameter(double Initial_Speed);
};

#endif // !_VEHICLEDYNAMICMODEL_H_