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
#pragma config(Motor,  port8,           LeftWheel,     tmotorVex393HighSpeed_MC29, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port9,           RightWheel,    tmotorVex393HighSpeed_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port10,          Light,         tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

short LeftTarget, RightTarget;
short LeftPower, RightPower;
bool LeftFalg, RightFalg;

short x;

void GetBall()
{
	motor[LeftWheel] = motor[RightWheel] = 50;
	waitUntil(getMotorEncoder(LeftWheel) > 200 | getMotorEncoder(RightWheel) > 200);
	motor[LeftWheel] = motor[RightWheel] = 100;
	waitUntil(getMotorEncoder(LeftWheel) > 500 | getMotorEncoder(RightWheel) > 500);
	motor[GlMotor] = 127;
	waitUntil(getMotorEncoder(LeftWheel) > 1000 | getMotorEncoder(RightWheel) > 1000);
	motor[LeftWheel] = motor[RightWheel] = 35;
	waitUntil(getMotorEncoder(LeftWheel) > 1450 | getMotorEncoder(RightWheel) > 1450);
	motor[LeftWheel] = motor[RightWheel] = -50;
	waitUntil(getMotorEncoder(LeftWheel) > 1200 | getMotorEncoder(RightWheel) > 1200);
	motor[LeftWheel] = motor[RightWheel] = -75;
	waitUntil(getMotorEncoder(LeftWheel) > 1000 | getMotorEncoder(RightWheel) > 1000);
	motor[LeftWheel] = motor[RightWheel] = -100;
	waitUntil(getMotorEncoder(LeftWheel) > 800 | getMotorEncoder(RightWheel) > 800);
	motor[LeftWheel] = motor[RightWheel] = -127;
	waitUntil(getMotorEncoder(LeftWheel) < 600 | getMotorEncoder(RightWheel) < 600);
	motor[GlMotor] = 0;
	waitUntil(getMotorEncoder(LeftWheel) < 500 | getMotorEncoder(RightWheel) < 500);
	motor[LeftWheel] = motor[RightWheel] = -75;
	waitUntil(getMotorEncoder(LeftWheel) < 100 | getMotorEncoder(RightWheel) < 60);
	motor[LeftWheel] = motor[RightWheel] = -25;
	waitUntil(getMotorEncoder(LeftWheel) < 50 | getMotorEncoder(RightWheel) < 40);
	wait1Msec(500);
	motor[LeftWheel] = motor[RightWheel] = 0;
	motor[GlMotor] = 0;
}
task LeftRun()
{
	motor[LeftWheel] = LeftPower;
	if(LeftPower >0 )
	{
		waitUntil(getMotorEncoder(LeftWheel) > LeftTarget - 15);
		motor[LeftWheel] = -1* LeftPower *2/5;
		}else{
		waitUntil(getMotorEncoder(LeftWheel) < LeftTarget + 15);
		motor[LeftWheel] = 1* LeftPower *2/5;
	}
	wait1Msec(50);
	motor[LeftWheel] = 0;
	LeftFalg = true;
}

