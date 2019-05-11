#include "Struct.c"
#include "Math.c"
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
void UpDateCommand(command* Command)
{
	short Up, Yaw;
	Up = DataHandling(Max(vexRT[Ch3], vexRT[Ch2]));
	Yaw = DataHandling(Max(vexRT[Ch1], vexRT[Ch4]));
	if(abs(Up) > 75)
	{
		Command -> RightWheelPower = (Up - Yaw * 1.5);
		Command -> LeftWheelPower  = (Up + Yaw*1.5);
	}else
	{
		Command -> RightWheelPower = (Up - Yaw );
		Command -> LeftWheelPower = (Up + Yaw);
	}
}
