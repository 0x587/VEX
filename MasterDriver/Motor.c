#pragma config(Motor, port8, LeftWheel, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor, port9, RightWheel, tmotorVex393_MC29, openLoop, encoderPort, I2C_2)

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
		short MoveCode = getMotorEncoder(MotorList[i].Port) - MotorList[i].StartCode;
		MotorList[i].Speed = MoveCode * (1000/T) / 627.2 * 60;
	}
}

void PIDCommandMotor(DriverMotorValue* MotorList)
{
	for(short i = 0;i<5;i++)
	{
		if(i == 5)
		{
			motor[MotorList[i].Port] = MotorList[i].TargetSpeed;

		}else{
			short Error = MotorList[i].TargetSpeed - MotorList[i].Speed;
			MotorList[i].dValue += Error - MotorList[i].LastErroe;
			MotorList[i].LastErroe = Error;
			motor[MotorList[i].Port] += ((Error * MotorList[i].Kp)+(MotorList[i].dValue * MotorList[i].Kd));
		}
	}
}

void DriverMotorDo(command* Command)
{
	motor[LeftWheel]  = Command -> LeftWheelPower;
	motor[RightWheel] = Command -> RightWheelPower;
}
