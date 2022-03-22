#define clear_enc_q_p_L();  {SensorValue[enc_move_L]=0;}
#define clear_enc_q_p_R(); {SensorValue[enc_move_R]=0;}
#define clear_enc_updown();   {SensorValue[enc_updown]=0;}
#define clear_gyro_q_p(); {SensorValue[Gyro]=0;}
#define reset_local_timer()    {t0=nSysTime;}
#define local_timer()          (nSysTime-t0)
#define clr_enc_move     {SensorValue[enc_move_L]=0;   SensorValue[enc_move_R]=0}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ########   #######  ##     ## ######## ########       ##
//  ##     ## ##     ## ##     ##    ##    ##           ####
//  ##     ## ##     ## ##     ##    ##    ##             ##
//  ########  ##     ## ##     ##    ##    ######         ##
//  ##   ##   ##     ## ##     ##    ##    ##             ##
//  ##    ##  ##     ## ##     ##    ##    ##             ##
//  ##     ##  #######   #######     ##    ########     ######
//red 1
void auto_route_1()
{
	int err;
	unsigned long time_7386x ;
	float num_kp=0.8;
	int enc_now;
	int enc_last;
	int speed_now;
	unsigned long  time_begin=nSysTime;

	clearTimer(T_auto_timer);
	clearTimer(T_auto_gbl_timer);
	claw_func(pwr_claw_hold_close);
	clear_gyro_q_p()
	clear_enc_updown();
	clear_enc_q_p_L();
	clear_enc_q_p_R();

	move( 35, 0 );
	wait1Msec(100);//slowly_move

	startTask(updown_key_up_task);//updown_up_to_let_lift_down
	wait1Msec(200);
	startTask(lift_one_key_lowest_task);//lift_down
	move(70,0);
	wait1Msec(500);
	time_7386x =time1[T_auto_timer];
	while(!limit_lift_dn_pressed&&time1[T_auto_timer]<(time_7386x+500));//wait_for_lift_down
	foward_adjust_with_enc_itself( 1330, pwr_RT_abs_max, pwr_RT_abs_max, 0, 800, T_auto_timer, STOPCAR );
// slowly_forward
	move( 55, 0 );
	wait1Msec(100);
	startTask(lift_one_key_highest_task);
	wait1Msec(100);
	move(-18,0);
	time_7386x =time1[T_auto_timer];
	while(!limit_lift_up_pressed&&time1[T_auto_timer]<(time_7386x+1100));
	startTask(updown_key_down_task);//put_first_zone_down
	time_7386x=time1[T_auto_timer];
	while(!limit_updown_down_pressed&&time1[T_auto_timer]<(time_7386x+400));

	startTask(claw_open_task);
	wait1Msec(200);
	startTask(updown_key_up_task);
	wait1Msec(200);

	    //prepare_to_get_second_cone
	startTask(swing_one_key_lowest_task);
	time_7386x =time1[T_auto_timer];
	while(!limit_swing_dn_pressed&&time1[T_auto_timer]<(time_7386x+400));
	startTask(updown_key_down_task);//wait_updown_down
	wait1Msec(300);
	startTask(claw_open_task);

	//second_zone
	foward_adjust_with_enc_itself( 1540, pwr_RT_abs_max, pwr_RT_abs_max, 0, 500, T_auto_timer, STOPCAR );
	//
	enc_last=SensorValue[enc_move_L];
	wait1Msec(50);
	enc_now=SensorValue[enc_move_L];
	speed_now=enc_now-enc_last;
	if(speed_now<2)
	{
		startTask(claw_close_task);
		wait1Msec(150);
		claw_func(pwr_claw_hold_close);
	}
	else
	{
		Move_Stop();
		startTask(claw_close_task);
		wait1Msec(200);
		claw_func(pwr_claw_hold_close);
	}
	clear_enc_q_p_L();
	clear_enc_q_p_R();
	move( -(pwr_RT_abs_max*num_kp), 0 );//backward THE SAME
	updown_enc_TASK_FUNC( 13, 1,100 , 600, T_auto_timer );
	wait1Msec(300);
	startTask(swing_one_key_highest_task);
	wait1Msec(500);
	startTask(updown_key_down_task);
	wait1Msec(400);
	//startTask(claw_open_task);
	//back_to_zero_place
	foward_adjust_with_enc_itself( -1600,pwr_RT_abs_max, pwr_RT_abs_max, 0, 900, T_auto_timer, STOPCAR );
	claw_func( pwr_claw_hold_open );
	updown_func( pwr_updown_hold_hgt);
	//
	if(auto.ROLE==Role_Left)
	{
		clear_gyro_q_p()
		Turn_Without_PID( -330*auto.ROLE, pwr_RT_abs_max, 0, 500, T_auto_timer, STOPCAR );
	//
		startTask(claw_open_task);
		wait1Msec(300);
		clear_enc_q_p_L();
		clear_enc_q_p_R();
		foward_adjust_with_enc_itself( -720, pwr_RT_abs_max, pwr_RT_abs_max, 0, 1000, T_auto_timer, STOPCAR );
    //
		clear_gyro_q_p()
		Turn_Without_PID( -710*auto.ROLE, pwr_RT_abs_max, 0, 750, T_auto_timer, STOPCAR );
		move(pwr_RT_abs_max+5,0);
		wait1Msec(300);//into _10_points
		startTask(updown_key_up_task);
		wait1Msec(300);
		startTask(lift_one_key_lowest_task);
		wait1Msec(1000);
		lift_func( pwr_lift_keep_highest);
		move( -pwr_RT_abs_max+2, 0 );
		wait1Msec(722);
		writeDebugStream("time1:%d, \n",  time1[T_auto_gbl_timer]);
	}
	else
	{
		clear_gyro_q_p()
		Turn_Without_PID( -330*auto.ROLE, pwr_RT_abs_max, 0, 500, T_auto_timer, STOPCAR );
	//
		clear_enc_q_p_L();
		clear_enc_q_p_R();
		foward_adjust_with_enc_itself( -634, pwr_RT_abs_max-4, pwr_RT_abs_max-6, 0, 1000, T_auto_timer, STOPCAR );
    //
		clear_gyro_q_p()
		Turn_Without_PID(-710*auto.ROLE, pwr_RT_abs_max, 0, 800, T_auto_timer, STOPCAR );
		move(pwr_RT_abs_max+1,0);
		wait1Msec(660);//into _10_points
		startTask(updown_key_up_task);
		wait1Msec(150);
		move(pwr_RT_abs_max-3,0);
		wait1Msec(200);
		startTask(lift_one_key_lowest_task);
		wait1Msec(1346);
		lift_func( pwr_lift_keep_highest);
		wait1Msec(700);
		move( -pwr_RT_abs_max, 0 );
		wait1Msec(250);
		startTask(updown_key_down_task);
		wait1Msec(200);
		foward_adjust_with_enc_itself( 66, 66, 66, 0, 150, T_auto_timer, STOPCAR );
		writeDebugStream("time all:%d\n",  nSysTime-time_begin);
	}
}

