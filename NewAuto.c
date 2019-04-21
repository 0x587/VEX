#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LeftLight,     tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           RightWheel,    tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_4)
#pragma config(Motor,  port3,           LeftWheel,     tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port4,           Hand1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Hand2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           DtMotor,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           Dp1,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Dp2,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           GlMotor,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          RightLight,    tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

bool CanDriver = true;
bool isBreak = true;
task Break()
{
	float Kp=0.2;
	//float kd;
	short LError,RError;
	while(true)
	{
		if(isBreak)
		{
			short
			SLC =-getMotorEncoder(LeftWheel),
			SRC = getMotorEncoder(RightWheel);
			waitUntil(CanDriver);
			LError=getMotorEncoder(LeftWheel)-SLC;
			RError=getMotorEncoder(RightWheel)-SRC;
			motor[LeftWheel]=getMotorEncoder(LeftWheel)*Kp;
			motor[RightWheel]=getMotorEncoder(RightWheel)*Kp;
		}
	}

}
task main()
{
	startTask(Break,kDefaultTaskPriority);
	waitUntil(1==2);
}