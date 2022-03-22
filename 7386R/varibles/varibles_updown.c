#include "includes.c"
//
#define pwr_updown_up_max           121
#define pwr_updown_down_max         -99
#define pwr_updown_keep_lowest       -18

#define pwr_updown_hold_hgt          12


//////////////////////////////////////////////////
#define  enc_updown_up             22
#define  enc_updown_down            0

#define limit_updown_down_pressed (SensorValue[limit_updown_dn]==0)

typedef enum
{
	updown_dir_dn  = -1,
	updown_dir_up  = 1,
	updown_dir_none  = 0,
} updown_dir_Types;


typedef struct
{
	int     dir;
	float   pwr;

	int     chx_updown_raw;
	int     chx_updown;

} updown_Struct;

Separator __________________________updown=_;
updown_Struct updown;

void updown_Struct_init()
{

}