//  ########   #######  ##     ## ######## ########     #######
//  ##     ## ##     ## ##     ##    ##    ##          ##     ##
//  ##     ## ##     ## ##     ##    ##    ##                 ##
//  ########  ##     ## ##     ##    ##    ######       #######
//  ##   ##   ##     ## ##     ##    ##    ##          ##
//  ##    ##  ##     ## ##     ##    ##    ##          ##
//  ##     ##  #######   #######     ##    ########    #########

void auto_route_2()
{
	int err;
	unsigned long time_7386x ;
	float num_kp=0.5;
	int enc_now;
	int enc_last;
	int speed_now;
	clear_gyro_q_p()
	clearTimer(T_auto_timer);
	clearTimer(T_auto_gbl_timer);
	claw_func(pwr_claw_hold_close);
	clear_enc_q_p_L();
	clear_enc_q_p_R();

	//updown_enc_TASK_FUNC( 12, 1, 85, 500,T_auto_timer);


	//slowly_move
	move( 25, 0 );
	wait1Msec(100);
	clear_enc_updown();
	startTask(updown_key_up_task);
	//updown_enc_TASK_FUNC( 15, 1, 90, 500,T_auto_timer);
	// updown_up_to_let_lift_down
	wait1Msec(200);
	startTask(lift_one_key_lowest_task);//lift_down

	move(30,0);
	wait1Msec(430);
	time_7386x =time1[T_auto_timer];
	while(!limit_lift_dn_pressed&&time1[T_auto_timer]<(time_7386x+500));//wait_for_lift_down
	wait1Msec(100);
	foward_adjust_with_enc_itself( 1280, pwr_RT_abs_max, pwr_RT_abs_max, 0, 1300, T_auto_timer, STOPCAR );
// slowly_forward
	move( 40, 0 );
	wait1Msec(150);
	startTask(lift_one_key_highest_task);
	move( -15, 0 );
	time_7386x =time1[T_auto_timer];
	while(!limit_lift_up_pressed&&time1[T_auto_timer]<(time_7386x+1300));
	startTask(updown_key_down_task);//put_first_zone_down
	wait1Msec(300);
	startTask(updown_key_down_task);
	wait1Msec(100);
	startTask(claw_open_task);
	wait1Msec(250);
	startTask(updown_key_up_task);
	wait1Msec(250);
	//prepare_to_get_second_cone
	startTask(swing_one_key_lowest_task);
	time_7386x =time1[T_auto_timer];
	while(!limit_swing_dn_pressed&&time1[T_auto_timer]<(time_7386x+800));
	startTask(updown_key_down_task);//wait_updown_down
	wait1Msec(200);
	//startTask(claw_open_task);*************
	//wait1Msec(200);

	//second_zone
	foward_adjust_with_enc_itself( 1530, pwr_RT_abs_max, pwr_RT_abs_max, 0, 600, T_auto_timer, STOPCAR );
	//
	startTask(claw_close_task);
	wait1Msec(200);
    //updown_enc_TASK_FUNC( 16, 1, 100, 600, T_auto_timer );
   // move( -20, 0 );//un
   /* updown_enc_TASK_FUNC( 16, 1, 105, 600, T_auto_timer );
    wait1Msec(300);
    startTask(swing_one_key_highest_task);
    wait1Msec(400);
	//updown_func( pwr_updown_hold_hgt );
	//wait1Msec(300);
	//startTask(updown_key_down_task);
    startTask(updown_key_down_task);
    wait1Msec(400);
	//third zone
	//
	//
   startTask(claw_open_task);
    wait1Msec(200);
    updown_enc_TASK_FUNC( 18, 1, 100, 700, T_auto_timer );
    wait1Msec(100);
    startTask(swing_one_key_lowest_task);
    wait1Msec(100);
    startTask(updown_key_down_task);
    time_7386x =time1[T_auto_timer];
    while(!limit_swing_dn_pressed&&time1[T_auto_timer]<(time_7386x+350));
	//move( 120, 0 );
   // wait1Msec(100);
    foward_adjust_with_enc_itself( 1872, 63	, 63, 0, 500, T_auto_timer, STOPCAR );
    wait1Msec(100);*/
   // startTask(claw_close_task);
   // wait1Msec(200);
	move( -120, 0 );//backward THE SAME
	updown_enc_TASK_FUNC( 22, 1,100 , 600, T_auto_timer );
	wait1Msec(300);
	startTask(swing_one_key_highest_task);
	wait1Msec(450);
	startTask(updown_key_down_task);
	wait1Msec(350);
	startTask(claw_open_task);
	//foward_adjust_with_enc_itself( 250, pwr_RT_abs_max, pwr_RT_abs_max, 0, 1000, T_auto_timer, STOPCAR );
	//move( -120, 0 );
	//wait1Msec(1205);
	wait1Msec(220);
	startTask(updown_key_up_task);
//updown_enc_TASK_FUNC( 15, 1, 80, 600, T_auto_timer );
	//startTask(updown_key_up_task);
	wait1Msec(200);
	startTask(lift_one_key_lowest_task);
	clear_gyro_q_p()
	Turn_Without_PID( -2000*auto.ROLE, pwr_RT_abs_max, 0, 1500, T_auto_timer, STOPCAR );
	time_7386x =time1[T_auto_timer];
	while (!limit_lift_dn_pressed&&time1[T_auto_timer]<(time_7386x+1500));
	move(-pwr_RT_abs_max,20*auto.ROLE);
	wait1Msec(500);


}


