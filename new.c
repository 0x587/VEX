#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    a,              sensorPotentiometer)
#pragma config(Sensor, in2,    b,              sensorPotentiometer)
#pragma config(Sensor, in3,    c,              sensorPotentiometer)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LeftLight,     tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           RightWheel,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           LeftWheel,     tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           Hand1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Hand2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           DtMotor,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           Dp1,           tmotorVex393_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port8,           Dp2,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           GlMotor,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          RightLight,    tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

struct command{
	short LeftMotor;
	short RightMotor;
	short Hand;
	short GL;
	short DT;
	short DP;
	bool RL;
	bool LL;
};
struct state{
	short up;
	short turn;
	short DpSpeed;
};
// global
command Command;
state State;
int TurnFlashT = 100;
bool isLight = true;
// global

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
task Flash()
{
	while(true)
	{
		if(!vexRT[Btn5D])
		{
			if(isLight)
			{
				if(vexRT[Btn7R] & vexRT[Btn8D])
				{
					// Boom Flash
					short BoomT;
					BoomT = State.DpSpeed;
					clearTimer(T1);
					motor[LeftLight]=motor[RightLight]=127;
					waitUntil(time1[T1]>BoomT);
					clearTimer(T1);
					motor[LeftLight]=motor[RightLight]=0;
					waitUntil(time1[T1]>BoomT);
				}else
				{
					// Turning FLash
					if(vexRT[Ch1]<0)
					{
						clearTimer(T1);
						motor[LeftLight]=127;
						waitUntil(time1[T1]>TurnFlashT);
						clearTimer(T1);
						motor[LeftLight]=0;
						waitUntil(time1[T1]>TurnFlashT);
					}else{motor[LeftLight]=127;}
					if(vexRT[Ch1]>0)
					{
						clearTimer(T2);
						motor[RightLight]=127;
						waitUntil(time1[T2]>TurnFlashT);
						clearTimer(T2);
						motor[RightLight]=0;
						waitUntil(time1[T2]>TurnFlashT);
					}else{motor[RightLight]=127;}
				}
			}else{
				motor[LeftLight]=motor[RightLight]=0;
			}
		}else{
				clearTimer(T1);
				motor[LeftLight]=motor[RightLight]=127;
				waitUntil(time1[T1]>50);
				clearTimer(T1);
				motor[LeftLight]=motor[RightLight]=0;
				waitUntil(time1[T1]>50);
				}
	}
}
task Read()
{
	while(true)
	{
		//Sensor
		State.DpSpeed=getMotorVelocity(Dp1);
		if(vexRT[Btn5U])
			{
				isLight=!isLight;
				wait1Msec(200);
			}
	}
}
task Do()
{
	while(true)
	{
		if(abs(Command.RightMotor)>20){motor[RightWheel]=Command.RightMotor;}
		else{motor[RightWheel]=0;}
		if(abs(Command.LeftMotor)>20){motor[LeftWheel]=Command.LeftMotor;}
		else{motor[LeftWheel]=0;}
		motor[DtMotor]=Command.DT;
		motor[GlMotor]=Command.GL;
		motor[Dp1]=motor[Dp2]=Command.DP;
		motor[Hand1]=motor[Hand2]=Command.Hand;
		SensorValue[in1]=123;
	}
}
void ManualControl()
{
	if (vexRT[Btn7U]) //DT com
	{
		if (vexRT[Btn8U]){Command.DT = 127;}
		else if (vexRT[Btn8D]){Command.DT = -127;}
		else{Command.DT = 0;}
	}
	else if (vexRT[Btn7D]) // GL com
	{
		if (vexRT[Btn8U]){Command.GL = 127;}
		else if (vexRT[Btn8D]){Command.GL = -127;}
		else if (vexRT[Btn8L]){Command.GL = 0;}
	}
	else if (vexRT[Btn7L]) // Hand com
	{
		if (vexRT[Btn8U]){Command.Hand = 127;}
		else if (vexRT[Btn8D]){Command.Hand = -127;}
		else{Command.Hand = 0;}
	}
	else if (vexRT[Btn7R]) // DP com
	{
		if (vexRT[Btn8U]){Command.DP = 127;}
		else if (vexRT[Btn8D]){Command.DP = -127;}
		else{Command.DP = 0;}
	}
	else
	{
		Command.DP = 0;
		Command.DT = 0;
		Command.Hand = 0;
	}
}
int tt;
task Decision()
{
	while(true)
	{
		tt = -4095+SensorValue[b]+(SensorValue[a]);
		ManualControl();
		short up, turn;
		up = DataHandling(vexRT[Ch3]);
		turn = (vexRT[Ch1]/2);
		if(abs(up)<64)
		{
			Command.LeftMotor = up - turn;
			Command.RightMotor = up + turn;
		}else{
			Command.LeftMotor = up - 2 * turn;
			Command.RightMotor = up + 2 * turn;
		}
	}
}

task main()
{
	bLCDBacklight = true;
	startTask(Read, kDefaultTaskPriority);
	startTask(Decision, kDefaultTaskPriority);
	startTask(Do, kDefaultTaskPriority);
	startTask(Flash, kDefaultTaskPriority);
	waitUntil(false);
}
