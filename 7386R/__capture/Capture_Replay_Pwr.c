#define time_capture      15000                               //30000
#define interval_capture  30                                  //30
#define NN                (time_capture/interval_capture)     //985


//2950 bytes max
typedef struct
{
	#if P1
	signed char pwr_1;
	#endif

	#if P2
	signed char pwr_2;
	#endif

	#if P3
	signed char pwr_3;
	#endif

	#if P4
	signed char pwr_4;
	#endif

	#if P5
	signed char pwr_5;
	#endif

	#if P6
	signed char pwr_6;
	#endif

	#if P7
	signed char pwr_7;
	#endif

	#if P8
	signed char pwr_8;
	#endif

	#if P9
	signed char pwr_9;
	#endif

	#if P10
	signed char pwr_10;
	#endif
} pwr_move_Struct;

#if CAPTURE_AUTO

pwr_move_Struct pwr_move[NN];

void clear_all_data(unsigned int i)
{
	#if P1
	pwr_move[i].pwr_1 = 0;
	#endif

	#if P2
	pwr_move[i].pwr_2 = 0;
	#endif

	#if P3
	pwr_move[i].pwr_3 = 0;
	#endif

	#if P4
	pwr_move[i].pwr_4 = 0;
	#endif

	#if P5
	pwr_move[i].pwr_5 = 0;
	#endif

	#if P6
	pwr_move[i].pwr_6 = 0;
	#endif

	#if P7
	pwr_move[i].pwr_7 = 0;
	#endif

	#if P8
	pwr_move[i].pwr_8 = 0;
	#endif

	#if P9
	pwr_move[i].pwr_9 = 0;
	#endif

	#if P10
	pwr_move[i].pwr_10 = 0;
	#endif
}


void save_pwr(unsigned int i)
{
	#if P1
	pwr_move[i].pwr_1 = motor[port1];
	#endif

	#if P2
	pwr_move[i].pwr_2 = motor[port2];
	#endif

	#if P3
	pwr_move[i].pwr_3 = motor[port3];
	#endif

	#if P4
	pwr_move[i].pwr_4 = motor[port4];
	#endif

	#if P5
	pwr_move[i].pwr_5 = motor[port5];
	#endif

	#if P6
	pwr_move[i].pwr_6 = motor[port6];
	#endif

	#if P7
	pwr_move[i].pwr_7 = motor[port7];
	#endif

	#if P8
	pwr_move[i].pwr_8 = motor[port8];
	#endif

	#if P9
	pwr_move[i].pwr_9 = motor[port9];
	#endif

	#if P10
	pwr_move[i].pwr_10 = motor[port10];
	#endif
}



task capture_task()
{
	unsigned int i = 0;

	for ( i = 0; i < NN; i++)
	{
		clear_all_data(i);
	}

	clearTimer(T_capture);
	clearDebugStream();

	i = 0;
	while ( time1[T_capture] <= time_capture &&  i < NN )
	{
		save_pwr(i);

		i++;
		wait1Msec(interval_capture);
	}

	playTone(333, 100);
	capturing_auto = 0;

}

/////////////////////////////////////////////////////////////////////////////////
void play_pwr(unsigned int i)
{
	#if P1
	motor[port1] = pwr_move[i].pwr_1;
	#endif

	#if P2
	motor[port2] = pwr_move[i].pwr_2;
	#endif

	#if P3
	motor[port3] = pwr_move[i].pwr_3;
	#endif

	#if P4
	motor[port4] = pwr_move[i].pwr_4;
	#endif

	#if P5
	motor[port5] = pwr_move[i].pwr_5;
	#endif

	#if P6
	motor[port6] = pwr_move[i].pwr_6;
	#endif

	#if P7
	motor[port7] = pwr_move[i].pwr_7;
	#endif

	#if P8
	motor[port8] = pwr_move[i].pwr_8;
	#endif

	#if P9
	motor[port9] = pwr_move[i].pwr_9;
	#endif

	#if P10
	motor[port10] = pwr_move[i].pwr_10;
	#endif
}



void replay_pwr()
{
	for (int i = 0; i < NN; i ++)
	{
		play_pwr(i);

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
	}
	//////////////////////////////////////////////////////////////////////////
	All_Motors_Pwr_Off();
}



void print_pwr_frame(unsigned int i)
{
	#if P1
	writeDebugStream("%-4d,", pwr_move[i].pwr_1);
	#endif

	#if P2
	writeDebugStream("%-4d,", pwr_move[i].pwr_2);
	#endif

	#if P3
	writeDebugStream("%-4d,", pwr_move[i].pwr_3);
	#endif

	#if P4
	writeDebugStream("%-4d,", pwr_move[i].pwr_4);
	#endif

	#if P5
	writeDebugStream("%-4d,", pwr_move[i].pwr_5);
	#endif

	#if P6
	writeDebugStream("%-4d,", pwr_move[i].pwr_6);
	#endif

	#if P7
	writeDebugStream("%-4d,", pwr_move[i].pwr_7);
	#endif

	#if P8
	writeDebugStream("%-4d,", pwr_move[i].pwr_8);
	#endif

	#if P9
	writeDebugStream("%-4d,", pwr_move[i].pwr_9);
	#endif

	#if P10
	writeDebugStream("%-4d,", pwr_move[i].pwr_10);
	#endif

	writeDebugStream("\n", );
}


void  print_pwr()
{
	for (int i = 0; i < NN; i++)
	{
		while(getAvailSpaceInDebugStream() < 70)
			wait1Msec(1);
		print_pwr_frame(i);
		wait1Msec(2);
	}
}


#endif
