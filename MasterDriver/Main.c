#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    HandCoder,      sensorPotentiometer)
#pragma config(Sensor, dgtl1,  BoomLock,       sensorTouch)
#pragma config(Sensor, dgtl2,  KeyTouch,       sensorTouch)
#pragma config(Sensor, dgtl3,  HighHandTouch,  sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           GlMotor,       tmotorVex393TurboSpeed_HBridge, openLoop)
#pragma config(Motor,  port3,           DtMotor,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           HighHandMotor, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port5,           HandMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           BoomMotor,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           BoomMotorAnother, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LeftWheel,     tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port9,           RightWheel,    tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port10,          Light,         tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Joysticks.c"
#include "Struct.c"
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
task Flash()
{
	bool isLight;
	while(true)
	{
		//Update isLight
		if(vexRT[Btn5U])
		{
			isLight=!isLight;
			wait1Msec(200);
		}
		//Boom Run
		if(vexRT[Btn8R] & vexRT[Btn5D])
		{
			short BoomT;
			BoomT = getMotorVelocity(BoomMotor);
			clearTimer(T1);
			motor[Light]=motor[Light]=127;
			waitUntil(time1[T1]>BoomT);
			clearTimer(T1);
			motor[Light]=motor[Light]=0;
			waitUntil(time1[T1]>BoomT);
		}
	}
}
task OtherDriver()
{

	while (true)
	{

		if (vexRT[Btn6U]){motor[DtMotor] = 127;}//Dt
		else if (vexRT[Btn6D]){motor[DtMotor] = -127;}
		else{motor[DtMotor] = 0;}


//////////////////////////////////////

	}
}
task Boom()
{
	bool Locking;
	bool CanShoot;
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
			else if (vexRT[Btn7D]){motor[BoomMotor] = motor[BoomMotorAnother] = 127;}
			else{motor[BoomMotor] = motor[BoomMotorAnother] = 0;}
		}
		if (CanShoot & SensorValue[BoomLock])
		{
			while(SensorValue[HandCoder] < 1200)
			{
				motor[HandMotor] = 30;
			}
			motor[HandMotor] = 0;
			motor[BoomMotor] = motor[BoomMotorAnother] = 127;
			waitUntil(!SensorValue[BoomLock]);
			motor[BoomMotor] = motor[BoomMotorAnother] = 0;
			CanShoot = false;
		}
		///////////////////////////////////
		if (!SensorValue[BoomLock]){clearTimer(T3);}
		if(time1[T3] > 2000){Locking = false;}
	}
}
task Hand()
{
	bool isDown;
	//bool isHold;
	while(true)
	{
		/////////////////////////////
		//////////////////////////////////
		if (vexRT[Btn8L])
		{
			clearTimer(T4);
			motor[HandMotor] = -127;
			waitUntil(SensorValue[HandCoder]< 720);
			waitUntil(vexRT[Btn8L] | time1[T4] >1000);
			motor[HandMotor] = 127;
			waitUntil(SensorValue[HandCoder]> 1800);
			motor[HandMotor] = 0;
		}else if(vexRT[Btn8R])
		{
			clearTimer(T4);
			motor[HandMotor] = 127;
			waitUntil(SensorValue[HandCoder] >= 2700 | time1[T4] >750);
			motor[HandMotor] = 70;
			if(SensorValue[HandCoder] >= 2700){isDown = true;}
			else{isDown = false;}
			if(isDown)
			{
				waitUntil(vexRT[Btn8R] | time1[T4] >2000);
				motor[HandMotor] = -127;
				waitUntil(SensorValue[HandCoder] <= 2000);
				motor[HandMotor] = 0;
				isDown = false;
			}else
			{
				motor[HandMotor] = -127;
				waitUntil(SensorValue[HandCoder] <= 2000);
				motor[HandMotor] = 0;
				isDown = false;
			}
		}else
		{
			motor[HandMotor] = 0;
		}
	}
}
task GlCom()
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
task main()
{
	startTask(GlCom, kDefaultTaskPriority);
	startTask(Hand, kDefaultTaskPriority);
	startTask(Boom, kDefaultTaskPriority);
	startTask(Flash, kDefaultTaskPriority);
	startTask(DriverMotorCommand, kDefaultTaskPriority);
	startTask(OtherDriver, kDefaultTaskPriority);
	//startTask(OutPutBoom , kDefaultTaskPriority);
	waitUntil(false);
}
