///////////////////////////////////////////////////////////////////////////////////////

#define up_stopped_spd 2


void up_enc(int Enc_aim, int Pwr_ABS, int turn, int Exit_Time, TTimers Timer_x, int brake)
{
	int temp;
	int dir = 1;
	long enc_last, enc_now;
	int spd_up;
	int err;
	int brake_pwr;

	writeDebugStream("\n");
	ClearTimer(Timer_x);

	Pwr_ABS = abs(Pwr_ABS);

	if(SensorValue[enc_updown] <= Enc_aim )
	{
	updown_func( 100 );
	dir=1;
	}
	else
	{
		updown_func( -100 );
		dir=-1
	}


	while(1)
	{
		temp = SensorValue[enc_updown];

		if(time1[Timer_x] > Exit_Time )
		{
			writeDebugStream("****up:time-out aim:%d, final:%d T:%d \n", Enc_aim, temp, time1[Timer_x]);
			break;
		}
		if(abs(temp - Enc_aim) < 10)
		{
			writeDebugStream("****up: OK aim:%d, final:%d T:%d\n", Enc_aim, temp, time1[Timer_x] );
			break;
		}
		wait1Msec(5);
	}

	updown_func( -dir*15 );
	if(brake == BRAKE)
	{
		// ClearTimer(Timer_x);
		while(1)
		{
			err=SensorValue[enc_updown]-Enc_aim;
			if( abs(err)>20  )
			{
				brake_pwr=15+abs(err);
				brake_pwr=(brake_pwr>20)?20:brake_pwr;
				updown_func(-dir*brake_pwr);
				writeDebugStream("brake not enough,brake_pwr: %d\n",brake_pwr);
			}

			if(1)//stop
			{
				enc_last = SensorValue[enc_updown];
				wait1Msec(20);
				enc_now = SensorValue[enc_updown];
				spd_up = enc_now - enc_last;
				if(  abs(spd_up) < up_stopped_spd  )
				{
					writeDebugStream("brake stop:%d\n",spd_up);
					break;
				}
			}

			if(time1[Timer_x] > (200+Exit_Time) )
			{
				writeDebugStream("brake time out\n");
				break;
			}
		}
		writeDebugStream("enc after braking:%d   time:%d\n",SensorValue[enc_updown],time1[Timer_x]);
	}

	