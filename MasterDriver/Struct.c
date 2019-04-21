struct DriverMotorValue
{
	tMotor Port;
	int StartCode;
	short Speed;
	short TargetSpeed;
	float Kp;
	float Kd;
	int LastErroe;
	int dValue;
	short Force;
};

struct command
{
	short LeftWheelPower;
	short RightWheelPower;
};
