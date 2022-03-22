void lift_handle()
{
	if(pwr_off)
		lift.dir = lift_dir_none;

	//
	if(!key_lift_up &&  key_lift_dn)//dn
	{
		lift.one_key_flag=0;
		stopTask(lift_one_key_lowest_task);
		stopTask(lift_one_key_highest_task);

		lift.dir = lift_dir_dn;
		pwr_off = 0;

		if( !limit_lift_dn_pressed)
		{
			lift_func(pwr_lift_down_max);
		}
		else
			lift_func(pwr_lift_keep_lowest);
	}
	//up
	else if( key_lift_up && !key_lift_dn)
	{
		lift.one_key_flag=0;
		stopTask(lift_one_key_lowest_task);
		stopTask(lift_one_key_highest_task);

		lift.dir = lift_dir_up;
		pwr_off = 0;
		if( !limit_lift_up_pressed)
		{
			lift_func(pwr_lift_up_max);
		}
		else
			lift_func(pwr_lift_keep_highest);
	}
	else
	{
		if(lift.one_key_flag == 0)
		{
			switch(lift.dir)
			{
				case lift_dir_none:
				lift_func(0);
				break;
				case lift_dir_up:
				lift_func(pwr_lift_keep_highest);
				break;
				case lift_dir_dn:
				lift_func(pwr_lift_keep_lowest);
				break;
				default:
				break;
			};
		}
	}

	
	if(key_lift_one_key_lowest)
	{
		lift.one_key_flag=1;
		lift.dir = lift_dir_dn;
		pwr_off = 0;
		if(getTaskState(lift_one_key_lowest_task) == taskStateStopped)
		{
			startTask(lift_one_key_lowest_task);
		}
	}

	if(key_lift_one_key_highest)
	{
		lift.one_key_flag=1;
		lift.dir = lift_dir_up;
		pwr_off = 0;
		if(getTaskState(lift_one_key_highest_task) == taskStateStopped)
		{
			startTask(lift_one_key_highest_task);
		}
	}
}
