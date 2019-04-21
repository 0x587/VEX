#include "Struct.c"

void UpDateSpeed(DriverMotorValue* MotorList)
{
	short T=5;
	for(short i=0;i<4;i++)
	{
		MotorList[i].StartCode = getMotorEncoder(MotorList[i].Port);
	}
	wait1Msec(T);
	for(short i=0;i<4;i++)
	{
		MotorList[i].StartCode = getMotorEncoder(MotorList[i].Port);
		short MoveCode = getMotorEncoder(MotorList[i].Port) - MotorList[i].StartCode;
		MotorList[i].Speed = MoveCode * (1000/T) / 627.2 * 60;
	}
}
