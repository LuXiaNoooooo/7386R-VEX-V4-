///////////////////////////////////////////////////////////////////////////////////////
//  ########  #######  ########  ##      ##    ###
//  ##       ##     ## ##     ## ##  ##  ##   ## ##
//  ##       ##     ## ##     ## ##  ##  ##  ##   ##
//  ######   ##     ## ########  ##  ##  ## ##     ##
//  ##       ##     ## ##   ##   ##  ##  ## #########
//  ##       ##     ## ##    ##  ##  ##  ## ##     ##
//  ##        #######  ##     ##  ###  ###  ##     ##
void foward_adjust_with_enc_itself(int aim,int PWR_ABS, int forward, int turn,int Exit_Time,TTimers Timer_x,int stopcar)
{
	clearTimer(Timer_x);
	//
	int dir;
	if(enc_RTmove_L<aim)
		dir=1;
	if(enc_RTmove_L>aim)
		dir=-1;
	int err;
	int brake_pwr;
	float firstly_step=0.30;
	int ready_break=10;
	int enc_pre_brake_distance;
	long enc_now;
	long enc_last;
	int spd_move;
	float ad_kp=0.8;
	//
	int temp;
	int LR_err;
//max_pwr
	Pwr_ABS=abs(Pwr_ABS);
	if(forward>=Pwr_ABS)
		forward=Pwr_ABS;
	if(turn>=Pwr_ABS)
		turn=Pwr_ABS;
//kp
	//move
	if(enc_RTmove_L<aim)
	{

		enc_now=enc_move_L;
		enc_pre_brake_distance=abs(aim-enc_now)*firstly_step;
		//
		LR_err=SensorValue[enc_move_L]-SensorValue[enc_move_R];
		if(abs(LR_err)>=10)
			LR_err=sgn(LR_err)*4;
		//
		if(enc_RTmove_L<(aim-enc_pre_brake_distance))
		{
			move( dir*forward, -LR_err);
		}
		if(enc_RTmove_L>(aim-enc_pre_brake_distance)&&enc_RTmove_L<aim)
		{
			move( dir*ad_kp*forward, -LR_err );
		}
	}

	if(enc_RTmove_L>aim)
	{

		enc_now=enc_move_L;
		enc_pre_brake_distance=abs(aim-enc_now)*firstly_step;
		//
		LR_err=SensorValue[enc_move_L]-SensorValue[enc_move_R];
		if(abs(LR_err)>=10)
			LR_err=sgn(LR_err)*4;
		//
		if(enc_RTmove_L>(aim+enc_pre_brake_distance))
		{
			move( dir*forward, -LR_err);
		}
		if(enc_RTmove_L<(aim+enc_pre_brake_distance)&&enc_RTmove_L>aim)
		{
			move( dir*ad_kp*forward, -LR_err );
		}
	}
	while(1)
	{
		temp = SensorValue[enc_move_L];

		if(time1[Timer_x] > Exit_Time )
		{
			writeDebugStream("****forward:time-out aim:%d, final:%d T:%d \n", aim, temp, time1[Timer_x]);
			break;
		}
		if(abs(temp -aim) < ready_break)
		{
			writeDebugStream("****forward: OK aim:%d, final:%d T:%d\n", aim, temp, time1[Timer_x] );
			break;
		}
		wait1Msec(5);
	}
	move( -10*dir, 0 );
	wait1Msec(100);
	//after break;
	if(stopcar==STOPCAR)
	{
		while(1)
		{
			err=SensorValue[enc_RTmove_R]-aim;
			if( abs(err)>20 )
			{
				brake_pwr=abs(err);
				brake_pwr=(brake_pwr>18)?18:brake_pwr;
				move(-dir*brake_pwr,0);
				writeDebugStream("brake not enough,brake_pwr: %d\n",brake_pwr);
			}
			if(1)//stop
			{
				enc_last = SensorValue[enc_RTmove_L];
				wait1Msec(20);
				enc_now = SensorValue[enc_RTmove_L];
				spd_move = enc_now - enc_last;
				if(  abs(spd_move) < 2 )
				{
					writeDebugStream("brake stop:%d\n",spd_move);
				}

			}
			if(time1[Timer_x] > (200+Exit_Time))
			{
				writeDebugStream("brake time out\n");
				break;
			}
		}
		writeDebugStream("enc after braking:%d   time:%d\n",SensorValue[enc_move_L],time1[Timer_x]);
	}
	Move_Stop();
}

//////////////////////////////////////////////////////////////////////////////////////
//  ######## ##     ## ########  ##    ##
//     ##    ##     ## ##     ## ###   ##
//     ##    ##     ## ##     ## ####  ##
//     ##    ##     ## ########  ## ## ##
//     ##    ##     ## ##   ##   ##  ####
//     ##    ##     ## ##    ##  ##   ###
//     ##     #######  ##     ## ##    ##
void turn_with_enc(int dir,int Enc_aim, int Pwr_ABS, int forward, int Exit_Time, TTimers Timer_x, int stopcar)
{
	int temp;
	long enc_last, enc_now;
	int spd_move;
	int err;
	int brake_pwr;

	writeDebugStream("\n");
	ClearTimer(Timer_x);

	Pwr_ABS = abs(Pwr_ABS);

	move(forward,dir*Pwr_ABS);


	while(1)
	{
		temp = SensorValue[enc_move_L];

		if(time1[Timer_x] > Exit_Time )
		{
			writeDebugStream("****forward:time-out aim:%d, final:%d T:%d \n", Enc_aim, temp, time1[Timer_x]);
			break;
		}
		if(abs(temp - Enc_aim) < 10)
		{
			writeDebugStream("****forward: OK aim:%d, final:%d T:%d\n", Enc_aim, temp, time1[Timer_x] );
			break;
		}
		wait1Msec(5);
	}

	move(0, -dir * 18);
	if(stopcar == STOPCAR)
	{
		// ClearTimer(Timer_x);
		while(1)
		{
			err = SensorValue[enc_move_L] - Enc_aim;
			if( abs(err) > 20  )
			{
				brake_pwr = 15 + abs(err);
				brake_pwr = (brake_pwr > 22) ? 22 : brake_pwr;
				move(0,-dir * brake_pwr);
				writeDebugStream("brake not enough,brake_pwr: %d\n", brake_pwr);
			}

			if(1)//stop
			{
				enc_last = SensorValue[enc_move_L];
				wait1Msec(20);
				enc_now = SensorValue[enc_move_L];
				spd_move = enc_now - enc_last;
				if(  abs(spd_move) < 2  )
				{
					writeDebugStream("brake stop:%d\n", spd_move);
					break;
				}
			}

			if(time1[Timer_x] > (330 + Exit_Time) )
			{
				writeDebugStream("brake time out\n");
				break;
			}
		}
		writeDebugStream("enc after braking:%d   time:%d\n", SensorValue[enc_move_L], time1[Timer_x]);
	}
	Move_Stop();
}
