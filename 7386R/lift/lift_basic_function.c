void lift_func(int output)
{
	if(pwr_off)
		return;
	lift.pwr = output;
	motor[mtr_lift] = output;
}

task lift_one_key_lowest_task();
task lift_one_key_highest_task();

task lift_one_key_lowest_task()
{
	stopTask(lift_one_key_highest_task);
	lift_func( pwr_lift_down_max );
	clearTimer(T_lift_handle);
	while(1)
	{
		if(time1[T_lift_handle] > 2300   )
			break;
		if(limit_lift_dn_pressed)
			break;
	}
	lift_func( pwr_lift_keep_lowest );
	lift.one_key_flag = 0;
}

task lift_one_key_highest_task()
{
	stopTask(lift_one_key_lowest_task);
	lift_func( pwr_lift_up_max );
	clearTimer(T_lift_handle);
	while(1)
	{
		if(time1[T_lift_handle] > 1800   )
			break;
		if(limit_lift_up_pressed)
		{
			wait1Msec(100);
			break;
		}
	}
	lift_func( pwr_lift_keep_highest );
	lift.one_key_flag = 0;
}


void stop_lift()
{
	stopTask(lift_one_key_highest_task);
	stopTask(lift_one_key_lowest_task);
	lift.one_key_flag = 0;
	lift_func( 0 );
}
