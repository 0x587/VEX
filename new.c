#pragma config(Sensor, in1,    ,               sensorPotentiometer)
#pragma config(Sensor, in2,    ,               sensorPotentiometer)
#pragma config(Sensor, dgtl1,  LeftEncode,     sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  RightEncode,    sensorQuadEncoder)
#pragma config(Motor,  port1,           LeftLight,     tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           RightWheel,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LeftWheel,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           Hand1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Hand2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           DtMotor,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Dp1,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Dp2,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           GlMotor,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          RightLight,    tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

struct Command{
	short LeftMotor;
	short RightMotor;
	short Hand;
	short GL;
	short DT;
	short DP;
	bool RL;
	bool LL;
};
struct State{
	short up;
	short turn;
	int LeftPalstance;
	int RightPalstance;
	short LeftPower;
	short RightPower;
	int Range;
	int HandState;
};
// global
Command command;
State state;
int T = 100;
// global
void GetPalstance()
{
	// return Palstance rad/s
	int StartLCode, StartRCode;
	StartLCode = SensorValue[LeftEncode];
	StartRCode = SensorValue[RightEncode];
	wait1Msec(5);
	state.LeftPalstance = (SensorValue[LeftEncode] - StartLCode) / 5 * 1000;
	state.RightPalstance = (SensorValue[RightEncode] - StartRCode) / 5 * 1000;
}
short DataHandling(short data)
{
	int temp = (data*100/127);
	short back;
	if (temp > 0)
	{
		if (temp < 10){temp = 0;}
		else if (temp < 80)
		{
			temp = 5 * (temp - 10) / 7;
		}else{
			temp = (5 * temp) / 2 - 150;
		}
	}
	else
	{
		if (temp > -10){temp = 0;}
		else if (temp > -80)
		{
			temp = 5 * (temp + 10) / 7;
		}else
		{
			temp = (5 * temp) / 2 + 150;
		}

	}
	back = temp*127/100;
	return back;
}
task LeftFlash()
{
	clearTimer(T1);
	while(time1[T1]<T)
	{
	motor[LeftLight]=127;
	}
	clearTimer(T1);
	while(time1[T1]<T)
	{
	motor[LeftLight]=0;
	}
}
task RightFlash()
{
	clearTimer(T2);
	while(time1[T2] <T)
	{
	motor[RightLight]=-127;
	}
	clearTimer(T2);
	while(time1[T2]<T)
	{
	motor[RightLight]=0;
	}
}
task Read()
{
	while(true)
	{
		//Sensor
		GetPalstance();
	}
}
task Do()
{
	while(true)
	{
		if(abs(command.RightMotor)>20){motor[RightWheel]=command.RightMotor;}
		else{motor[RightWheel]=0;}
		if(abs(command.LeftMotor)>20){motor[LeftWheel]=command.LeftMotor;}
		else{motor[LeftWheel]=0;}
		motor[DtMotor]=command.DT;
		motor[GlMotor]=command.GL;
		motor[Dp1]=motor[Dp2]=command.DP;
		motor[Hand1]=motor[Hand2]=command.Hand;
	}
}
void ManualControl()
{
	if (vexRT[Btn7U]) //DT com
	{
		if (vexRT[Btn8U]){command.DT = 127;}
		else if (vexRT[Btn8D]){command.DT = -127;}
		else{command.DT = 0;}
	}
	else if (vexRT[Btn7D]) // GL com
	{
		if (vexRT[Btn8U]){command.GL = 127;}
		else if (vexRT[Btn8D]){command.GL = -127;}
		else if (vexRT[Btn8L]){command.GL = 0;}
	}
	else if (vexRT[Btn7L]) // Hand com
	{
		if (vexRT[Btn8U]){command.Hand = 127;}
		else if (vexRT[Btn8D]){command.Hand = -127;}
		else{command.Hand = 0;}
	}
	else if (vexRT[Btn7R]) // DP com
	{
		if (vexRT[Btn8U]){command.DP = 127;}
		else if (vexRT[Btn8D]){command.DP = -127;}
		else{command.DP = 0;}
	}
	else
	{
		command.DP = 0;
		command.DT = 0;
		command.Hand = 0;
	}
}
task Decision()
{
	while(true)
	{
		ManualControl();
		short up, turn;
		up = DataHandling(vexRT[Ch3]);
		turn = DataHandling(vexRT[Ch1]);
		command.LeftMotor = up - turn;
		command.RightMotor = up + turn;
	}
}
task main()
{
	bLCDBacklight = true;
		startTask(Read, kDefaultTaskPriority);
		startTask(Decision, kDefaultTaskPriority);
		startTask(Do, kDefaultTaskPriority);
		startTask(RightFlash, 8);
		startTask(LeftFlash, 8);
}