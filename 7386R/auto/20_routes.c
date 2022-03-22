/*#define clear_enc_q_p_L() {SensorValue[enc_move_L]=0;}
#define clear_enc_q_p_R() {SensorValue[enc_move_R]=0;}
#define clear_enc_updown()   {SensorValue[enc_updown]=0;}
#define clear_gyro_q_p() {SensorValue[Gyro]=0;}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  ########   #######  ##     ## ######## ########       ##
//  ##     ## ##     ## ##     ##    ##    ##           ####
//  ##     ## ##     ## ##     ##    ##    ##             ##
//  ########  ##     ## ##     ##    ##    ######         ##
//  ##   ##   ##     ## ##     ##    ##    ##             ##
//  ##    ##  ##     ## ##     ##    ##    ##             ##
//  ##     ##  #######   #######     ##    ########     ######
//red 1

void auto_route_1()//20 points and two zones
{

	unsigned long time_7386x;
	unsigned long time_begin=nSysTime;
	int gyro_aim;
	int  gyro_err;
	int spad_gyro;
	int num_kp=0.5;
	int gyro_now;
	int gyro_last;
	int do_task=1;


	clearTimer(T_auto_timer);
	clearTimer(T_auto_gbl_timer);
//
	clear_enc_q_p_L() 
	clear_enc_q_p_R() 
	clear_enc_updown()  
	clear_gyro_q_p() 

	gyro_last=SensorValue[Gyro];
	wait1Msec(50);
	gyro_now=SensorValue[Gyro];
	spad_gyro=abs(gyro_now-gyro_last);
	if(abs(spad_gyro)>100)
	{
		playTone(1500,100);
		do_task=0;
	}
	if(do_task==1)
	{

		claw_func( pwr_claw_hold_close );//hold_claw
		move( pwr_RT_max_vy*num_kp, 0 );
		wait1Msec(200);//slowly_move
		updown_enc_TASK_FUNC( 15, 1, pwr_updown_up_max-40, 400, T_auto_timer );//updown_slight_up
		move( pwr_RT_max_vy*0.7, 0 );
		startTask(lift_one_key_lowest_task);//lift_down_to_lowest
		wait1Msec(300);
		time_7386x=time1[T_auto_timer];
		while(!limit_lift_dn_pressed&&time1[T_auto_timer]<time_7386x+800);//wait_for_lift_lowest
    //
		foward_adjust_with_enc_itself( 1200, pwr_RT_abs_max-5, pwr_RT_abs_max-5, 0, 600, T_auto_timer, STOPCAR );
//get_mg
		move( pwr_RT_for_auto*num_kp, 0 );
		wait1Msec(100);//hit_mb
		startTask(lift_one_key_highest_task);
		wait1Msec(300);


		clear_enc_q_p_L() 
		clear_enc_q_p_R() 
    //
		move( -(pwr_RT_for_auto*0.8), 0 );//back
		wait1Msec(800);
		startTask(updown_key_down_task);
		time_7386x=time1[T_auto_timer];
		while(!limit_updown_down_pressed&&time1[T_auto_timer]<time_7386x+300);
		startTask(claw_open_task);//put_zone_down


		foward_adjust_with_enc_itself( -1030, pwr_RT_abs_max-5, pwr_RT_abs_max-5, 0, 1300, T_auto_timer, STOPCAR );
//ready_to_turn


		clear_gyro_q_p()
		Turn_Without_PID( -335*auto.ROLE, pwr_RT_abs_max-5, 0, 600, T_auto_timer, STOPCAR );

		clear_enc_q_p_L() 
		clear_enc_q_p_R() 
		foward_adjust_with_enc_itself( -725, pwr_RT_abs_max-5, pwr_RT_abs_max-5, 0, 800, T_auto_timer, STOPCAR );

		clear_gyro_q_p()
		Turn_Without_PID( -710*auto.ROLE, pwr_RT_abs_max-5, 0, 800, T_auto_timer, STOPCAR);

		move( pwr_RT_for_auto, 0 );
		wait1Msec(200);//into 10 points

		updown_enc_TASK_FUNC( 15, 1, pwr_updown_up_max-40, 400, T_auto_timer );
		wait1Msec(100);
		startTask(lift_one_key_lowest_task);
		move( pwr_RT_max_vy, 0 );
		wait1Msec(400);
		move( pwr_RT_abs_max*0.25, 0 );
		wait1Msec(400);
		lift_func( pwr_lift_keep_highest);
		move( -(pwr_RT_abs_max*0.8), 0 );
		wait1Msec(600);
		move( pwr_RT_max_vy, 0 );
		wait1Msec(400);

//     ##     #####      ##     ##  ######  ######## 
//   ####    ##   ##     ###   ### ##    ## ##       
//     ##   ##     ##    #### #### ##       ##       
//     ##   ##     ##    ## ### ##  ######  ######   
//     ##   ##     ##    ##     ##       ## ##       
//     ##    ##   ##     ##     ## ##    ## ##       
//   ######   #####      ##     ##  ######  ######## 

		clear_enc_q_p_L() 
		clear_enc_q_p_R() 
		foward_adjust_with_enc_itself( -725, pwr_RT_abs_max-5, pwr_RT_abs_max-5, 0, 800, T_auto_timer, STOPCAR );


		writeDebugStream("tiem_all:%d/n",nSysTime-time_begin);
	}
	else
	{
		playTone(830,100);
	}
}





//        ##       ## 
//       ##       ##  
//      ##       ##   
//     ##       ##    
//    ##       ##     
//   ##       ##      
//  ##       ## */      
