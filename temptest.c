
task main()
{
	while(true)
	{
		if(vexRT[Btn7U])
		{
			motor[port2]=motor[port3]=-100;
		}else
		{
			motor[port2]=motor[port3]=0;
		}
	}


}
