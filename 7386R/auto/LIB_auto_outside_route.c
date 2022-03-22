void lift_one_key_lowest_with_swing_down()
{

	unsigned long time_x;
	pwr_off=0;
	clearTimer(T_lift_handle);

	//key_start
	if(getTaskState(lift_one_key_lowest_task) == taskStateStopped)
	{
		startTask(lift_one_key_lowest_task);
		updown_func( 25 );
		swing_func( -40 );

		time_x = time1[T_lift_handle];
		while (1)
		{
			if (time1[T_lift_handle] > (time_x + 600))
			{
				updown_func( -37);
				swing_func( -41;
			}
			if(key_lift_dn || key_lift_up )
				break;

			if(limit_lift_dn_pressed)
			{
				writeDebugStream("time_lift_pressed:%d, \n",  time1[T_lift_handle]);
				break;
			}
		}

		lift_func( 2*pwr_lift_keep_highest );
		wait1Msec(200);
		swing_func( pwr_swing_keep_lowest -5);
		updown_func( pwr_lift_keep_highest );
		lift_func( pwr_lift_keep_highest );

	}

}
//

void swing_keep_hgt_to_put_zone()
{int  swing_down_time=500;
	unsigned long  time_swing_chx;
	//
	clearTimer(T_swing_handle);
	time_swing_chx=time1[T_swing_handle];
	swing_func( -80 );
	while(time1[T_swing_handle]<time_swing_chx+swing_down_time);
	swing_func( pwr_swing_keep_lowest );
}
	
