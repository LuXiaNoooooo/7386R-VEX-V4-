void swing_handle_button(int key_swing_up_x, int key_swing_dn_x)
{
	if(pwr_off)
		swing.dir = swing_dir_none;

	//dn
	if(  key_swing_dn_x && !key_swing_up_x)
	{
		swing.dir = swing_dir_dn;
		pwr_off = 0;

		if( !limit_swing_dn_pressed)
		{
			swing_func(pwr_swing_down_max);
		}
		else
			swing_func(pwr_swing_keep_lowest);
	}
	//up
	else if(key_swing_up_x && !key_swing_dn_x)
	{
		swing.dir = swing_dir_up;
		pwr_off = 0;
		if( !limit_swing_up_pressed)
		{
			swing_func(pwr_swing_up_max);
		}
		else
			swing_func(pwr_swing_keep_highest);
	}
	else
	{
		switch(swing.dir)
		{
			case swing_dir_none:
			swing_func(0);
			break;
			case swing_dir_up:
			swing_func(pwr_swing_keep_highest);
			break;
			case swing_dir_dn:
			swing_func(pwr_swing_keep_lowest);
			break;
			default:
			break;
		}
	}
}


//
void swing_handle_joystick(int ch_src)
{
	if(pwr_off)
		swing.dir = swing_dir_none;

	swing.chx_swing_raw = ch_src;
	swing.chx_swing = abs(swing.chx_swing_raw) > 20 ? swing.chx_swing_raw : 0; //dead area


	///////////////////////////////////////////////////up
	if(swing.chx_swing > 0) //up
	{
		pwr_off = 0;
		swing.dir = swing_dir_up;
		if(!limit_swing_up_pressed)
		{
			swing_func(swing.chx_swing / 127.0 * pwr_swing_up_max); //max
		}
		else //pressed
		{
			swing_func(pwr_swing_keep_highest);
		}
	}
	//////////////////////////////down
	else if(swing.chx_swing < 0)
	{
		pwr_off = 0;
		swing.dir = swing_dir_dn;
		if(!limit_swing_dn_pressed)
		{
			swing_func(swing.chx_swing / 127.0 * abs(pwr_swing_down_max)); //max
		}
		else //pressed
		{
			swing_func(pwr_swing_keep_lowest);
		}
	}
	///////////////////////////////// swing.chx_swing=0 (abs<15)
	else
	{
		switch(swing.dir)
		{
			case swing_dir_none:
			swing_func(0);
			break;
			case swing_dir_up:
			swing_func(pwr_swing_keep_highest);
			break;
			case swing_dir_dn:
			swing_func(pwr_swing_keep_lowest);
			break;
			default:
			break;
		}
	}
}
