#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           LeftLight,     tmotorVexFlashlight, openLoop, reversed)
#pragma config(Motor,  port2,           RightWheel,    tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port3,           LeftWheel,     tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port4,           Hand1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Hand2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           DtMotor,       tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           Dp1,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Dp2,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           GlMotor,       tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          RightLight,    tmotorVexFlashlight, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
void run(short max, short value)
{
	short start_left = SensorValue[left_encode];
	short start_right = SensorValue[right_encode];
	short target_left = SensorValue[left_encode]+value;
	short target_right = SensorValue[right_encode]+value;
	short up_x = (value/10)*2;
	short down_x = (value/10)*3;
	short power;
	if(max<20){max=30;}
	/*************************************power up*******************************************************/
	for(int i=0;i<5;i++)
	{
		power = 20+((max-20)/5*i);
		while(((start_left+(up_x/5*i) - SensorValue[left_encode])>20)|((start_right+(up_x/5*i) - SensorValue[right_encode])>20))
		{
			motor[left_center]=motor[left_qh]=power;
			motor[right_center]=motor[right_qh]=power;
		}
	}
	/*************************************power keep******************************************************/
	while(
		(((target_left-down_x)-SensorValue[left_encode])>20)
		|
		(((target_right-down_x)-SensorValue[right_encode])>20))
	{
	motor[left_qh]=motor[left_center]=max;
	motor[right_qh]=motor[right_center]=max;
	}
	/*************************************power down*******************************************************/
	for(int i=0;i<3;i++)
	{
		power = 20+((max-20)/3*(3-i));
		while(((target_left-down_x+(down_x/3*i)-SensorValue[left_encode])>20) | ((target_left-down_x+(down_x/3*i)-SensorValue[right_encode])>20))
		{
			motor[left_center]=motor[left_qh]=power;
			motor[right_center]=motor[right_qh]=power;
		}
	}
	/*************************************break**********************************************************/
	for(int i=0;i<10;i++)
	{
		motor[left_qh]=motor[left_center]=motor[right_qh]=motor[right_center]=-i-5;
		wait1Msec(5);
	}
}
void turn(bool rl = true)
{
	short start_left = SensorValue[left_encode];
	short start_right = SensorValue[right_encode];
	short value = 630;
	short power;
	if(rl)
	{
		while(abs(start_left+(value/5*4)-SensorValue[left_encode])>10)
		{
			motor[left_center]=motor[left_qh]=50;
			motor[right_center]=motor[right_qh]=-10;
		}
		for(int i=0;i<5;i++)
		{
			power = 20+(30/5*(5-i));
			while(abs((start_left+(value/5*4)+(value/5/5*i))-SensorValue[left_encode])>10)
			{
				motor[left_center]=motor[left_qh]=power;
			}
		}
		motor[left_center]=motor[left_qh]=-15;
		wait10Msec(5);
	}else{
		while(abs(start_right+(value/5*4)-SensorValue[right_encode])>10)
		{
			motor[right_center]=motor[right_qh]=50;
			motor[left_center]=motor[left_qh]=-10;
		}
		for(int i=0;i<5;i++)
		{
			power = 20+(30/5*(5-i));
			while(abs((start_right+(value/5*4)+(value/5/5*i))-SensorValue[right_encode])>10)
			{
				motor[right_center]=motor[right_qh]=power;
			}
		}
		motor[left_center]=motor[left_qh]=-15;
		wait10Msec(5);
	}
}
void shoot()
{
	motor[dp1]=motor[dp2]=100;
	wait10Msec(300);
}
void gl_able(bool En)
{
	if(En)
	{
		motor[gl_motor]=127;
	}else{
		motor[gl_motor]=0;
	}
}
void dt_able(bool En)
{
	if(En)
	{
		motor[dt_motor]=127;
	}else{
		motor[dt_motor]=0;
	}
}
task main()
{
	run(50,500);
	turn();
}
