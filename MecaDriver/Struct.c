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
};
