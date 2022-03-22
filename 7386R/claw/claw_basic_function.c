void claw_func(int pwr )
{
	motor[mtr_claw]=pwr;
	claw.pwr=pwr;
}

task claw_close_task();
task claw_open_task();

task claw_open_task()
{
	stopTask(claw_close_task);
	claw_func( pwr_claw_open );
	wait1Msec(300);
	claw_func( pwr_claw_hold_open );
}
task claw_close_task()
{
	stopTask(claw_open_task);
	claw_func(pwr_claw_close);
	wait1Msec(300);
	claw_func( pwr_claw_hold_close );
}