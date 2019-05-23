#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    HandCoder,      sensorPotentiometer)
#pragma config(Sensor, in2,    Xasic,          sensorAccelerometer)
#pragma config(Sensor, in3,    ExpanderBattery, sensorAnalog)
#pragma config(Sensor, dgtl1,  BoomLock,       sensorTouch)
#pragma config(Sensor, dgtl2,  KeyTouch,       sensorTouch)
#pragma config(Sensor, dgtl3,  HighHandTouch,  sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           GlMotor,       tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port3,           DtMotor,       tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           HighHandMotor, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port5,           HandMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           BoomMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           BoomMotorAnother, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LeftWheel,     tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port9,           RightWheel,    tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port10,          Light,         tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Struct.c"
#include "Joysticks.c"
#include "Motor.c"
//Global Four Driver Motor
command Command;
///////////////////////////////
task DriverMotorCommand()
{
	while(true)
	{
		UpDateCommand(Command);
		DriverMotorDo(Command);
	}
}
bool Locking;
bool CanShoot;	bool isLight;
task Flash()
{
	while(true)
	{
		//Update isLight
		if(vexRT[Btn6D] & vexRT[Btn6U])
		{
			isLight=!isLight;
			waitUntil(!(vexRT[Btn6D] | vexRT[Btn6U]));
		}
		//Boom Flash
		if(isLight)
		{
			if(Locking)
			{
				short BoomT = 200;
				clearTimer(T2);
				motor[Light]=motor[Light]=127;
				waitUntil(time1[T2]>BoomT);
				clearTimer(T2);
				motor[Light]=motor[Light]=0;
				waitUntil(time1[T2]>BoomT);
				if(CanShoot)
				{
					motor[Light]=motor[Light]=127;
					waitUntil(!CanShoot);
					wait1Msec(500);
				}
			}else{
				short UsuallyT = 750;
				clearTimer(T2);
				motor[Light]=motor[Light]=127;
				waitUntil(time1[T2]>UsuallyT);
				clearTimer(T2);
				motor[Light]=motor[Light]=0;
				waitUntil(time1[T2]>UsuallyT/2);
			}
		}
	}
}
task DtControl()
{
	while (true)
	{
		if (vexRT[Btn6U]){motor[DtMotor] = 127;}//Dt
		else if (vexRT[Btn6D]){motor[DtMotor] = -127;}
		else{motor[DtMotor] = 0;}
	}
}
bool isUse;
task BoomControl()
{
	while (true)
	{
		//////////////////////////////
		if (vexRT[Btn5D])
		{
			Locking = !Locking;
			waitUntil(!vexRT[Btn5D]);
		}
		if (vexRT[Btn5U] & Locking)
		{
			CanShoot = !CanShoot;
			waitUntil(!vexRT[Btn5U]);
		}
		//////////////////////////////////
		if (Locking)
		{
				if (!SensorValue[BoomLock]){motor[BoomMotor] = motor[BoomMotorAnother] = 127;}
				else{motor[BoomMotor] = motor[BoomMotorAnother] = 50;}
		}else
		{
			if (vexRT[Btn7U]){motor[BoomMotor] = motor[BoomMotorAnother] = -127;}
			else if (vexRT[Btn7D])
			{
				isUse = true;
				if(SensorValue[HandCoder] > 1750){motor[HandMotor] = 100;}
				motor[BoomMotor] = motor[BoomMotorAnother] = 127;
			}
			else{motor[BoomMotor] = motor[BoomMotorAnother] = 0;isUse = false;}
		}
		if (CanShoot & SensorValue[BoomLock])
		{
			isUse = true;
			while(SensorValue[HandCoder] > 1750)
			{
				motor[HandMotor] = 100;
			}
			motor[HandMotor] = 0;
			motor[BoomMotor] = motor[BoomMotorAnother] = 127;
			waitUntil(!SensorValue[BoomLock]);
			motor[BoomMotor] = motor[BoomMotorAnother] = 0;
			isUse = CanShoot = false;
		}
		///////////////////////////////////
		if (!SensorValue[BoomLock]){clearTimer(T3);}
		if(time1[T3] > 2500){Locking = false;}//BoomTimeOut
	}
}
task HandControl()
{
	bool isDown;
	while(true)
	{
		//////////////////////////////////
		if (vexRT[Btn8L])
		{
			isUse = true;
			waitUntil(vexRT[Btn8L]);
			motor[HandMotor] = 127;
			waitUntil(SensorValue[HandCoder] < 1200);
			motor[HandMotor] = 0;
			isUse = false;
		}else if(vexRT[Btn8R])
		{
			isUse = true;
			clearTimer(T4);
			motor[HandMotor] = 127;
			waitUntil(SensorValue[HandCoder] <= 500 | time1[T4] >750);
			motor[HandMotor] = 50;
			if(SensorValue[HandCoder] <= 600){isDown = true;}
			else{isDown = false;}
			if(isDown)
			{
				waitUntil(vexRT[Btn8R] | time1[T4] >2000);
				motor[HandMotor] = -127;
				waitUntil(SensorValue[HandCoder] >= 750);
				motor[HandMotor] = -50;
				waitUntil(SensorValue[HandCoder] >= 1000);
				motor[HandMotor] = 50;
				waitUntil(SensorValue[HandCoder] >= 1250);
				motor[HandMotor] = 0;
				isDown = false;
			}else
			{
				motor[HandMotor] = -127;
				waitUntil(SensorValue[HandCoder] <= 2000);
				motor[HandMotor] = 0;
				isDown = false;
			}
			isUse = false;
		}else{
			if(!isUse)
			{
				if(SensorValue[HandCoder] <= 2450 )
				{
					motor[HandMotor] = -50;
				}else
				{
					motor[HandMotor] = 0;
				}
			}else{
					motor[HandMotor] = 0;
			}
		}
	}
}
task GlControl()
{
	short GL;
	while (true)
	{
		if (vexRT[Btn8U])
		{
			if(GL == 1) {}
			else if(GL == 0) {GL = 1;}
			else if(GL == -1){GL = 0;}
			waitUntil(!vexRT[Btn8U]);
		}
		if (vexRT[Btn8D])
		{
			if(GL == 1) {GL = 0;}
			else if(GL == 0) {GL = -1;}
			else if(GL == -1){}
			waitUntil(!vexRT[Btn8D]);
		}
		switch (GL)
		{
		case 1:
			motor[GlMotor] = 127;
			break;
		case 0:
			motor[GlMotor] = 0;
			break;
		case -1:
			motor[GlMotor] = -127;
			break;
		}
	}
}
task HighHandControl()
{
	bool Hold;
	while(true)
	{
		if (vexRT[Btn7R])
		{
			Hold = !Hold;
			waitUntil(!vexRT[Btn7R]);
		}
		if(Hold)
		{
			if(SensorValue[I2C_3] < -550){motor[HighHandMotor] = 75;}
			else if(SensorValue[I2C_3] > -350){motor[HighHandMotor] = -75;}
			else{motor[HighHandMotor] = 0;}
			if(vexRT[Btn7L])
			{
				motor[HighHandMotor] = -127;
				waitUntil(SensorValue[I2C_3] < -950);
				motor[HighHandMotor] = 0;
			}
		}else
		{
			if(!SensorValue[HighHandTouch]){motor[HighHandMotor] = 50;}
			else{motor[HighHandMotor] = 0;}
		}
	}
}
task main()
{
	//HighHand Rest
	bLCDBacklight = true;
	clearLCDLine(0);
	clearLCDLine(1);
	motor[HighHandMotor] = 75;
	clearTimer(T1);
	waitUntil(SensorValue[HighHandTouch] | time1[T1] > 1000);
	SensorValue[I2C_3] = 0;
	motor[HighHandMotor] = 0;
	startTask(GlControl, kDefaultTaskPriority);
	startTask(HandControl, kDefaultTaskPriority);
	startTask(BoomControl, kDefaultTaskPriority);
	startTask(Flash, kDefaultTaskPriority);
	startTask(DriverMotorCommand, kDefaultTaskPriority);
	startTask(DtControl, kDefaultTaskPriority);
	startTask(HighHandControl,kDefaultTaskPriority);
	//startTask(OutPutBoom , kDefaultTaskPriority);
	short CrotexBattery ,CBDecimal;
	short PowerExpBattery ,PEDecimal;
	while(true)
	{
		CrotexBattery = nAvgBatteryLevel/1000;
		CBDecimal = nAvgBatteryLevel-CrotexBattery*1000;
		float Temp = SensorValue[in3] /4 /70*1000;
		PowerExpBattery = Temp/1000;
		PEDecimal = Temp-PowerExpBattery*1000;
		displayLCDString(0,0,"Crotex:");
		displayLCDNumber(0,8,CrotexBattery);
		displayLCDChar(0,9,'.');
		displayLCDNumber(0,10,CBDecimal);
		displayLCDChar(0,13,220);
		displayLCDString(1,0,"PowerExp:");
    displayLCDNumber(1,9,SensorValue[in3]/4/70);
    displayLCDChar(1,10,'.');
    displayLCDNumber(1,11,(SensorValue[in3] - (SensorValue[in3]/70)/4));
    displayLCDChar(1,14,220);
    wait1Msec(500
    );
	}
}
