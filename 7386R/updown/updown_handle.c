#include "includes.c"


void updown_handle_joystick(int ch_src)
{

	if(pwr_off)
		updown.dir = 0;

	updown.chx_updown_raw = ch_src;
	updown.chx_updown = abs(updown.chx_updown_raw) > 20 ? updown.chx_updown_raw : 0; //dead area


	///////////////////////////////////////////////////up
	if(updown.chx_updown > 0) //up
	{
		pwr_off = 0;
		updown.dir = updown_dir_up;
		updown_func(updown.chx_updown / 127.0 * pwr_updown_up_max);
	}
	//////////////////////////////down
	else if(updown.chx_updown < 0)
	{
		pwr_off = 0;
		updown.dir = updown_dir_dn;
		if(!limit_updown_down_pressed)
		{
			updown_func(updown.chx_updown / 127.0 * abs(pwr_updown_down_max)); //max
		}
		else //pressed
		{
			updown_keep_lowest();
		}
	}
	///////////////////////////////// updown.chx_updown=0 (abs<15)
	else
	{
		switch(updown.dir)
		{
			case updown_dir_none:
				updown_func(0);
				break;
			default:
				updown_func(updown.dir * pwr_updown_hold_hgt);
				break;
		}
	}
}


void updown_handle_button(int key_updown_up_x, int key_updown_dn_x)
{
	if(pwr_off)
		updown.dir = updown_dir_none;

	//dn
	if(  key_updown_dn_x && !key_updown_up_x)
	{
		updown.dir = updown_dir_dn;
		pwr_off = 0;

		if( !limit_updown_down_pressed)
		{
			updown_func(pwr_updown_down_max);
		}
		else
			updown_func(pwr_updown_keep_lowest);
	}
	//up
	else if(key_updown_up_x && !key_updown_dn_x)
	{
		updown.dir = updown_dir_up;
		pwr_off = 0;
		updown_func(pwr_updown_up_max);

	}
	else
	{
		switch(updown.dir)
		{
			case updown_dir_none:
				updown_func(0);
				break;
			default:
				updown_func(updown.dir * pwr_updown_hold_hgt);
				break;
		}
	}
}