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
	return back;
}
void UpDateTargetSpeed(DriverMotorValue* MotorList)
{
	short Xasis,Yasis,Yaw;
	Xasis = DataHandling(vexRT[Ch4]);
	Yasis = DataHandling(vexRT[Ch3]);
	Yaw = DataHandling(vexRT[Ch1]);

	MotorList[0].TargetSpeed = (Yasis + Xasis + Yaw);
	MotorList[0].TargetSpeed = (Yasis + -Xasis + Yaw);
	MotorList[0].TargetSpeed = (Yasis + -Xasis + -Yaw);
	MotorList[0].TargetSpeed = (Yasis + Xasis + -Yaw);
}
