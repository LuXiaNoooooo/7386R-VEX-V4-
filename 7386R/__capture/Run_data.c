#if !CAPTURE_AUTO
int data_side;
int pl;
int pr;

#if  Enable_Data_1
	#include "__capture\\route_data\\route_data_1.c"
#endif

#if  Enable_Data_2
	#include "__capture\\route_data\\route_data_2.c"
#endif

#if  Enable_Data_3
	#include "__capture\\route_data\\route_data_3.c"
#endif

#if  Enable_Data_4
	#include "__capture\\route_data\\route_data_4.c"
#endif

#if  Enable_Data_5
	#include "__capture\\route_data\\route_data_5.c"
#endif

#if  Enable_Data_6
	#include "__capture\\route_data\\route_data_6.c"
#endif


pwr_move_Struct *pdata;





void set_drv_base_L(int pwr)
{
	#if P1==port_drv_L
	motor[port1] = pwr;
	#endif

	#if P2==port_drv_L
	motor[port2] = pwr;
	#endif

	#if P3==port_drv_L
	motor[port3] = pwr;
	#endif

	#if P4==port_drv_L
	motor[port4] = pwr;
	#endif

	#if P5==port_drv_L
	motor[port5] = pwr;
	#endif

	#if P6==port_drv_L
	motor[port6] = pwr;
	#endif

	#if P7==port_drv_L
	motor[port7] = pwr;
	#endif

	#if P8==port_drv_L
	motor[port8] = pwr;
	#endif

	#if P9==port_drv_L
	motor[port9] = pwr;
	#endif

	#if P10==port_drv_L
	motor[port10] = pwr;
	#endif
}

void set_drv_base_R(int pwr)
{
	#if P1==port_drv_R
	motor[port1] = pwr;
	#endif

	#if P2==port_drv_R
	motor[port2] = pwr;
	#endif

	#if P3==port_drv_R
	motor[port3] = pwr;
	#endif

	#if P4==port_drv_R
	motor[port4] = pwr;
	#endif

	#if P5==port_drv_R
	motor[port5] = pwr;
	#endif

	#if P6==port_drv_R
	motor[port6] = pwr;
	#endif

	#if P7==port_drv_R
	motor[port7] = pwr;
	#endif

	#if P8==port_drv_R
	motor[port8] = pwr;
	#endif

	#if P9==port_drv_R
	motor[port9] = pwr;
	#endif

	#if P10==port_drv_R
	motor[port10] = pwr;
	#endif
}


void get_drv_pwr()
{
	//////////////////////////////////R
	#if P1==port_drv_L
	pl = (*pdata).pwr_1;
	#endif

	#if P2==port_drv_L
	pl = (*pdata).pwr_2;
	#endif

	#if P3==port_drv_L
	pl  = (*pdata).pwr_3;
	#endif

	#if P4==port_drv_L
	pl = (*pdata).pwr_4;
	#endif

	#if P5==port_drv_L
	pl  = (*pdata).pwr_5;
	#endif

	#if P6==port_drv_L
	pl  = (*pdata).pwr_6;
	#endif

	#if P7==port_drv_L
	pl  = (*pdata).pwr_7;
	#endif

	#if P8==port_drv_L
	pl  = (*pdata).pwr_8;
	#endif

	#if P9==port_drv_L
	pl  = (*pdata).pwr_9;
	#endif

	#if P10==port_drv_L
	pl  = (*pdata).pwr_10;
	#endif

	//////////////////////////////////R
		#if P1==port_drv_R
	pr = (*pdata).pwr_1;
	#endif

	#if P2==port_drv_R
	pr = (*pdata).pwr_2;
	#endif

	#if P3==port_drv_R
	pr = (*pdata).pwr_3;
	#endif

	#if P4==port_drv_R
	pr = (*pdata).pwr_4;
	#endif

	#if P5==port_drv_R
	pr = (*pdata).pwr_5;
	#endif

	#if P6==port_drv_R
	pr  = (*pdata).pwr_6;
	#endif

	#if P7==port_drv_R
	pr  = (*pdata).pwr_7;
	#endif

	#if P8==port_drv_R
	pr  = (*pdata).pwr_8;
	#endif

	#if P9==port_drv_R
	pr  = (*pdata).pwr_9;
	#endif

	#if P10==port_drv_R
	pr  = (*pdata).pwr_10;
	#endif
}

void set_drv_base(int pwr_L, int pwr_R, int not_reversed)
{
	if(not_reversed)
	{
		set_drv_base_L(pwr_L);
		set_drv_base_R(pwr_R);
	}
	else
	{
		set_drv_base_L(pwr_R);
		set_drv_base_R(pwr_L);
	}
}





void map_power(unsigned int i)
{

	get_drv_pwr();
	set_drv_base(pl, pr, (data_side == ROLE_SIDE) );

	#if P1==save_pwr_normal
	motor[port1] = (*pdata).pwr_1;
	#endif

	#if P2==save_pwr_normal
	motor[port2] = (*pdata).pwr_2;
	#endif

	#if P3==save_pwr_normal
	motor[port3] = (*pdata).pwr_3;
	#endif

	#if P4==save_pwr_normal
	motor[port4] = (*pdata).pwr_4;
	#endif

	#if P5==save_pwr_normal
	motor[port5] = (*pdata).pwr_5;
	#endif

	#if P6==save_pwr_normal
	motor[port6] = (*pdata).pwr_6;
	#endif

	#if P7==save_pwr_normal
	motor[port7] = (*pdata).pwr_7;
	#endif

	#if P8==save_pwr_normal
	motor[port8] = (*pdata).pwr_8;
	#endif

	#if P9==save_pwr_normal
	motor[port9] = (*pdata).pwr_9;
	#endif

	#if P10==save_pwr_normal
	motor[port10] = (*pdata).pwr_10;
	#endif
}



void run_data()
{
	switch (RUN_ROUTE_DATA_N)
	{
		case 1:
			data_side = data_side_1;
			break;
		case 2:
			data_side = data_side_2;
			break;
		case 3:
			data_side = data_side_3;
			break;
		case 4:
			data_side = data_side_4;
			break;
		default:
			data_side = data_side_1;
			break;
	}




	for (int i = 0; i < NN * PWR_N; i += PWR_N)
	{
		switch (RUN_ROUTE_DATA_N)
		{
				#if  Enable_Data_1
			case 1:
				pdata = (pwr_move_Struct *) (&data_1[i]);
				break;
				#endif


				#if  Enable_Data_2
			case 2:
				pdata = (pwr_move_Struct *) (&data_2[i]);
				break;
				#endif

				#if  Enable_Data_3
			case 3:
				pdata = (pwr_move_Struct *) (&data_3[i]);
				break;
				#endif

				#if  Enable_Data_4
			case 4:
				pdata = (pwr_move_Struct *) (&data_4[i]);
				break;
				#endif

			default:
				break;
		}


		map_power(i);

		clearTimer(T_capture);
		while(time1[T_capture] < interval_capture)
		{
			if(vexRT[Btn7R])
			{
				All_Motors_Pwr_Off();
				return;
			}
			wait1Msec(1);
		}
		//////////////////////////////////////////////////////////////////////////
	}
	All_Motors_Pwr_Off();
}

#endif
