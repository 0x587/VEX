#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    HandCoder,      sensorPotentiometer)
#pragma config(Sensor, in2,    Xasic,          sensorAccelerometer)
#pragma config(Sensor, in3,    ExpanderBattery, sensorAnalog)
#pragma config(Sensor, in4,    Yasic,          sensorAccelerometer)
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
#pragma config(Motor,  port8,           LeftWheel,     tmotorVex393_MC29, PIDControl, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port9,           RightWheel,    tmotorVex393_MC29, PIDControl, encoderPort, I2C_2)
#pragma config(Motor,  port10,          Light,         tmotorVexFlashlight, openLoop, reversed)
#pragma config(DatalogSeries, 0, "LeftEncoder", Motors, MotorEncoder, port8, 10)
#pragma config(DatalogSeries, 1, "RightEncoder", Motors, MotorEncoder, port9, 10)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task FrontAuto5S()
{
	waitUntil(vexRT[Btn8U]);
	waitUntil(!vexRT[Btn8U]);
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	waitUntil(SensorValue[KeyTouch]);
	waitUntil(!SensorValue[KeyTouch]);
	clearTimer(T1);
	motor[BoomMotor] = motor[BoomMotorAnother] = 127;
	motor[HandMotor] = 50;
	waitUntil(SensorValue[BoomLock]);
	wait1Msec(500);
	motor[BoomMotor] = motor[BoomMotorAnother] = 0;
	setMotorTarget(LeftWheel, 0 ,70,false);
	setMotorTarget(RightWheel, 0,70,false);
	motor[HandMotor] = -35;
	waitUntil(getMotorTargetCompleted(LeftWheel)& getMotorTargetCompleted(RightWheel));
	motor[LeftWheel]=motor[RightWheel] = 127;
	waitUntil(getMotorEncoder(LeftWheel) > 950|getMotorEncoder(RightWheel) > 950);
	motor[LeftWheel]=motor[RightWheel] = 0;
	motor[HandMotor] = 127;
	wait1Msec(750);
}
task RearAuto10S()
{
	bLCDBacklight = true;
	clearTimer(T1);
	waitUntil(SensorValue[KeyTouch]);
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	short Code = 1000;
	setMotorTarget(LeftWheel, Code ,75,false);
	setMotorTarget(RightWheel,Code,75,false);
	waitUntil(getMotorTargetCompleted(LeftWheel)& getMotorTargetCompleted(RightWheel));
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	setMotorTarget(LeftWheel,  340  ,50,false);
	setMotorTarget(RightWheel,-340  ,50,false);
	waitUntil(getMotorTargetCompleted(LeftWheel)& getMotorTargetCompleted(RightWheel));
	motor[LeftWheel]=motor[RightWheel] = 127;
	wait1Msec(1500);
	motor[LeftWheel]=motor[RightWheel] = 0;
	displayLCDNumber(0,0,time1[T1]);
}
task main()
{/*
	clearLCDLine(0);clearLCDLine(1);
	short VoltageErroe = -0;
	bLCDBacklight = true;
	//Go
	resetMotorEncoder(LeftWheel);
	resetMotorEncoder(RightWheel);
	waitUntil(SensorValue[KeyTouch] | nLCDButtons==2);
	clearTimer(T1);clearTimer(T2);
	short UpCode1 = 1000;
	setMotorTarget(LeftWheel, UpCode1,100 + VoltageErroe,false);
	setMotorTarget(RightWheel, UpCode1,100 + VoltageErroe,false);
	waitUntil(getMotorTargetCompleted(LeftWheel)& getMotorTargetCompleted(RightWheel));
	displayLCDNumber(0,0,time1[T1]);
	displayLCDNumber(0,10,getMotorEncoder(LeftWheel) - getMotorEncoder(RightWheel));
	//Back

	short BackPlace = 550;
	//short BackPlace = 0;
	setMotorTarget(LeftWheel, BackPlace,50 + VoltageErroe,false);
	setMotorTarget(RightWheel, BackPlace,50 + VoltageErroe,false);
	waitUntil(getMotorTargetCompleted(LeftWheel)& getMotorTargetCompleted(RightWheel));
	//stopAllTasks();
	displayLCDNumber(1,0,time1[T2]);
	displayLCDNumber(1,10,getMotorEncoder(LeftWheel) - getMotorEncoder(RightWheel));
	//Turn
	//resetMotorEncoder(LeftWheel);
	//resetMotorEncoder(RightWheel);
	setMotorTarget(LeftWheel, getMotorEncoder(RightWheel) + 0,40,true);
	setMotorTarget(RightWheel, getMotorEncoder(RightWheel) -637,75,false);
	waitUntil(getMotorTargetCompleted(LeftWheel)& getMotorTargetCompleted(RightWheel));
	//waitUntil(vexRT[Btn8U]);
	//resetMotorEncoder(LeftWheel);
	//resetMotorEncoder(RightWheel);
	//waitUntil(vexRT[Btn8U]);
	waitUntil(false);
	setMotorTarget(LeftWheel, 64,getMotorEncoder(LeftWheel) + 50,false);
	setMotorTarget(RightWheel,64,getMotorEncoder(RightWheel) + 50,false);
	waitUntil(getMotorTargetCompleted(LeftWheel)& getMotorTargetCompleted(RightWheel));
	wait1Msec(1000);*/
	startTask(RearAuto5S);
	waitUntil(false);
}
