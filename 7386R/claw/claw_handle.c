void claw_handle()
{

	if(pwr_off)
	{
		claw.status = claw_sta_pwr_off;
		claw.dir = claw_dir_none;
	}

	if(key_claw_open &&  !key_claw_close )            //open
	{
		pwr_off = 0;
		claw.dir = claw_dir_open;

		if (claw.reset == 0)
		{
			claw.reset = 1;
			ClearTimer(T_claw_handle);
		}

		if(time1[T_claw_handle] > 450)
		{
			claw.status = claw_sta_opening;
			claw_func(pwr_claw_hold_open);
		}
		else
		{
			claw.status = claw_sta_opening;
			claw_func(pwr_claw_open);
		}
	}
	else if(key_claw_close  &&  !key_claw_open)       //close
	{
		pwr_off = 0;
		claw.dir = claw_dir_close;

		if (claw.reset == 0)
		{
			claw.reset = 1;
			ClearTimer(T_claw_handle);
		}

		if(time1[T_claw_handle] > 350)
		{
			claw.status = claw_sta_hold_close_powerful;
			claw_func(pwr_claw_hold_close_powerful);
		}
		else
		{
			claw.status = claw_sta_closing;
			claw_func(pwr_claw_close);
		}
	}
	else
	{
		claw.reset = 0;

		switch(claw.status)
		{
			case claw_sta_pwr_off:
				claw_func(0);
				break;
			case claw_sta_opening:
				claw_func(pwr_claw_hold_open);
				break;
			case claw_sta_closing:
				claw_func(pwr_claw_hold_close);
				break;
			case claw_sta_hold_close_powerful:
				claw_func(pwr_claw_hold_close_powerful);
				break;
			default:
				break;
		};
	}
}


