#pragma config(Motor, port8, LeftWheel, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor, port9, RightWheel, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)

#include "Struct.c"
void UpDateSpeed(DriverMotorValue* MotorList)
{
	short T=5;//ms
	for (short i = 0; i < 2; i++)
	{
		MotorList[i].StartCode = getMotorEncoder(MotorList[i].Port);
	}
	wait1Msec(T);
	for (short i = 0; i < 2; i++)
	{
		short MoveCode = getMotorEncoder(MotorList[i].Port) - MotorList[i].StartCode;
		MotorList[i].Speed = MoveCode * (1000/T) / 627.2 * 60;
		if (abs(MotorList[i].Speed) > 0)
		{MotorList[i].isMoving = true;}
		else{MotorList[i].isMoving = false;}
	}
}

void DriverMotorDo(DriverMotorValue *MotorList)
{
	for (short i = 0; i < 2; i++)
	{
		motor[MotorList[i].Port] = MotorList[i].TargetPower;
	}
}
