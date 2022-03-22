#define CAPTURE_AUTO         1 //change it to start capture

int capturing_auto=0;

//save port_x
#define save_pwr_not        0
#define save_pwr_normal     2
#define port_drv_L          -1
#define port_drv_R          1

#define P1  save_pwr_not
#define P2  save_pwr_normal
#define P3  save_pwr_normal
#define P4  port_drv_L
#define P5  save_pwr_normal
#define P6  port_drv_R
#define P7  save_pwr_normal
#define P8  save_pwr_normal
#define P9  save_pwr_normal
#define P10 save_pwr_not



const int PWR_N = !!P1 + !!P2 + !!P3 + !!P4 + !!P5 + !!P6 + !!P7 + !!P8 + !!P9 + !!P10;

#define ROLE_LEFT  1
#define ROLE_RIGHT -1

int ROLE_SIDE=ROLE_RIGHT;
int RUN_ROUTE_DATA_N=1;


///////////////////////////////////////////////////////////////////////////////////////
void save_pwr(unsigned int i);
void clear_all_data(unsigned int i);
void map_power(unsigned int i);

void All_Motors_Pwr_Off()
{
	for (int i = port1; i < port10; i++)
	{
		motor[i]=0;
	}
}



#define Enable_Data_1   1
#define Enable_Data_2   0
#define Enable_Data_3   0
#define Enable_Data_4   0
#define Enable_Data_5   0
#define Enable_Data_6   0


#define data_side_1  ROLE_LEFT
#define data_side_2  ROLE_RIGHT
#define data_side_3  ROLE_RIGHT
#define data_side_4  ROLE_RIGHT
#define data_side_5  ROLE_RIGHT
#define data_side_6  ROLE_RIGHT


//////////////////////////////////////////////////////////////////////////////////////
#define  T_capture T1
#include "Capture_Replay_Pwr.c"
#include "Run_data.c"
#include "capture_handle.c"
