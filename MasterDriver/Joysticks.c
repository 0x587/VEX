#include "Struct.c"
short DataHandling(short data)
{
	int temp = (data*100/127);
	short back;
	if (temp > 0)
	{
		if (temp < 10){temp = 0;}
		else if (temp < 80)
		{
			temp = (temp - 10) / 2;
			}else{
			temp = (13 * temp) / 4 - 225;
		}
	}
	else
	{
		if (temp > -10){temp = 0;}
		else if (temp > -80)
		{
			temp = (temp + 10) / 2;
		}else
		{
			temp = (13 * temp) / 4 + 225;
		}

	}
	back = temp*127/100;
	if (abs(back) <= 15)
	{
		back =0;
	}
	return back;
}
void UpDateTargetSpeed(DriverMotorValue* MotorList)
{
	short Up, Yaw;
	Up = DataHandling(vexRT[Ch3]);
	Yaw = DataHandling(vexRT[Ch1]);
	if(abs(Up) > 75)
	{
		MotorList[0].TargetSpeed = (Up - Yaw*1.5);
		MotorList[1].TargetSpeed = (Up + Yaw*1.5);
	}else{
	MotorList[0].TargetSpeed = (Up - Yaw);
	MotorList[1].TargetSpeed = (Up + Yaw);
	}
}
