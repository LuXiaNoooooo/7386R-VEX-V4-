// //        ##       ## ######## ##     ## ########  ##    ##
// //       ##       ##     ##    ##     ## ##     ## ###   ##
// //      ##       ##      ##    ##     ## ##     ## ####  ##
// //     ##       ##       ##    ##     ## ########  ## ## ##
// //    ##       ##        ##    ##     ## ##   ##   ##  ####
// //   ##       ##         ##    ##     ## ##    ##  ##   ###
// //  ##       ##          ##     #######  ##     ## ##    ##
// /////////////////////////
void Turn_Without_PID(int Gyro_aim,short Speed_ABS,short forward,int Exit_Time,int Timer_x,int stopcar)
{
	int temp;
	int aim;

	int enc_last;
	int enc_now;
	int turn_spd;
	int spd_delta;
	float kp=6;
	int dir;

	aim=Gyro_aim;
	ClearTimer(Timer_x);

	if(SensorValue[Gyro]<= aim )
	{
		move(forward,Speed_ABS);
		dir=1;
	}
	else
	{
		move(forward,-Speed_ABS);
		dir=-1;
	}

	while(1)
	{
		temp=SensorValue[Gyro];

		if(time1[Timer_x]>Exit_Time )
		{
			writeDebugStream("\nturn:time-out aim:%d, final:%d T:%d\n",aim,temp,time1[Timer_x]);
			break;
		}

		if(abs(temp-aim)<10)
		{
			writeDebugStream("\nturn:aim:%d, final:%d T:%d\n",aim,SensorValue[Gyro],time1[Timer_x]);
			break;
		}
		if(temp>aim && dir==1)
		{
			writeDebugStream("\nturn:aim:%d, final:%d T:%d\n",aim,SensorValue[Gyro],time1[Timer_x]);
			break;
		}
		if(temp<aim && dir==-1)
		{
			writeDebugStream("\nturn:aim:%d, final:%d T:%d\n",aim,SensorValue[Gyro],time1[Timer_x]);
			break;
		}
	}
	if(stopcar==STOPCAR)
	{
		if(Speed_ABS>50)
		{
			move(-forward*0.3,-dir*20);
			wait1Msec(150);
		}
		else
		{
			move(-forward*0.3,-dir*18);
			wait1Msec(150);
		}
	}

	if(forward==0)
	{
		move(0,-dir*7);
	}
	else
	{
		move(-sgn(forward)*7,-dir*7);
	}
}