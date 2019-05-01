struct DriverMotorValue
{
	tMotor Port;
	int StartCode;
	short Speed;
	short TargetPower;
	short TargetSpeed;
	int LastError;
	int dValue;
	short Force;
	bool isMoving;
};

struct command
{
	short LeftWheelPower;
	short RightWheelPower;
};