task RightRun()
{
	motor[RightWheel] = RightPower;
	waitUntil(getMotorEncoder(RightWheel) < RightTarget);
	if(RightPower > 0)
	{
		waitUntil(getMotorEncoder(RightWheel) > RightTarget);
		motor[RightWheel] = -1* RightPower *2/5;
		}else{
		waitUntil(getMotorEncoder(RightWheel) < RightTarget);
		motor[RightWheel] = 1* RightPower *2/5;
	}

	wait1Msec(50);
	motor[RightWheel] = 0;
	RightFalg = true;
}
void Turn()
{
	short TurnCode = 338;
	LeftFalg = RightFalg =false;
	LeftTarget = TurnCode;
	RightTarget = -TurnCode;
	LeftPower = 40;
	RightPower = -40;
	startTask(LeftRun);
	startTask(RightRun);
	motor[DtMotor]=120;
	clearTimer(T1);
	waitUntil(time1[T1] > 600);
	motor[DtMotor]=0;
	waitUntil(LeftFalg & RightFalg);
}
void BoomOne()
{
	while(SensorValue[HandCoder] < 1200)
	{
		motor[HandMotor] = 50;
	}
	motor[HandMotor] = 0;
	motor[BoomMotor]=motor[BoomMotorAnother]=127;
	waitUntil(SensorValue[BoomLock]);
	wait1Msec(325);
	motor[BoomMotor]=motor[BoomMotorAnother]=0;
}
void HandDriven()
{
	while(8426==8426)
	{
		if(nLCDButtons==1){waitUntil(nLCDButtons==0);motor[LeftWheel]=motor[RightWheel]=45;}else{motor[LeftWheel]=motor[RightWheel]=0;}
		if(nLCDButtons==3){waitUntil(nLCDButtons==0);motor[LeftWheel]=motor[RightWheel]=-45;}else{motor[LeftWheel]=motor[RightWheel]=0;}
		motor[LeftWheel]=motor[RightWheel]=vexRT[Ch3];
		motor[LeftWheel]=vexRT[Ch2];
		motor[RightWheel]=-vexRT[Ch2];
	}
}
/*task main()
{
	while(true)
	{
	bLCDBacklight = true;
	x=0;
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	waitUntil(SensorValue[KeyTouch] | nLCDButtons==2);
	GetBall();
	//if(nLCDButtons==1){motor[LeftWheel]=motor[RightWheel]=50;waitUntil}
	//waitUntil(nLCDButtons==2);
	LeftTarget = RightTarget = 425;
	LeftPower = RightPower = 50;
	LeftFalg = RightFalg =false;
	startTask(LeftRun);
	startTask(RightRun);
	waitUntil(LeftFalg & RightFalg);
	wait1Msec(50);
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	wait1Msec(100);
	Turn();
//	waitUntil(false);
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	BoomOne();
	LeftTarget = RightTarget = 600;
	LeftPower = RightPower = 75;
	LeftFalg = RightFalg =false;
	startTask(LeftRun);
	startTask(RightRun);
	motor[GlMotor] = 127;
	motor[DtMotor]=120;
	wait1Msec(1000);
	waitUntil(LeftFalg & RightFalg);
	BoomOne();
}
}*/
task main()
{
	bLCDBacklight = true;
	//motor[GlMotor] = motor[DtMotor] = 0;
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	//waitUntil(SensorValue[KeyTouch] | nLCDButtons==2);
	short UpCode1 = 1000;
	setMotorTarget(LeftWheel, UpCode1,64,false);
	setMotorTarget(RightWheel, UpCode1,64,false);
	waitUntil(
				abs(getMotorEncoder(LeftWheel) - UpCode1/4) < 50
				&
				abs(getMotorEncoder(RightWheel) - UpCode1/4) < 50
	);
	setMotorTarget(LeftWheel, UpCode1,122,false);
	setMotorTarget(RightWheel, UpCode1,127,false);
	waitUntil(
				abs(getMotorEncoder(LeftWheel) - UpCode1) < 50
				&
				abs(getMotorEncoder(RightWheel) - UpCode1) < 50
	);
	wait1Msec(1000);
	short BackPlace = 550;
	setMotorTarget(LeftWheel, BackPlace,100,false);
	setMotorTarget(RightWheel, BackPlace,100,false);
	waitUntil(
				getMotorEncoder(LeftWheel) < BackPlace +15
				&
				getMotorEncoder(RightWheel)< BackPlace +15
	);
	waitUntil(vexRT[Btn8D]);
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	setMotorTarget(RightWheel, -635,100,false);
	waitUntil(getMotorEncoder(RightWheel) <= 635);
	waitUntil(vexRT[Btn8U]);
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	//setMotorTarget(LeftWheel, 100,25,false);
	//setMotorTarget(RightWheel,100,25,false);
	wait1Msec(1000
}