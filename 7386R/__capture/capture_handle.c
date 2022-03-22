void capture_handle()
{
	//replay
	if(vexRT[Btn7D] && vexRT[Btn7U] ) //replay and run data
	{
		while_pressing( vexRT[Btn7D] || vexRT[Btn7U] );
		playTone(1500, 200);

		#if CAPTURE_AUTO
		replay_pwr();
		#else
		run_data();
		#endif
	}

	#if CAPTURE_AUTO  //capture

	//capture
	if(vexRT[Btn7D] && vexRT[Btn6D])
	{
		All_Motors_Pwr_Off();

		capturing_auto = 1;
		stopTask(capture_task);

		while_pressing( vexRT[Btn7D] || vexRT[Btn6D] );

		playTone(150, 50);
		startTask(capture_task);
	}

	//print data
	if(vexRT[Btn7D] && vexRT[Btn7R])
	{
		while_pressing( vexRT[Btn7D] || vexRT[Btn7R] );
		print_pwr();
	}
	#endif
}