//  ########   #######  ##     ## ######## ########     #######
//  ##     ## ##     ## ##     ##    ##    ##          ##     ##
//  ##     ## ##     ## ##     ##    ##    ##                 ##
//  ########  ##     ## ##     ##    ##    ######       #######
//  ##   ##   ##     ## ##     ##    ##    ##                 ##
//  ##    ##  ##     ## ##     ##    ##    ##          ##     ##
//  ##     ##  #######   #######     ##    ########     #######

void auto_route_3()
{pwr_off = 0;
	unsigned long  time0;
	float updown_kp = 0.5;


	playTone(678, 100);
	clearTimer(T_auto_timer);
	clear_enc_q_p_L()
	clear_enc_q_p_R()
	clear_enc_updown()
	clear_gyro_q_p()
	// if (limit_updown_down_pressed)
	updown_enc_TASK_FUNC( 22, 1, 100, 600, T_auto_timer );
	wait1Msec(222);
	updown_func(10);
	foward_adjust_with_enc_itself( 420, pwr_RT_abs_max, 95, 0, 500, T_auto_timer, STOPCAR );
	startTask(swing_one_key_lowest_task);
	wait1Msec(500);
	updown_enc_TASK_FUNC( 40, 1, 80, 300, T_auto_timer );
	startTask(claw_open_task);
	wait1Msec(200);
	updown_func( 13);
	foward_adjust_with_enc_itself( -2, pwr_RT_abs_max, 50, 0, 600, T_auto_timer, !STOPCAR );
	wait1Msec(300);
	updown_enc_TASK_FUNC( 15, -1, 90, 264, T_auto_timer );
	wait1Msec(300);
	//Turn_Without_PID( auto.ROLE*, Speed_ABS, forward, Exit_Time, Timer_x, stopcar );
	Turn_Without_PID( auto.ROLE * (900), 80, 80, 470, T_auto_timer, STOPCAR );
	//updown_enc_TASK_FUNC( 20, 1, 80, 500, T_auto_timer );
	wait1Msec(160);
	startTask(lift_one_key_lowest_task);
	wait1Msec(650);
	//time0 = time1[T_auto_timer];
	//while(!limit_lift_dn_pressed && time1[T_auto_timer] < (time0 + 600));
	foward_adjust_with_enc_itself( 1300, pwr_RT_abs_max, pwr_RT_abs_max, 0, 1360, T_auto_timer, STOPCAR);
	move( 60, 0 );
	wait1Msec(40);
	startTask(lift_one_key_highest_task);
	//time0 = time1[T_auto_timer];
	//while(!limit_lift_up_pressed && time1[T_auto_timer] < (time0 + 1000));
	//updown_enc_TASK_FUNC( 16, dir, pwr, exit_time, timer_x );
	//startTask(updown_key_up_task);
	wait1Msec(650);
	startTask(updown_key_down_task);
	wait1Msec(257);
	startTask(swing_one_key_lowest_task);
	wait1Msec(620);
	//time0 = time1[T_auto_timer];
	//while(!limit_swing_dn_pressed && time0 <= (time1[T_auto_timer] + 600));
	//startTask(updown_key_down_task);
	updown_enc_TASK_FUNC( -1, -1, 99, 240, T_auto_timer );
	wait1Msec(500);
	//time0 = time1[T_auto_timer];
	//while(!limit_updown_down_pressed && time0 <= (time1[T_auto_timer] + 1000));
	move( 40, 0 );
	wait1Msec(40);
	startTask(claw_close_task);
	wait1Msec(150);
	move( -120, 0 );
	/*startTask(updown_key_up_task);
	wait1Msec(196);
	// updown_enc_TASK_FUNC(10,1,40,500,T_auto_timer);
	// wait1Msec(300);
	startTask(swing_one_key_highest_task);
	wait1Msec(560);
	startTask(updown_key_down_task);
	time0 = time1[T_auto_timer];
	while(!limit_updown_down_pressed && time1[T_auto_timer] < (time0 + 400));
	startTask(claw_open_task);
	wait1Msec(100);//finish
	foward_adjust_with_enc_itself(-20, pwr_RT_abs_max, 40, 0, 1500, T_auto_timer, STOPCAR );
	wait1Msec(200);

	updown_enc_TASK_FUNC( 20, 1, 80, 500, T_auto_timer );
	Turn_Without_PID( auto.ROLE * (-2400), 35, 0, 2000, T_auto_timer, STOPCAR );

	clr_enc_move;
	foward_adjust_with_enc_itself(-100, pwr_RT_abs_max, 40, 0, 200, T_auto_timer, STOPCAR );

	startTask(lift_one_key_lowest_task);
	wait1Msec(800);
	time0 = time1[T_auto_timer];
	while(!limit_lift_dn_pressed && time1[T_auto_timer] < (time0 + 1000));
	foward_adjust_with_enc_itself(0, pwr_RT_abs_max, 40, 0, 260, T_auto_timer, STOPCAR );

	move( -50, 0 );
	wait1Msec(500);
	Move_Stop();*/
	move( -120, 0 );//backward THE SAME
	updown_enc_TASK_FUNC( 22, 1,100 , 600, T_auto_timer );
	wait1Msec(300);
	startTask(swing_one_key_highest_task);
	wait1Msec(500);
	startTask(updown_key_down_task);
	wait1Msec(350);
	startTask(claw_open_task);
	//foward_adjust_with_enc_itself( 250, pwr_RT_abs_max, pwr_RT_abs_max, 0, 1000, T_auto_timer, STOPCAR );
	//move( -120, 0 );
	//wait1Msec(1205);
	wait1Msec(100);
	startTask(updown_key_up_task);
//updown_enc_TASK_FUNC( 15, 1, 80, 600, T_auto_timer );
	//startTask(updown_key_up_task);
	wait1Msec(200);
	startTask(lift_one_key_lowest_task);
	clear_gyro_q_p()
	Turn_Without_PID( -2222*auto.ROLE, pwr_RT_abs_max, 0, 1500, T_auto_timer, STOPCAR );
	time0 =time1[T_auto_timer];
	while (!limit_lift_dn_pressed&&time1[T_auto_timer]<(time0+1500));
	move(-pwr_RT_abs_max,20*auto.ROLE);
	wait1Msec(500);


}

