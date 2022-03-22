void swing_func(int output)
{
	if(pwr_off)
		return;
	swing.pwr = output;
	motor[mtr_swing] = output;
}


task swing_one_key_lowest_task();
task swing_one_key_highest_task();

task swing_one_key_lowest_task()
{
	stopTask(swing_one_key_highest_task);
	swing_func( pwr_swing_down_max-2 );
	clearTimer(T_swing_handle);
	while(1)
	{
		if(time1[T_swing_handle] > 1500   )
			break;
		if(limit_swing_dn_pressed)
			break;
	}
	swing_func( pwr_swing_keep_lowest );
}
task swing_one_key_highest_task()
{
	stopTask(swing_one_key_lowest_task);
	swing_func( pwr_swing_up_max );
	clearTimer(T_swing_handle)
	while(1)
	{
		if(time1[T_swing_handle] > 700   )
			break;
	}
	swing_func( pwr_swing_keep_highest );
}
