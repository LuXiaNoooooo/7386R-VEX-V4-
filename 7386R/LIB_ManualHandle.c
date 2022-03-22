void manual_handle()
{
	Robot_Move(vexRT[Ch3], vexRT[Ch4], pwr_RT_max_vy, pwr_RT_max_turn, pwr_RT_abs_max);
	updown_handle_joystick(vexRT[Ch2]);
	swing_handle_button(key_swing_up, key_swing_dn);
	lift_handle();
	claw_handle();

	special_key_handle();

	if(vexRT[Btn7R] && !vexRT[Btn7L])
	{
		while(vexRT[Btn7R]){}
			lift_one_key_lowest_with_swing_down();
	}
	if(vexRT[Btn7U] && !vexRT[Btn7L])
	{
		while(vexRT[Btn7U]){}
			swing_keep_hgt_to_put_zone();
	}
}


task usercontrol()
{
	StopTask(autonomous);
	stop_all_motors();

	while(1)
	{
		capture_handle();
		manual_handle();
	}
}
