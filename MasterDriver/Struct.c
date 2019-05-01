struct DriverMotorValue
{
	tMotor Port;
	int StartCode;
	short Speed;
	short TargetPower;
	short TargetSpeed;
	short Force;
	bool isMoving;
};

struct command
{
	short LeftWheelPower;
	short RightWheelPower;
};
