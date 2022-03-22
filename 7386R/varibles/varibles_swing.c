#define pwr_swing_up_max           125
#define pwr_swing_down_max         -125

#define pwr_swing_keep_highest     15
#define pwr_swing_keep_lowest     -18

//////////////////////////////////////////////////


#define limit_swing_dn_pressed    (SensorValue[limit_swing_dn]==0)
#define limit_swing_up_pressed   (SensorValue[limit_swing_up]==0)

typedef enum
{
	swing_dir_dn  = -1,
	swing_dir_up  = 1,
	swing_dir_none  = 0,
} swing_dir_Types;


typedef struct
{
	swing_dir_Types     dir;
	float               pwr;

	int                 chx_swing_raw;
	int                 chx_swing;
} swing_Struct;

Separator __________________________swing=_;
swing_Struct swing;

void swing_Struct_init()
{

}