//  ########   #######  ##     ## ######## ########    ##
//  ##     ## ##     ## ##     ##    ##    ##          ##    ##
//  ##     ## ##     ## ##     ##    ##    ##          ##    ##
//  ########  ##     ## ##     ##    ##    ######      ##    ##
//  ##   ##   ##     ## ##     ##    ##    ##          #########
//  ##    ##  ##     ## ##     ##    ##    ##                ##
//  ##     ##  #######   #######     ##    ########          ##

void auto_route_4()
{
	unsigned long  time_7386X_R;
	clearTimer(T_auto_timer);
	clear_gyro_q_p();
	clear_enc_q_p_R();
	clear_enc_q_p_L();

	//
	//
	//
	move( pwr_RT_max_vy*0.25, 0 );
	wait1Msec(100);//slowly_move
	updown_enc_TASK_FUNC( 50, 1, pwr_updown_up_max-20, 500, T_auto_timer );//updwon_up_to_put_rocket
	foward_adjust_with_enc_itself( 310, pwr_RT_abs_max*0.7, pwr_RT_abs_max*0.7, 0, 800, T_auto_timer, STOPCAR );
	updown_enc_TASK_FUNC( 40, -1, pwr_updown_down_max-40, 600, T_auto_timer );
	if(getTaskState(updown_enc_task)==taskStateRunning)
		wait1Msec(200);//wait_updown_down

	startTask(claw_open_task);//claw_open_to_put_zone_on_the_rocket
	wait1Msec(100);
	move( -pwr_RT_abs_max*0.35, 0 );
	wait1Msec(100);
	updown_enc_TASK_FUNC( 45, 1, pwr_updown_up_max, 600, T_auto_timer );
	foward_adjust_with_enc_itself( 80, pwr_RT_abs_max*0.6, pwr_RT_abs_max*0.6, 0, 800, T_auto_timer, STOPCAR );
	wait1Msec(100);//wait_for_move_stop

	clear_gyro_q_p()
	Turn_Without_PID( -740*auto.ROLE, pwr_RT_max_turn-40, 0, 1200, T_auto_timer, STOPCAR );

	clear_enc_q_p_L()
	clear_enc_q_p_R()

	move( pwr_RT_max_vy*0.4, 0 );
	startTask(lift_one_key_lowest_task);
	wait1Msec(200);//put_lift_down

	updown_enc_TASK_FUNC( 30, -1, pwr_updown_down_max, 800, T_auto_timer );

	move( pwr_RT_max_vy*0.65, 0 );
	time_7386X_R=time1[T_auto_timer];
	while(!limit_lift_dn_pressed&&time1[T_auto_timer]<time_7386X_R+900);
	foward_adjust_with_enc_itself( 1330, pwr_RT_max_vy, pwr_RT_max_vy, 0, 800, T_auto_timer, STOPCAR );

	startTask(lift_one_key_lowest_task);
//get_mg
	move( pwr_RT_abs_max*0.5, 0 );
	wait1Msec(100);
	startTask(lift_one_key_highest_task);
	move( -pwr_RT_abs_max*0.25, 0 );
	wait1Msec(400);
	move( 0, 0 );
	startTask(claw_open_task);
	wait1Msec(400);
	startTask(updown_key_down_task);

	foward_adjust_with_enc_itself( 1500, pwr_RT_abs_max, pwr_RT_abs_max, 0, 600, T_auto_timer, STOPCAR );
	wait1Msec(20);
	startTask(claw_close_task);
	wait1Msec(200);
	move( -pwr_RT_max_vy*0.8, 0 );
	wait1Msec(500);
	updown_enc_TASK_FUNC( 30, 1, pwr_updown_up_max-30, 500, T_auto_timer );
	wait1Msec(100);
	startTask(swing_one_key_highest_task);
	wait1Msec(200);

	foward_adjust_with_enc_itself( 580, pwr_RT_abs_max, pwr_RT_abs_max, 0, 600, T_auto_timer, STOPCAR );
	//back
	move( -20, -40 );
	wait1Msec(100);
	startTask(updown_key_down_task);
	clear_gyro_q_p();
	Turn_Without_PID( -1200*auto.ROLE, pwr_RT_max_turn, 0, 1000, T_auto_timer, STOPCAR );
	startTask(claw_open_task);
	move( pwr_RT_abs_max*0.25, 0 );
	wait1Msec(200);
	updown_enc_TASK_FUNC( 35, 1, pwr_updown_up_max-30, 500, T_auto_timer );
	wait1Msec(50);
	//
	startTask(lift_one_key_lowest_task);
	time_7386X_R=time1[T_auto_timer];
	while (!limit_lift_dn_pressed&&time1[T_auto_timer]<time_7386X_R+800);
	clear_enc_q_p_R();
	clear_enc_q_p_L();


	foward_adjust_with_enc_itself( -400, pwr_RT_abs_max, pwr_RT_abs_max, 0, 600, T_auto_timer, STOPCAR );
	startTask(swing_one_key_lowest_task);




}
