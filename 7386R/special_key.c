


//
void special_key_handle()
{
	if(key_special_key)
	{
		claw_func(0);
		Move_Stop();
		updown_func(0);
		swing_func( 0 );
		stop_lift();

		pwr_off = 1;

		stopTask(lift_one_key_lowest_task);
		stopTask(lift_one_key_highest_task);

		while(key_special_key)
		{
			if(vexRT[Btn7R])
			{
				auto_manager( );
			}
			if(vexRT[Btn5U])
			{
				clearSounds();
				playTone(100, 150);
				auto.ROLE = Role_Right;
			}
			if(vexRT[Btn5D])
			{
				clearSounds();
				playTone(1800, 150);
				auto.ROLE = Role_Left;
			}

			if(vexRT[Btn8U])
			{
				playTone(520,100);
				auto.Route=1;
			}
			if(vexRT[Btn8L])
			{
				playTone(1314,100);
				auto.Route=2;
			}
			if(vexRT[Btn8R])
			{
				playTone(666,100);
				auto.Route=3;
			}
			if(vexRT[Btn8D])
			{
				playTone(999,100);
				auto.Route=4;
			}

			
			//define claw close button
			// if(1)
			// {
			// 	if(vexRT[Btn6D])
			// 	{
			// 		claw_open = Btn6U;
			// 		claw_close = Btn6D;
			// 	}

			// 	if(vexRT[Btn6U])
			// 	{
			// 		claw_open = Btn6D;
			// 		claw_close = Btn6U;
			// 	}
			// }

			//handle mode
			// if(1)
			// {
			//     if(vexRT[Btn8U])
			//         handle_mode = handle_mode_updown_joystick;
			//     if(vexRT[Btn8D])
			//         handle_mode = handle_mode_updown_button;
			// }
		}
	}
}

// void special_key_handle_auto_choose()
// {
// 	if(key_special_key_auto_choose)
// 	{
// 		claw_func(0);
// 		Move_Stop();
// 		updown_func(0);
// 		swing_func( 0 );

// 		stop_lift();

// 		pwr_off = 1;

// 		stopTask(lift_one_key_lowest_task);
// 		stopTask(lift_one_key_highest_task);

// 		while(key_special_key_auto_choose)
// 		{
// 			if(vexRT[Btn5U])
// 			{
// 				clearSounds();
// 				playTone(100, 150);
// 				auto.ROLE = Role_Right;
// 			}
// 			if(vexRT[Btn5D])
// 			{
// 				clearSounds();
// 				playTone(1800, 150);
// 				auto.ROLE = Role_Left;
// 			}

// 			if(vexRT[Btn8U])
// 			{
// 				playTone(520,100);
// 				auto.Route=1;
// 			}
// 			if(vexRT[Btn8L])
// 			{
// 				playTone(1314,100);
// 				auto.Route=2;
// 			}
// 			if(vexRT[Btn8D])
// 			{
// 				playTone(666,100);
// 				auto.Route=3;
// 			}
// 			if(vexRT[Btn8R])
// 			{
// 				playTone(999,100);
// 				auto.Route=4;
// 			}
// 		}
// 	}
// }
